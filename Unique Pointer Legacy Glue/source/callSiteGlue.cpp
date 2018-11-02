#include "SmartPointerAdapter.h"
#include "Destroyable.h"

// Now let's consider a scenario where createDestroyable() cannot be changed. Maybe it comes from a third party library,
// or maybe it comes from internal library that is code-frozen at the moment.

static bool createDestroyable_cannotBeChanged(Destroyable *& destroyableOut)
{
    TRACE;
    destroyableOut = new Destroyable;
    return destroyableOut->init();
}

// The question is how can you write modern code using such an API?
// The following is not very elegant.

static bool legacy()
{
    TRACE;
    unique_ptr<Destroyable, DestroyDeleter> ptr;

    Destroyable * temp = NULL;
    bool rc = createDestroyable_cannotBeChanged(temp);
    ptr.reset(temp);

    return rc && ptr->doStuff();
}

// The unique pointer adapter will do the trick.

static bool better()
{
    TRACE;
    unique_ptr<Destroyable, DestroyDeleter> ptr;

    // The adaptUniquePtr macro calls a function that returns UniquePointerAdapter object. 
    // This object holds internally a pointer to the unique pointer and a plain pointer.
    // The plain pointer can be reference-accessed by the .get() method, and the macro does call it for us.
    // The trick is that the temporary object will remain in scope for the duration of call
    // and once the call finishes it will be destroyed. When that happens, the destructor updates
    // the unique pointer to whatever value is now present in the plain pointer.

    if (!createDestroyable_cannotBeChanged(adaptSmartPointer(ptr)))
    {
        return false;
    }

    return ptr->doStuff();
}


// The mechanism of SmartPointerAdapter can backfire
// when one inadvertently tries to use the smart pointer
// before SmartPointerAdapter leaves scope.
// adaptSmartPointer creates a temporary variable that is within
// scope for the whole full expression. In theory temporary variable scope can
// even be extended by making a reference to it, but the macro should prevent
// that. But there are still ways to execute multiple functions within one full expression
// such as the below.

static bool pitfall()
{
    unique_ptr<Destroyable, DestroyDeleter> ptr;

    return (
        createDestroyable_cannotBeChanged(adaptSmartPointer(ptr))
        &&
        ptr->doStuff() // error - still the same full expression, ptr is not updated yet
    );
}

// Other things to watch out for:
//  * Simultaneous (usually asynchronous, but not necessarily) access to the unique pointer
//  * Callee storing retaining reference to the temporary pointer after the call finishes

void callSiteGlue()
{
    legacy();
    better();
}
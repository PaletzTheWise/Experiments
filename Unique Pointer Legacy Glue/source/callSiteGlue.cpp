#include "SmartPointerAdapter.h"
#include "Destroyable.h"

static bool maybe()
{
	return rand() % 100 > 0;
}

// Now let's consider a scenario where createDestroyable() is untouchable. Maybe it comes from a third party library,
// or maybe it comes from internal library that is code-frozen at the moment.

static bool createDestroyable(Destroyable *& destroyableOut, bool shouldSucceedInit)
{
	bool rc = true; // chain through RC for single return at the bottom glory

	rc = rc && ((destroyableOut = new Destroyable) != NULL); // On a normal compiler new can't return null, but let's suppose the line looks like this for whatever reason.
	rc = rc && destroyableOut->init(shouldSucceedInit);

	return rc;
}

// The question is how can you write modern code using such an API?

static bool notSoModern()
{
	unique_ptr<Destroyable, DestroyDeleter> ptr;

	Destroyable * temp = NULL;
	bool rc = createDestroyable(temp, maybe());
	ptr.reset(temp);

	return (
		rc
		&&
		ptr->doStuff(maybe())
	);
}

// The unique pointer adapter will do the trick.

static bool modern()
{
	unique_ptr<Destroyable,DestroyDeleter> ptr;

	return (
		createDestroyable( adaptSmartPointer(ptr), maybe())
		&&
		ptr->doStuff(maybe())
	);
}

// The adaptUniquePtr macro calls a function that returns UniquePointerAdapter object. 
// This object holds internally a pointer to the unique pointer and a plain pointer.
// The plain pointer can be reference-accessed by the .get() method, and the macro does call it for us.
// The trick is that the temporary object will remain in scope for the duration of call
// and once the call finishes it will be destroyed. When that happens, the destructor updates
// the unique pointer to whatever value is now present in the plain pointer.
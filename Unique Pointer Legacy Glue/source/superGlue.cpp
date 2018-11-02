#include "SmartPointerAdapter.h"
#include "OutputPointer.h"
#include "Destroyable.h"

// Final scenario where both glues are combined.
// Assuming there is a third party function to create an object that we cannot upgrade to unique pointer.

static void createDestroyableThirdParty(Destroyable *& destroyableOut)
{
	TRACE;
	destroyableOut = new Destroyable;
}

// Then a legacy function initializes the created object

static bool initDestroyableLegacy(Destroyable *& destroyableOut)
{
	TRACE;
	createDestroyableThirdParty( destroyableOut );
	return destroyableOut->init();
}

// And another legacy function initializes it a bit more

static bool initMoreDestroyableLegacy(Destroyable *& destroyableOut)
{
	TRACE;
	bool rc =  initDestroyableLegacy(destroyableOut);
	return rc && destroyableOut->init(); // more init()
}

// And finally yet another legacy function uses the init more function.

static bool legacy()
{
	TRACE;
	Destroyable * ptr = NULL; // define all variables at the top for more legacy feel :)
	
	bool rc = initMoreDestroyableLegacy(ptr);
	rc = rc && ptr->doStuff();

	if (ptr != NULL)
	{
		ptr->destroy();
	}

	return rc;
}

// We can improve init function using the OutputPointer to keep it compatible with all call sites.
// However, the third party create function won't e compatible with OutputPointer, so we have to use adaptSmartPointer().
// Fortunately, even though OutputPointer is not a smart pointer in the strictest sense, it still does fulfill the requirements of
// SmartPointerAdapter.

static bool initDestroyableBetter(OutputPointer<Destroyable, DestroyDeleter> destroyableOut)
{
	TRACE;
	createDestroyableThirdParty(adaptSmartPointer(destroyableOut));
	return destroyableOut->init();
}

static bool initMoreDestroyableBetter(OutputPointer<Destroyable, DestroyDeleter> destroyableOut)
{
	TRACE;
	if (!initDestroyableBetter(destroyableOut))
	{
		return false;
	}

	return destroyableOut->init();
}

// Now we can improve the legacy method to use unique_ptr.

static bool better()
{
	TRACE;
	unique_ptr<Destroyable, DestroyDeleter> ptr;
	
	return (
		initMoreDestroyableBetter(ptr)
		&&
		ptr->doStuff()
	);
}

void superGlue()
{
	legacy();
	better();
}
#include "SmartPointerAdapter.h"
#include "OutputPointer.h"
#include "Destroyable.h"

// Final scenario where both glues are combined.
// Assuming there is a third party function to create an object that we cannot upgrade to unique pointer.

static bool createDestroyableThirdParty(Destroyable *& destroyableOut)
{
	TRACE;
	return (destroyableOut = new Destroyable) != NULL; // On a normal compiler new can't return null, but let's suppose the line looks like this for whatever reason.
}

// Then a legacy function initializes the created object

static bool initDestroyableLegacy(Destroyable *& destroyableOut)
{
	TRACE;
	bool rc = true; // chain through RC for single return at the bottom glory

	rc = rc && createDestroyableThirdParty( destroyableOut );
	rc = rc && destroyableOut->init();

	return rc;
}

// And another legacy function initializes it a bit more

static bool initMoreDestroyableLegacy(Destroyable *& destroyableOut)
{
	TRACE;
	bool rc = true; // chain through RC for single return at the bottom glory

	rc = rc && initDestroyableLegacy(destroyableOut);
	rc = rc && destroyableOut->init(); // more init()

	return rc;
}

// And finally yet another legacy function uses the init more function.

static bool legacy()
{
	TRACE;
	Destroyable * ptr = NULL; // define all variables at the top for more legacy feel :)
	bool rc = true; // chain through RC for single return at the bottom glory

	rc = rc && initMoreDestroyableLegacy(ptr);
	rc = rc && ptr->doStuff();

	if (ptr != NULL)
	{
		ptr->destroy();
	}

	return rc;
}

// We can improve init function using the OutputPointer to keep it compatible with all call sites.
// However, the third party create function won't e compatible with OutputPointer, so we have to use adaptSmartPointer().
// Fortunately, even though OutputPointer is not a smart pointer in the strictest sense, it still does fullfil the requirements of
// SmartPointerAdapter.

static bool initDestroyableBetter(OutputPointer<Destroyable, DestroyDeleter> destroyableOut)
{
	TRACE;
	if (!createDestroyableThirdParty(adaptSmartPointer(destroyableOut)))
	{
		return false;
	}

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
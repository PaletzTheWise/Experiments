#include "SmartPointerAdapter.h"
#include "OutPointer.h"
#include "Destroyable.h"

static bool maybe()
{
	return rand() % 100 > 0;
}

// Final scenario where both glues are combined.
// Assuming there is a third party function to create an object that we cannot upgrade to unique pointer.

static bool createDestroyableThirdParty(Destroyable *& destroyableOut, bool shouldSucceed)
{
	return shouldSucceed && ((destroyableOut = new Destroyable) != NULL); // On a normal compiler new can't return null, but let's suppose the line looks like this for whatever reason.
}

// Then a legacy function initializes the created object

static bool initDestroyableLegacy(Destroyable *& destroyableOut, bool shouldSucceedInit)
{
	bool rc = true; // chain through RC for single return at the bottom glory

	rc = rc && createDestroyableThirdParty( destroyableOut, maybe());
	rc = rc && destroyableOut->init(shouldSucceedInit);

	return rc;
}

// And finally some other legacy function uses the init function.

static bool legacy()
{
	Destroyable * ptr = NULL; // define all variables at the top for more legacy feel :)
	bool rc = true; // chain through RC for single return at the bottom glory

	rc = rc && initDestroyableLegacy(ptr, maybe());
	rc = rc && ptr->doStuff(maybe());

	if (ptr != NULL)
	{
		ptr->destroy();
	}

	return rc;
}

//

static bool initDestroyableBetter(OutPointer<Destroyable, DestroyDeleter> destroyableOut, bool shouldSucceedInit)
{
	return (
		createDestroyableThirdParty(adaptSmartPointer(destroyableOut), maybe())
		&&
		destroyableOut->init(shouldSucceedInit)
	);
}

static bool legacyBetter()
{
	unique_ptr<Destroyable, DestroyDeleter> ptr;
	
	return (
		initDestroyableBetter(ptr, maybe())
		&&
		ptr->doStuff(maybe())
	);
}
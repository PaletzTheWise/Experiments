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
	if (!destroyableOut->init())
	{
		destroyableOut = nullptr;
		return false;
	}

	return true;
}

// And another legacy function initializes it a bit more

static bool initMoreDestroyableLegacy(Destroyable *& destroyableOut)
{
	TRACE;
	bool rc =  initDestroyableLegacy(destroyableOut);

	if (!destroyableOut->init())
	{
		destroyableOut = nullptr;
		return false;
	}

	return true;
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
	if (!destroyableOut->init())
	{
		destroyableOut = nullptr;
		return false;
	}

	return true;
}

static bool initMoreDestroyableBetter(OutputPointer<Destroyable, DestroyDeleter> destroyableOut)
{
	TRACE;
	if (!initDestroyableBetter(destroyableOut))
	{
		return false;
	}

	if (!destroyableOut->init())
	{
		destroyableOut = nullptr;
		return false;
	}

	return true;
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

Destroyable * createDestroyableNewLike()
{
	return new Destroyable();
}

unique_ptr<Destroyable, DestroyDeleter> createDestroyableUniqueLike()
{
	return unique_ptr<Destroyable, DestroyDeleter>(new Destroyable);
}


void superGlue()
{
	legacy();
	better();

	unique_ptr<Destroyable, DestroyDeleter> b( createDestroyableNewLike() );
	b = unique_ptr<Destroyable, DestroyDeleter>( createDestroyableNewLike() );
	Destroyable * c = createDestroyableNewLike();

	unique_ptr<Destroyable, DestroyDeleter> a(createDestroyableUniqueLike());
	b = unique_ptr<Destroyable, DestroyDeleter>(createDestroyableUniqueLike());

	unique_ptr<Destroyable, DestroyDeleter> a(createDestroyableUniqueLike());
	b = createDestroyableUniqueLike();
}
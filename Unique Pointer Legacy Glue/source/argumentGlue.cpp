#include "OutputPointer.h"
#include "Destroyable.h"

// Now I will outline how a legacy method can be upgraded in a bacwkard compatible fashion with little effort

static bool createDestroyableLegacy(Destroyable *& destroyableOut)
{
	TRACE;
	bool rc = true; // chain through RC for single return at the bottom glory

	rc = rc && ((destroyableOut = new Destroyable) != NULL); // On a normal compiler new can't return null, but let's suppose the line looks like this for whatever reason.
	rc = rc && destroyableOut->init();

	return rc;
}

static bool createDestroyableBetter(OutputPointer<Destroyable, DestroyDeleter> destroyableOut)
{
	TRACE;
	bool rc = true; // chain through RC for single return at the bottom glory

	rc = rc && ((destroyableOut = new Destroyable) != NULL); // On a normal compiler new can't return null, but let's suppose the line looks like this for whatever reason.
	rc = rc && destroyableOut->init();

	return rc;
}

// Ok, did we just change the argument type? Indeed. No actual changes were needed in the body itself!
// There are functionality changes though. Now we can pass unique_ptr references as the first argument.
// WARNING! Non-null plain pointer held by destroyableOut will now be deleted before overwritten, 
// doesn't matter if it originates from outside or inside.

// As you can see below, createDestroyableBetter() works the same way with plain pointer reference as createDestroyableLegacy()

static bool legacy()
{
	TRACE;
	Destroyable * ptr = NULL; // define all variables at the top for more legacy feel :)
	bool rc = true; // chain through RC for single return at the bottom glory

	rc = rc && createDestroyableLegacy(ptr);
	rc = rc && createDestroyableBetter(ptr); // destroys object created by createDestroyableLegacy(), createDestroyableLegacy() wouldn't do that unless explicitly coded to do so.
	rc = rc && ptr->doStuff();

	if (ptr != NULL)
	{
		ptr->destroy();
	}

	return rc;
}

// Call sites can be upgraded one by one as needed.

static bool better()
{
	TRACE;
	unique_ptr<Destroyable,DestroyDeleter> ptr;

	return (
		createDestroyableBetter(ptr)
		&&
		ptr->doStuff()
	);
}

void argumentGlue()
{
	legacy();
	better();
}
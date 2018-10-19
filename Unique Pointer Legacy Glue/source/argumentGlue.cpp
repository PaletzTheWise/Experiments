#include "OutPointer.h"
#include "Destroyable.h"

static bool maybe()
{
	return rand() % 100 > 0;
}

// Now I will outline how a legacy method can be upgraded in a bacwkard compatible fashion

static bool createDestroyableLegacy(Destroyable *& destroyableOut, bool shouldSucceedInit)
{
	bool rc = true; // chain through RC for single return at the bottom glory

	rc = rc && ((destroyableOut = new Destroyable) != NULL); // On a normal compiler new can't return null, but let's suppose the line looks like this for whatever reason.
	rc = rc && destroyableOut->init(shouldSucceedInit);

	return rc;
}

static bool createDestroyableBetter(OutPointer<Destroyable, DestroyDeleter> destroyableOut, bool shouldSucceedInit)
{
	bool rc = true; // chain through RC for single return at the bottom glory

	rc = rc && ((destroyableOut = new Destroyable) != NULL); // On a normal compiler new can't return null, but let's suppose the line looks like this for whatever reason.
	rc = rc && destroyableOut->init(shouldSucceedInit);

	return rc;
}

// Ok, did we just change the argument type? Yeah and no changes were needed in the body itself!
// There are functionality changes. Now we can unique_ptr references as the first argument.
// WARNING! If non-null plain pointer will now be deleted before overwritten, doesn't matter if they originate from outside or inside.
// As you can see below, createDestroyableBetter() works the same way with plain pointer reference as createDestroyableLegacy()

static bool legacy2()
{
	Destroyable * ptr = NULL; // define all variables at the top for more legacy feel :)
	bool rc = true; // chain through RC for single return at the bottom glory

	rc = rc && createDestroyableLegacy(ptr, maybe());
	rc = rc && createDestroyableBetter(ptr, maybe());
	rc = rc && ptr->doStuff(maybe());

	if (ptr != NULL)
	{
		ptr->destroy();
	}

	return rc;
}

// Later on, you can upgrade the call site.

static bool legacy2Upgraded()
{
	unique_ptr<Destroyable,DestroyDeleter> ptr;

	return (
		createDestroyableBetter(ptr, maybe())
		&&
		ptr->doStuff(maybe())
	);
}
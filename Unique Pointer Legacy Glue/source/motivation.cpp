
#include <iostream>
#include <memory>
using namespace std;

#include "Destroyable.h"

static bool maybe()
{
	return rand() % 100 > 0;
}

// Let's suppose you have legacy code that uses plain pointers to track resources

static bool legacy1()
{
	Destroyable * ptr = NULL; // define all variables at the top for more legacy feel :)
	bool rc = true; // chain through RC for single return at the bottom glory

	rc = rc && ((ptr = new Destroyable) != NULL); // On a normal compiler new can't return null, but let's suppose the line looks like this for whatever reason.
	rc = rc && ptr->init(maybe());
	rc = rc && ptr->doStuff(maybe());

	if (ptr != NULL)
	{
		ptr->destroy();
	}

	return rc;
}

// Rewriting the above using unique_ptr / RAII is simple and makes the code easier to read

static bool legacy1Upgraded()
{
	bool rc = true; // chain through RC for single return at the bottom glory

	unique_ptr<Destroyable,DestroyDeleter> ptr(new Destroyable);
	rc = rc && (ptr.get() != NULL); // On a normal compiler new can't return null, but let's suppose the line looks like this for whatever reason.
	rc = rc && ptr->init(maybe());
	rc = rc && ptr->doStuff(maybe());

	// no need to destroy manually, win!

	return rc;
}

// The problem is new and delete/destroy is often not happening in the same method

static bool createDestroyable(Destroyable *& destroyableOut, bool shouldSucceedInit)
{
	bool rc = true; // chain through RC for single return at the bottom glory

	rc = rc && ((destroyableOut = new Destroyable) != NULL); // On a normal compiler new can't return null, but let's suppose the line looks like this for whatever reason.
	rc = rc && destroyableOut->init(shouldSucceedInit);

	return rc;
}

static bool legacy2()
{
	Destroyable * ptr = NULL; // define all variables at the top for more legacy feel :)
	bool rc = true; // chain through RC for single return at the bottom glory

	rc = rc && createDestroyable( ptr, maybe());
	rc = rc && ptr->doStuff(maybe());

	if (ptr != NULL)
	{
		ptr->destroy();
	}

	return rc;
}

// Now assuming there are many methods like createDestroyable() and even more call sites like legacy2() it might be
// infeasible to upgrade createDestroyable() and all its call site in one go.

// You could overload createDestroyable() to remain backward compatible.

static bool createDestroyableUpgraded(unique_ptr<Destroyable, DestroyDeleter> & destroyableOut, bool shouldSucceedInit)
{
	Destroyable *ptr = nullptr;
	bool rc = createDestroyable(ptr, shouldSucceedInit);
	destroyableOut.reset(ptr);
	return rc;
}

// But again, if there are many functions like that, that would add a lot of arguably ugly glue code.


// Alternatively, you might want to upgrade the call site

static bool legacy2Upgraded()
{
	unique_ptr<Destroyable, DestroyDeleter> ptr; // define all variables at the top for more legacy feel :)
	bool rc = true; // chain through RC for single return at the bottom glory

	{ // Just as ugly as createDestroyableUpgraded() and now duplicated to each call site :(
		Destroyable * temp = NULL;
		rc = rc && createDestroyable(temp, maybe());
		ptr.reset(temp);
	}
	rc = rc && ptr->doStuff(maybe());

	return rc;
}
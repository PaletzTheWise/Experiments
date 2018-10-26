
#include <iostream>
#include <memory>
using namespace std;

#include "Destroyable.h"

// Let's suppose you have legacy code that uses plain pointers to track resources

static bool legacy1()
{
	Destroyable * ptr = NULL; // define all variables at the top for more legacy feel :)
	bool rc = true; // chain through RC for single return at the bottom glory

	rc = rc && ((ptr = new Destroyable) != NULL); // On a normal compiler new can't return null, but let's suppose the line looks like this for whatever reason.
	rc = rc && ptr->init();
	rc = rc && ptr->doStuff();

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
	rc = rc && ptr->init();
	rc = rc && ptr->doStuff();

	// no need to destroy manually, win!

	return rc;
}

// The problem is new and delete/destroy is often not happening in the same method

static bool createDestroyable(Destroyable *& destroyableOut)
{
	bool rc = true; // chain through RC for single return at the bottom glory

	rc = rc && ((destroyableOut = new Destroyable) != NULL); // On a normal compiler new can't return null, but let's suppose the line looks like this for whatever reason.
	rc = rc && destroyableOut->init();

	return rc;
}

static bool legacy2()
{
	Destroyable * ptr = NULL; // define all variables at the top for more legacy feel :)
	bool rc = true; // chain through RC for single return at the bottom glory

	rc = rc && createDestroyable( ptr);
	rc = rc && ptr->doStuff();

	if (ptr != NULL)
	{
		ptr->destroy();
	}

	return rc;
}

// Applying unique_ptr to legacy2() results in code that doesn't look great becasue there has to be
// a temporary pointer and aditional call to reset unique_ptr. 

static bool legacy2Upgraded()
{
	unique_ptr<Destroyable, DestroyDeleter> ptr; // define all variables at the top for more legacy feel :)
	bool rc = true; // chain through RC for single return at the bottom glory

	{ 
		Destroyable * temp = NULL;
		rc = rc && createDestroyable(temp);
		ptr.reset(temp);
	}
	rc = rc && ptr->doStuff();

	return rc;
}

// The root of the problem is createDestroyable() itself and that can be addressed.
// As simple wrapper function can fix the problem, either as an overload or a distinctly named variation.
// Either way the code is backward-compatible with legacy call sites.

static bool createDestroyableUpgraded(unique_ptr<Destroyable, DestroyDeleter> & destroyableOut)
{
	Destroyable *ptr = nullptr;
	bool rc = createDestroyable(ptr);
	destroyableOut.reset(ptr);
	return rc;
}

static bool legacy2MoreUpgraded()
{
	unique_ptr<Destroyable, DestroyDeleter> ptr; // define all variables at the top for more legacy feel :)
	bool rc = true; // chain through RC for single return at the bottom glory

	rc = rc && createDestroyableUpgraded(ptr);
	rc = rc && ptr->doStuff();

	return rc;
}


// But if there are many functions like that, it requires a lot of arguably ugly glue code.
// On the other hand if there are few call sites and functions, it is probably easier just to change createDestroyable() and
// fix all call sites in one go.
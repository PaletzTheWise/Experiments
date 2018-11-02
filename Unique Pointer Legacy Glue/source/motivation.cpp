
#include <iostream>
#include <memory>
using namespace std;

#include "Destroyable.h"

// Let's suppose you have legacy code that uses plain pointers to track resources

static bool legacy1()
{
	Destroyable * ptr = new Destroyable;

	bool rc = ptr->init();
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
	unique_ptr<Destroyable,DestroyDeleter> ptr(new Destroyable);

	bool rc = ptr->init();
	rc = rc && ptr->doStuff();

	// no need to destroy manually, win!

	return rc;
}

// The problem is new and delete/destroy is often not happening in the same method and the pointer is often assigned to pointer reference

static bool createDestroyable(Destroyable *& destroyableOut)
{
	destroyableOut = new Destroyable;

	if ( destroyableOut->init() )
	{
		destroyableOut->destroy();
		destroyableOut = NULL;
		return false;
	}

	return true;
}

static bool legacy2()
{
	Destroyable * ptr = NULL;

	bool rc = createDestroyable( ptr );
	rc = rc && ptr->doStuff();

	if (ptr != NULL)
	{
		ptr->destroy();
	}

	return rc;
}

// Applying unique_ptr to legacy2() results in code that doesn't look great becasue there has to be
// a temporary pointer and additional call to reset unique_ptr. 

static bool legacy2Upgraded()
{
	unique_ptr<Destroyable, DestroyDeleter> ptr;
	bool rc = true;

	{ 
		Destroyable * temp = NULL;
		rc = rc && createDestroyable(temp);
		ptr.reset(temp);
	}

	rc = rc && ptr->doStuff();

	return rc;
}

// The root of the problem is createDestroyable() itself and that can be addressed.
// A simple wrapper function can fix the problem, either as an overload or a distinctly named variation.
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
	unique_ptr<Destroyable, DestroyDeleter> ptr;
	
	return createDestroyableUpgraded(ptr) && ptr->doStuff();
}


// But if there are many functions like that, it requires a lot of arguably ugly glue code.
// On the other hand if there are few call sites and functions, it is probably easier just to change createDestroyable() and
// fix all call sites in one go.
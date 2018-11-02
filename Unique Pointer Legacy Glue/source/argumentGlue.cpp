#include "OutputPointer.h"
#include "Destroyable.h"

// Now I will outline how a legacy method can be upgraded in a backward compatible fashion with little effort

static bool createDestroyableLegacy(Destroyable *& destroyableOut)
{
	TRACE;
	destroyableOut = new Destroyable;
	return destroyableOut->init();
}

static bool createDestroyableBetter(OutputPointer<Destroyable, DestroyDeleter> destroyableOut)
{
	TRACE;
	destroyableOut = new Destroyable;
	return destroyableOut->init();
}

// OK, did we just change the argument type? Indeed. No actual changes were needed in the body itself!
// There are functionality changes though. Now we can pass unique_ptr references as the first argument.
// WARNING! Non-null plain pointer held by destroyableOut will now be deleted before overwritten, 
// doesn't matter if it originates from outside or inside.

// As you can see below, createDestroyableBetter() works the same way with plain pointer reference as createDestroyableLegacy()

static bool legacy()
{
	TRACE;
	Destroyable * ptr = NULL;
	
	bool rc = createDestroyableLegacy(ptr);
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
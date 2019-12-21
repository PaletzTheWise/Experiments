#include <iostream>     
#include <memory>
using namespace std;
#include "Destroyable.h"

// naive comparison of plain pointer and smart pointer code

static bool doSomething()
{
	return true;
}

static void doSomethingThatCannotFail()
{
}

static bool dumb1()
{
	int * resource = new int(0);
	bool rc = true;

	if ( doSomething() )
	{
		if ( doSomething() )
		{
			doSomethingThatCannotFail();
		}
		else
		{
			rc = false;
		}
	}
	else
	{
		rc = false;
	}

	delete resource;
	return rc;
}

static bool dumb2()
{
	int * resource = new int(0);

	if ( !doSomething() )
	{
		delete resource;
		return false;
	}

	if ( !doSomething() )
	{
		delete resource;
		return false;
	}
	
	doSomethingThatCannotFail();

	delete resource;
	return true;
}

static bool dumb3()
{
	int * resource = new int(0);
	bool rc = true;

	rc = rc && doSomething();
	rc = rc && doSomething();

	if (rc)
	{
		doSomethingThatCannotFail();
	}
	
	delete resource;
	return rc;
}

static bool smart()
{
	unique_ptr<int> resource(new int(0));

	if ( !doSomething() || !doSomething() )
	{
		return false;
	}

	doSomethingThatCannotFail();

	return true;
}
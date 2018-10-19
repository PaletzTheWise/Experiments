#include <iostream>
#include <string>
using namespace std;

#include "NamedValue.h"

// Stage 3: Use macros to make invocation.

#include "NamedValueMacros.h"

static bool readBooleanFromRegistry(
	const wstring & name,
	NamedParam( bool, defaultV ),
	NamedParam( bool, doThrow ),
	NamedParam( bool, doWrite ),
	NamedParam( bool, caseSens ) )
{
	wcout
		<< "readBooleanFromRegistry(" << endl
		<< "    name:     " << name << endl
		<< "    defaultV: " << *defaultV << endl
		<< "    doThrow:  " << *doThrow << endl
		<< "    doWrite:  " << *doWrite << endl
		<< "    caseSens: " << *caseSens << endl
		<< ")" << endl;
	// look up the registry value
	return true;
}

void stage3()
{
	cout << "Stage 3" << endl;
	bool godModeEnabled = readBooleanFromRegistry(
		L"GodMode",
		NV(defaultV, false),
		NV(doThrow, true),
		NV(doWrite, true),
		NV(caseSens, false)
	);

	NamedValue<typestring_is("defaultV"), bool> test = false;
}
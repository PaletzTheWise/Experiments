#include <iostream>
#include <string>
using namespace std;

#include "NamedValueMacros.h"

// Stage 4: Default parameters

static bool readBooleanFromRegistry(
	const wstring & name,
	NamedParam(bool, defaultV),
	NamedParam(bool, doThrow) = false, // default parameter values work, yaaay!
	NamedParam(bool, doWrite) = true,
	NamedParam(bool, caseSens) = true)
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

void stage4()
{
	cout << "Stage 4" << endl;
	bool noClipEnabled = readBooleanFromRegistry(
		L"NoClip",
		NV(defaultV, false),
		true // not sure I'm cool with this but it works
	);
	
	NamedValue<typestring_is("doWrite"), bool> test = false; // but both default arguments and unnamed parameters work because automatic conversion is allowed
}
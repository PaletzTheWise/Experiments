#include <iostream>
#include <string>
using namespace std;

#include "NamedValueMacros.h"

// Stage 5: Unordered parameters via overloading.

static bool readBooleanFromRegistry(
	const wstring & name,
	NamedParam(bool, defaultV),
	NamedParam(bool, doThrow) = false,
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

// this overload allows doWrite to be omitted
static bool readBooleanFromRegistry(
	const wstring & name,
	NamedParam(bool, defaultV),
	NamedParam(bool, doThrow) = false,
	NamedParam(bool, caseSens) = true,
	NamedParam(bool, doWrite) = true )
{
	return readBooleanFromRegistry(name, defaultV, doThrow, doWrite, caseSens);
}

void stage5()
{
	cout << "Stage 5" << endl;
	bool noClipEnabled = readBooleanFromRegistry(
		L"NoClip",
		NV(defaultV, false),
		NV(doThrow, false),
		NV(caseSens, true )
	);

	// coincidentally we can no longer pass unnamed parameters because function call would be ambiguous
}
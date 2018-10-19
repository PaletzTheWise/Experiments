#include <iostream>
#include <string>
#include <memory>
using namespace std;

#include "NamedValueMacros.h"

// Stage 6: Unordered parameters via template pattern matching.

#include "CompileTimeList.h"

/*
readBooleanFromRegistry_listify( const wstring & name, NamedValue<TN1,TV1> v1, NamedValue<TN2,TV2> v2, NamedValue<TN3,TV3> v3 )
// collects parameters into template list
>>
readBooleanFromRegistry_initstruct( const wstring & name, TemplateList< NamedValue<TN,TV> head, TTail tail > list )
// adds struct with unset parameters
>>
readBooleanFromRegistry_matchHead( const wstring & name, TemplateList< NamedValue<TN,TV> head, TTail tail > list, ReadBoolFromRegistryParameters struct )
// each call pulls the head and via patter matching puts assigns it into correct field in the struct and calls recursively... or fails. When the list is empty call the final implementation and pass only the struct.
>>
readBooleanFromRegistry_final( const wstring & name, ReadBoolFromRegistryParameters struct )
// the final implementation
*/

class ReadBoolFromRegistryParameters
{
public:

	unique_ptr<bool> defaultV;
	unique_ptr<bool> doWrite;
	unique_ptr<bool> doThrow;
	unique_ptr<bool> caseSens;
};

static wstring toString(const unique_ptr<bool> & value)
{
	if (value.get() != NULL)
	{
		return (*value ? L"true" : L"false");
	}
	else
	{
		return L"null";
	}
}

static bool readBooleanFromRegistry_final(
	const wstring & name,
	ReadBoolFromRegistryParameters & params )
{
	wcout
		<< "readBooleanFromRegistry(" << endl
		<< "    name:     " << name << endl
		<< "    defaultV: " << toString(params.defaultV) << endl
		<< "    doThrow:  " << toString(params.doThrow) << endl
		<< "    doWrite:  " << toString(params.doWrite) << endl
		<< "    caseSens: " << toString(params.caseSens) << endl
		<< ")" << endl;
	// look up the registry value
	return true;
}

bool readBooleanFromRegistry_matchHead(const wstring & name, EmptyCompileTimeList emptyList, ReadBoolFromRegistryParameters & params)
{
	return readBooleanFromRegistry_final(name, params);
}

template<class TName, class TValue, class TTail>
bool readBooleanFromRegistry_matchHead(const wstring & name, CompileTimeList< NamedValue<TName, TValue>, TTail> list, ReadBoolFromRegistryParameters & params)
{
	static_assert(!std::is_same<TValue, TValue>::value, "readBooleanFromRegistry(): Invalid argument provided." );
}

template<class TTail>
bool readBooleanFromRegistry_matchHead(const wstring & name, CompileTimeList< NamedValue<typestring_is("defaultV"), bool>, TTail> list, ReadBoolFromRegistryParameters & params)
{
	params.defaultV.reset( new bool(*(list.head)) );
	return readBooleanFromRegistry_matchHead( name, list.tail, params );
}

template<class TTail>
bool readBooleanFromRegistry_matchHead(const wstring & name, CompileTimeList< NamedValue<typestring_is("doWrite"), bool>, TTail> list, ReadBoolFromRegistryParameters & params)
{
	params.doWrite.reset( new bool(*(list.head)) );
	return readBooleanFromRegistry_matchHead(name, list.tail, params);
}

template<class TTail>
bool readBooleanFromRegistry_matchHead(const wstring & name, CompileTimeList< NamedValue<typestring_is("doThrow"), bool>, TTail> list, ReadBoolFromRegistryParameters & params)
{
	params.doThrow.reset(new bool(*(list.head)));
	return readBooleanFromRegistry_matchHead(name, list.tail, params);
}

template<class TTail>
bool readBooleanFromRegistry_matchHead(const wstring & name, CompileTimeList< NamedValue<typestring_is("caseSens"), bool>, TTail> list, ReadBoolFromRegistryParameters & params)
{
	params.caseSens.reset(new bool(*(list.head)));
	return readBooleanFromRegistry_matchHead(name, list.tail, params);
}

template<class THead, class TTail>
bool readBooleanFromRegistry_initStruct(const wstring & name, CompileTimeList< THead, TTail> list)
{
	ReadBoolFromRegistryParameters paramStruct;
	return readBooleanFromRegistry_matchHead( name, list, paramStruct);
}

template<class T1, class T2, class T3, class T4>
bool readBooleanFromRegistry_listify(const wstring & name, T1 p1, T2 p2, T3 p3, T4 p4)
{
	auto list = MakeCtl(p1, p2, p3, p4);
	return readBooleanFromRegistry_initStruct(name, list);
}

void stage6()
{
	cout << "Stage 6" << endl;
	
	{
		// manually set param struct
		ReadBoolFromRegistryParameters paramStruct;
		paramStruct.defaultV.reset( new bool(false) );
		paramStruct.doWrite.reset( new bool(true) );
		readBooleanFromRegistry_final(L"godMode", paramStruct);
	}

	{ 
		// one param matchHead
		CompileTimeList< NamedValue< typestring_is("defaultV"), bool>, EmptyCompileTimeList> paramList(true, EmptyCompileTimeList());
		readBooleanFromRegistry_initStruct(L"noClip", paramList);
	}

	{
		// two param matchHead build with ConcatenateCtl
		auto paramList = ConcatenateCtl( NV( doWrite, true), ConcatenateCtl(NV(defaultV, true)) );
		readBooleanFromRegistry_initStruct(L"giveAll", paramList);
	}

	{
		// four param matchHead build with MakeCtl
		auto paramList = MakeCtl( NV(doWrite, true), NV(defaultV, true), NV(caseSens, false), NV(doThrow, false) );
		readBooleanFromRegistry_initStruct(L"giveAllFour", paramList);
	}

	{
		// listify
		readBooleanFromRegistry_listify(L"slowmo", NV(doWrite, false), NV(defaultV, false), NV(caseSens, true), NV(doThrow, true) );
	}

	{
		// passing incorrect values
		//readBooleanFromRegistry_listify(L"slowmo", NV(dead, false), NV(defaultV, false), NV(caseSens, true), NV(doThrow, true)); // Error C2338 readBooleanFromRegistry() : Invalid argument provided.Named Parameters
		//readBooleanFromRegistry_listify(L"slowmo", NV(doWrite, 5), NV(defaultV, false), NV(caseSens, true), NV(doThrow, true)); // Error C2338 readBooleanFromRegistry() : Invalid argument provided.Named Parameters
	}
}

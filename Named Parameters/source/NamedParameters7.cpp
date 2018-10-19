#include <iostream>
#include <string>
#include <memory>
using namespace std;

#include "NamedValueMacros.h"
#include "CompileTimeList.h"

// Stage 7: Unordered parameters and optional/required parameter checking, via template pattern matching

// readBooleanFromRegistry( const wstring & name, NamedValue<TN1,TV1> v1, NamedValue<TN2,TV2> v2, NamedValue<TN3,TV3> v3 )
//	  make compile time list from params
//	  convert list to struct, fails if params are not provided correctly
//	  return readBooleanFromRegistry_impl(name, paramStruct);


class ReadBoolFromRegistryParameters
{
public:

	unique_ptr<bool> defaultV;
	unique_ptr<bool> doWrite;
	unique_ptr<bool> doThrow;
	unique_ptr<bool> caseSens;
};

template<bool defaultVSet, bool doWriteSet, bool doThrowSet, bool caseSensSet>
class ReadBoolFromRegistryParameterAvailability
{
public:
	typedef ReadBoolFromRegistryParameterAvailability<true, doWriteSet, doThrowSet, caseSensSet> WithDefaultVSet;
	typedef ReadBoolFromRegistryParameterAvailability<defaultVSet, true, doThrowSet, caseSensSet> WithDoWriteSet;
	typedef ReadBoolFromRegistryParameterAvailability<defaultVSet, doWriteSet, true, caseSensSet> WithDoThrowSet;
	typedef ReadBoolFromRegistryParameterAvailability<defaultVSet, doWriteSet, doThrowSet, true> WithCaseSensSet;

	static void AssertDefaultVNotSet()
	{
		static_assert(!defaultVSet, "Multiple values for DefaultV.");
	}

	static void AssertDoWriteNotSet()
	{
		static_assert(!doWriteSet, "Multiple values for DoWrite.");
	}

	static void AssertDoThrowNotSet()
	{
		static_assert(!doThrowSet, "Multiple values for DoThrow.");
	}

	static void AssertCaseSensNotSet()
	{
		static_assert(!caseSensSet, "Multiple values for CaseSens.");
	}
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

static bool readBooleanFromRegistry_impl(
	const wstring & name,
	ReadBoolFromRegistryParameters & params)
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

template<class TParameterAvailability, class TList>
class readBooleanFromRegistry_matchHead
{
public:
	static bool run(TList list, ReadBoolFromRegistryParameters & params)
	{
		static_assert(!std::is_same<TList, TList>::value, "readBooleanFromRegistry(): List must be a CompileTimeList of NamedValue<name,value> or EmptyCompileTimeList.");
	}
};

template<class TParameterAvailability, class TName, class TValue, class TTail>
class readBooleanFromRegistry_matchHead<TParameterAvailability, CompileTimeList< NamedValue<TName, TValue>, TTail> >
{
public:
	static bool run(CompileTimeList< NamedValue<TName, TValue>, TTail> list, ReadBoolFromRegistryParameters & params)
	{
		static_assert(!std::is_same<TValue, TValue>::value, "readBooleanFromRegistry(): Invalid argument provided.");
	}
};

template<class TParameterAvailability>
class readBooleanFromRegistry_matchHead<TParameterAvailability, EmptyCompileTimeList>
{
public:
	static bool run(EmptyCompileTimeList emptyList, ReadBoolFromRegistryParameters & params)
	{
		static_assert(!std::is_same<TParameterAvailability, TParameterAvailability>::value, "Missing parameter.");
	}
};

template<bool doWriteSet, bool doThrow, bool caseSens>
class readBooleanFromRegistry_matchHead<ReadBoolFromRegistryParameterAvailability<true, doWriteSet, doThrow, caseSens>, EmptyCompileTimeList >
{
public:
	typedef EmptyCompileTimeList TList;

	static void run(TList list, ReadBoolFromRegistryParameters & params)
	{
	}
};

template<class TParameterAvailability, class TTail>
class readBooleanFromRegistry_matchHead<TParameterAvailability, CompileTimeList< NamedValue<typestring_is("defaultV"), bool>, TTail> >
{
public:
	typedef CompileTimeList< NamedValue<typestring_is("defaultV"), bool>, TTail> TList;

	static void run(TList list, ReadBoolFromRegistryParameters & params)
	{
		TParameterAvailability::AssertDefaultVNotSet();
		params.defaultV.reset(new bool(*(list.head)));
		readBooleanFromRegistry_matchHead<typename TParameterAvailability::WithDefaultVSet, typename TList::TTail>::run(list.tail, params);
	}
};

template<class TParameterAvailability, class TTail>
class readBooleanFromRegistry_matchHead<TParameterAvailability, CompileTimeList< NamedValue<typestring_is("doWrite"), bool>, TTail>>
{
public:
	typedef CompileTimeList< NamedValue<typestring_is("doWrite"), bool>, TTail> TList;

	static void run(TList list, ReadBoolFromRegistryParameters & params)
	{
		TParameterAvailability::AssertDoWriteNotSet();
		params.doWrite.reset(new bool(*(list.head)));
		readBooleanFromRegistry_matchHead<typename TParameterAvailability::WithDoWriteSet, typename TList::TTail>::run(list.tail, params);
	}
};

template<class TParameterAvailability, class TTail>
class readBooleanFromRegistry_matchHead<TParameterAvailability, CompileTimeList< NamedValue<typestring_is("doThrow"), bool>, TTail> >
{
public:
	typedef CompileTimeList< NamedValue<typestring_is("doThrow"), bool>, TTail> TList;

	static void run(TList list, ReadBoolFromRegistryParameters & params)
	{
		TParameterAvailability::AssertDoThrowNotSet();
		params.doThrow.reset(new bool(*(list.head)));
		readBooleanFromRegistry_matchHead<typename TParameterAvailability::WithDoThrowSet, typename TList::TTail>::run(list.tail, params);
	}
};

template<class TParameterAvailability, class TTail>
class readBooleanFromRegistry_matchHead<TParameterAvailability, CompileTimeList< NamedValue<typestring_is("caseSens"), bool>, TTail>>
{
public:
	typedef CompileTimeList< NamedValue<typestring_is("caseSens"), bool>, TTail> TList;

	static void run(TList list, ReadBoolFromRegistryParameters & params)
	{
		TParameterAvailability::AssertCaseSensNotSet();
		params.caseSens.reset(new bool(*(list.head)));
		readBooleanFromRegistry_matchHead<typename TParameterAvailability::WithCaseSensSet, typename TList::TTail>::run(list.tail, params);
	}
};

template<class TList>
ReadBoolFromRegistryParameters readBooleanFromRegistry_listToStruct(TList list)
{
	ReadBoolFromRegistryParameters paramStruct;
	readBooleanFromRegistry_matchHead<ReadBoolFromRegistryParameterAvailability<false,false,false,false>, TList >::run(list, paramStruct);
	return paramStruct;
}

template<class T1 = IgnoredCtlElement *, class T2 = IgnoredCtlElement *, class T3 = IgnoredCtlElement *, class T4 = IgnoredCtlElement *>
bool readBooleanFromRegistry(const wstring & name, T1 p1 = nullptr, T2 p2 = nullptr, T3 p3 = nullptr, T4 p4 = nullptr)
{
	auto list = MakeCtl(p1, p2, p3, p4);
	ReadBoolFromRegistryParameters paramStruct = readBooleanFromRegistry_listToStruct(list);
	return readBooleanFromRegistry_impl(name, paramStruct);
}

void stage7()
{
	cout << "Stage 7" << endl;

	// all parameters passed
	readBooleanFromRegistry(L"godMode", NV(doWrite, false), NV(defaultV, false), NV(caseSens, true), NV(doThrow, true));

	// only required parameters passed
	readBooleanFromRegistry(L"noClip", NV(defaultV, false));
	

	// passing the same parameter twice
	//readBooleanFromRegistry(L"godMode", NV(doThrow, false), NV(defaultV, false), NV(caseSens, true), NV(doThrow, true)); // Error	C2338	Multiple values for DoThrow.
	
	// omitting required parameter
	//readBooleanFromRegistry(L"godMode", NV(doThrow, false), NV(caseSens, true), NV(doThrow, true));
}
#pragma once

#include <iostream> 
#include <memory>
#include "OutputPointer.h"
#include "Trace.h"
using namespace std;

// This adapter allows a modern caller to call legacy functions that expect
// reference to a pointer for the purpose of returning a newly created object.
// This assumes the caller has a smart pointer, such as unique_ptr, ready to 
// accept the newly create object and the only thing left to do is to bridge
// the API gap.
//
// The implementation mimics what the caller would probably do manually -
// it creates a temporary plain pointer that can be given to the legacy function.
// When the instance leaves scope, the destructor propagates the value in the temporary
// plain pointer back to the smart pointer.
//
// WARNING:
//  * Simultaneous access to the smart pointer will result in undefined behavior.
//  * Callee retaining reference to the temporary plain pointer after the adapter
//    leaves scope will result in undefined behavior.
template<typename TSmartPointer, typename T>
class SmartPointerAdapter
{
	TSmartPointer * smartPointer;
	T * plainPointer;

public:
	
	SmartPointerAdapter(TSmartPointer * uniquePointer)
		: smartPointer(uniquePointer)
	{
		TRACE;
		plainPointer = uniquePointer->get();
		Trace::indent();
		cout << "acquired " << plainPointer << endl;
	}

	SmartPointerAdapter(SmartPointerAdapter && other)
	{
		TRACE;
		smartPointer = other.smartPointer;
		plainPointer = other.plainPointer;

		// due to the destructor mechanism there can be only one
		other.smartPointer = NULL; 
		other.plainPointer = NULL;
	}

	~SmartPointerAdapter()
	{
		TRACE;
		Trace::indent();
		cout << "propagating " << plainPointer << endl;
		if (smartPointer && SmartPointerAdapterOperations::get( *smartPointer ) != plainPointer)
		{
			SmartPointerAdapterOperations::reset(*smartPointer, plainPointer);
		}
	}

	T *& get()
	{
		TRACE;
		return plainPointer;
	}

	void operator=(SmartPointerAdapter &) = delete;
};

namespace SmartPointerAdapterOperations
{
	// A set of fucntions for unique_ptr

	template<typename T, typename TDeleter>
	T * get(unique_ptr<T, TDeleter> & uniquePointer)
	{
		TRACE;
		return uniquePointer.get();
	}

	template<typename T, typename TDeleter>
	void reset(unique_ptr<T, TDeleter> & uniquePointer, T * value)
	{
		TRACE;
		uniquePointer.reset(value);
	}

	// A set of functions for OutputPointer

	template<typename T, typename TDeleter>
	T * get(OutputPointer<T, TDeleter> & outPointer)
	{
		TRACE;
		return outPointer.get();
	}

	template<typename T, typename TDeleter>
	void reset(OutputPointer<T, TDeleter> & outPointer, T * value)
	{
		TRACE;
		outPointer.reset(value);
	}
}

// Function allows us to infer template parameters
template<typename T, typename TDeleter>
SmartPointerAdapter<unique_ptr<T, TDeleter>, T> makeSmartPointerAdapter(unique_ptr<T, TDeleter> & uniquePointer)
{
	TRACE;
	return SmartPointerAdapter<unique_ptr<T, TDeleter>, T>(&uniquePointer);
}

// Function allows us to infer template parameters
template<typename T, typename TDeleter>
SmartPointerAdapter<OutputPointer<T, TDeleter>, T> makeSmartPointerAdapter(OutputPointer<T, TDeleter> & uniquePointer)
{
	TRACE;
	return SmartPointerAdapter<OutputPointer<T, TDeleter>, T>(&uniquePointer);
}

// Macro allows to automatically use the pointer ref returned by get() while the adapter remains in scope
// WARNING:
//  * Caller using the smart pointer in the same statement where adaptSmartPointer() is used will
//    result in undefined behavior. For example the following would fail:
//      create( adaptSmartPtr(smartPtr) ) && smartPtr->DoStuff();
//    The above can be corrected by adding ';' between adaptSmartPtr(smartPtr) and smartPtr->DoStuff():
//      bool rc = create( adaptSmartPtr(smartPtr) );
//      rc && smartPtr->DoStuff()
//    works fine.
//  * Simultaneous access to the smart pointer will result in undefined behavior.
//  * Callee retaining reference to the temporary plain pointer after the adapter
//    leaves scope will result in undefined behavior.
#define adaptSmartPointer( smartPointer ) (makeSmartPointerAdapter(smartPointer).get())
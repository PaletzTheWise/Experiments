#pragma once

#include <iostream> 
#include <memory>
#include "OutPointer.h"
using namespace std;

template<typename TSmartPointer, typename T>
class SmartPointerAdapter
{
	TSmartPointer * smartPointer;
	T * plainPointer;

public:
	
	SmartPointerAdapter(TSmartPointer * uniquePointer)
		: smartPointer(uniquePointer)
	{
		plainPointer = uniquePointer->get();
	}

	SmartPointerAdapter(SmartPointerAdapter && other)
	{
		smartPointer = other.smartPointer;
		plainPointer = other.plainPointer;
		other.smartPointer = NULL; // due to the destructor mechanism there can be only one
		other.plainPointer = NULL;
	}

	~SmartPointerAdapter()
	{
		if (smartPointer && SmartPointerAdapterOperations::get( *smartPointer ) != plainPointer)
		{
			SmartPointerAdapterOperations::reset(*smartPointer, plainPointer);
		}
	}

	T *& get()
	{
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
		return uniquePointer.get();
	}

	template<typename T, typename TDeleter>
	void reset(unique_ptr<T, TDeleter> & uniquePointer, T * value)
	{
		uniquePointer.reset(value);
	}

	// A set of functions for OutPointer

	template<typename T, typename TDeleter>
	T * get(OutPointer<T, TDeleter> & outPointer)
	{
		return outPointer.get();
	}

	template<typename T, typename TDeleter>
	void reset(OutPointer<T, TDeleter> & outPointer, T * value)
	{
		outPointer.reset(value);
	}
}

// Function allows us to infer template parameters
template<typename T, typename TDeleter>
SmartPointerAdapter<unique_ptr<T, TDeleter>, T> makeSmartPointerAdapter(unique_ptr<T, TDeleter> & uniquePointer)
{
	return SmartPointerAdapter<unique_ptr<T, TDeleter>, T>(&uniquePointer);
}

// Function allows us to infer template parameters
template<typename T, typename TDeleter>
SmartPointerAdapter<OutPointer<T, TDeleter>, T> makeSmartPointerAdapter(OutPointer<T, TDeleter> & uniquePointer)
{
	return SmartPointerAdapter<OutPointer<T, TDeleter>, T>(&uniquePointer);
}

// Macro allows to automatically use the pointer ref returned by get() while the adapter remains in scope
#define adaptSmartPointer( uniquePointer ) (makeSmartPointerAdapter(uniquePointer).get())
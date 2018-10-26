#pragma once

#include <iostream>                                                           
#include <memory>
using namespace std;

#include "Trace.h"

// Output pointer allows methods to accept both plain pointer and unique pointer references
// for the purpuse of returning a newly allocated.
//
// This is useful only if legacy code already calls the method with plain pointer reference.
// New code should use unique pointers exclusively.
// 
// For example 
// bool legacy( int * intOut )
// can be rewritten as 
// bool legacy( OutputPointer<int> intOut )
//
// This concept can be extended to other types of smart pointers.
template<typename T, typename TDeleter = default_delete>
class OutputPointer
{
private:

	enum class PointerType
	{
		PLAIN,
		UNIQUE,
	};

	union Pointer
	{
		unique_ptr<T, TDeleter> * unique;
		T ** plain;
	};

	PointerType type;
	Pointer pointer;
public:
	
	OutputPointer(T *& value)
		: type(PointerType::PLAIN)
	{
		TRACE;
		pointer.plain = &value;
	}

	OutputPointer(unique_ptr<T, TDeleter> & value)
		: type(PointerType::UNIQUE)
	{
		TRACE;
		pointer.unique = &value;
	}
	
	// Default copy-constructor would be generated with const argument.
	// While the argument itself is not going to be changed, the reset() operation is considered
	// non-const and has the same effect as if it was performed on the original OutputPointer directly.
	OutputPointer(OutputPointer & outPointer)
		: type(outPointer.type), pointer(outPointer.pointer)
	{
		TRACE;
	}

	void reset(T * value)
	{
		TRACE;
		Trace::indent();
		cout << "propagating " << value << endl;
		switch (type)
		{
		case PointerType::PLAIN:
			if (*pointer.plain != nullptr)
			{
				TDeleter()(*pointer.plain); // This means deleter has to be default-constructible.
			}
			*pointer.plain = value;
			break;
		case PointerType::UNIQUE:
			pointer.unique->reset(value);
			break;
		default:
			throw logic_error("Invalid type.");
		}
	}

	const T * get() const
	{
		TRACE;
		switch (type)
		{
		case PointerType::PLAIN:
			return *pointer.plain;
		case PointerType::UNIQUE:
			return pointer.unique->get();
		default:
			throw logic_error("Invalid type.");
		}
	}

	T * get()
	{
		TRACE;
		return const_cast<T *>( std::as_const(*this).get() );
	}

	// The following methods are mostly usefull for
	// backward-compatibility of old method code.
	
	OutputPointer & operator=(T * value)
	{
		TRACE;
		reset(value);
		return *this;
	}

	bool operator==(void * ptr) const
	{
		TRACE;
		return get() == ptr;
	}

	bool operator!=(void * ptr) const
	{
		TRACE;
		return get() != ptr;
	}

	const T * operator->() const
	{
		TRACE;
		return get();
	}

	T * operator->()
	{
		TRACE;
		return get();
	}

	const T & operator*() const
	{
		TRACE;
		return *get();
	}

	T & operator*()
	{
		TRACE;
		return *get();
	}

private:
	void operator=(OutputPointer) = delete; // not sure what this should do, so disable it :)
};

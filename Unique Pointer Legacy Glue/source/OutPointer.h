#pragma once

#include <iostream>                                                           
#include <memory>
using namespace std;

template<typename T, typename TDeleter = default_delete>
class OutPointer
{
private:

	enum class PointerType
	{
		UNIQUE,
		PLAIN,
	};

	union Pointer
	{
		unique_ptr<T, TDeleter> * unique;
		T ** plain;
	};

	PointerType type;
	Pointer pointer;
public:
	
	OutPointer(unique_ptr<T, TDeleter> & value)
		: type( PointerType::UNIQUE )
	{
		pointer.unique = &value;
	}

	OutPointer(T *& value)
		: type(PointerType::PLAIN)
	{
		pointer.plain = &value;
	}

	// Not sure if default copy-constructor would be generated with const argument or not.
	// While the argument itself is not going to be changed, the set operation is considered
	// non-const and has the same effect as if it was performed on the argument directly.
	OutPointer(OutPointer & outPointer)
		: type(outPointer.type), pointer(outPointer.pointer)
	{
	}

	OutPointer & operator=(T * value)
	{
		switch (type)
		{
		case PointerType::UNIQUE:
			pointer.unique->reset(value);
			break;
		case PointerType::PLAIN:
			if (*pointer.plain != nullptr)
			{
				TDeleter()(*pointer.plain);
			}
			*pointer.plain = value;
			break;
		}

		return *this;
	}

	void reset(T * value)
	{
		*this = value;
	}

	bool operator==(void * ptr) const
	{
		return get() == ptr;
	}

	bool operator!=(void * ptr) const
	{
		return get() != ptr;
	}

	const T * get() const
	{
		switch (type)
		{
		case PointerType::UNIQUE:
			return pointer.unique->get();
		case PointerType::PLAIN:
			return *pointer.plain;
		}
	}

	T * get()
	{
		switch (type)
		{
		case PointerType::UNIQUE:
			return pointer.unique->get();
		case PointerType::PLAIN:
			return *pointer.plain;
		}
	}

	const T * operator->() const
	{
		return get();
	}

	T * operator->()
	{
		return get();
	}

	const T & operator*() const
	{
		return *get();
	}

	T & operator*()
	{
		return *get();
	}
private:
	void operator=(OutPointer) = delete; // not sure what this should do, so disable it :)
};


#pragma once
#include "Trace.h"

class Destroyable
{
public:
	static size_t aliveInstanceCount;

	Destroyable()
	{
		++aliveInstanceCount;
		TRACEOBJ;
	}

	bool init() 
	{
		TRACEOBJ;
		return true;
	}

	virtual void destroy() 
	{
		TRACEOBJ;
		delete this; 
	}

	bool doStuff()
	{
		TRACEOBJ;
		return true;
	}
private:
	virtual ~Destroyable() 
	{
		--aliveInstanceCount;
		TRACEOBJ;
	}
};

class DestroyDeleter
{
public:
	template<class T>
	void operator()(T * ptr)
	{
		TRACE;
		if (ptr != nullptr)
		{
			ptr->destroy();
		}
	}
};
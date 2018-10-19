
#pragma once

class Destroyable
{
public:
	bool init(bool shouldSucceed) 
	{
		return shouldSucceed;
	}

	void destroy() 
	{
		delete this; 
	}

	bool doStuff(bool shouldSucceed)
	{
		return shouldSucceed;
	}
private:
	~Destroyable() {}
};

class DestroyDeleter
{
public:
	template<class T>
	void operator()(T * ptr)
	{
		if (ptr != nullptr)
		{
			ptr->destroy();
		}
	}
};
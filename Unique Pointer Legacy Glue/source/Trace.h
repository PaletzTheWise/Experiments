
#pragma once

#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class Trace
{
protected:
	static int depth;
	string name;

public:

	Trace(const string & name) : name(name)
	{
		indent();
		cout << "+" << name << endl;
		++depth;
	}

	~Trace()
	{
		--depth;
		indent();
		cout << "-" << name << endl;
	}

	static void indent()
	{
		cout << string(2 * depth, ' ');
	}

	static string addressToString(void * address)
	{
		stringstream ss;
		ss << address;
		return ss.str();
	}
};


#define TRACE Trace trace(__FUNCTION__);
#define TRACEOBJ Trace trace(string() + __FUNCTION__ + "    " + Trace::addressToString(this));
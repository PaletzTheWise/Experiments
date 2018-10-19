#include <iostream>
#include <string>
using namespace std;

#include "typestring.hh" // https://github.com/irrequietus/typestring

// Stage 1: Combining a string and a name

void stage1()
{
	cout << "Stage 1" << endl;
	irqus::typestring<'a', 'b', 'c'> abc;
	cout << abc.data() << endl;	
	
	//irqus::typestring<'a', 'b', 'd'> * abdPtr = &abc; // Error C2440 'initializing': cannot convert from 'irqus::typestring<97,98,99> *' to 'irqus::typestring<97,98,100> *'	Named Parameters	e : \workshop\coding\shared\rnd\named parameters\src\namedparameters1.cpp	14
	typestring_is("abd") abd; //irqus::typestring<'a', 'b', 'd'> abd;
	cout << abd.data() << endl;
	//typestring_is("abe") * abePtr = &abd; // Error	C2440	'initializing': cannot convert from 'irqus::typestring<97,98,100> *' to 'irqus::typestring<97,98,101> *'	Named Parameters	e : \workshop\coding\shared\rnd\named parameters\src\namedparameters1.cpp	17
}
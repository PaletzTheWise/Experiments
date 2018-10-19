#include <iostream>
#include <string>
using namespace std;

// Stage 2: Pairing name and value

#include "NamedValue.h"

void stage2()
{
	cout << "Stage 2" << endl;
	NamedValue< typestring_is("abc"), int > abc( 0 );
	cout << abc.getName() << endl;
	//NamedValue< int, int > fail(0); // Error C2338 TName template argument must be irqus::typestring.Named Parameters	e : \workshop\coding\shared\rnd\named parameters\src\namedvalue.h	7
	//NamedValue< typestring_is("abd"), int > * abdPtr = &abc; // Error	C2440	'initializing': cannot convert from 'NamedValue<irqus::typestring<97,98,99>,int> *' to 'NamedValue<irqus::typestring<97,98,100>,int> *'	Named Parameters	e : \workshop\coding\shared\rnd\named parameters\src\namedparameters2.cpp	17
}


#include <iostream>     
#include <memory>
using namespace std;
#include "Destroyable.h"

int Trace::depth = 0;
size_t Destroyable::aliveInstanceCount = 0;

void argumentGlue();
void superGlue();
void callSiteGlue();

int main()
{
	cout << endl << "Argument Glue" << endl << endl;
	argumentGlue();

	cout << endl << "Call Site Glue" << endl << endl;
	callSiteGlue();
	
	cout << endl << "Super Glue" << endl << endl;
	superGlue();

	cout << endl << "There should be zero Destroyable instances left: " << Destroyable::aliveInstanceCount << endl << endl;
}

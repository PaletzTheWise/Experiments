#include <iostream>
using namespace std;

void motivation();
void stage1();
void stage2();
void stage3();
void stage4();
void stage5();
void stage6();
void stage7();
void stage8();

#ifdef _MSC_VER
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char** argv)
#endif
{
	motivation();
	cout << endl << endl;
	stage1();
	cout << endl << endl;
	stage2();
	cout << endl << endl;
	stage3();
	cout << endl << endl;
	stage4();
	cout << endl << endl;
	stage5();
	cout << endl << endl;
	stage6();
	cout << endl << endl;
	stage7();
	cout << endl << endl;
	stage8();

    return 0;
}
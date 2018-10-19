
#include <string>
#include <iostream>
#include <vector>
using namespace std;

static bool readBooleanFromRegistry( const wstring & name, bool defaultValue, bool throwIfNotExists = false, bool writeIfNotExists = true, bool caseSensitive = true )
{
	// look up the registry value
	return true;
}

void motivation()
{
	bool godModeEnabled = readBooleanFromRegistry( L"GodMode", false, true, true, false );
	#ifdef what_if_we_could_write
		bool godModeEnabled = readBooleanFromRegistry( L"GodMode", throwIfNotExists : true, defaultValue : false, caseSensitive : false );
		// or
		bool godModeEnabled = readBooleanFromRegistry(L"GodMode", NV( throwIfNotExists, true), NV( defaultValue, false ), NV( caseSensitive, false ) );
	#endif
}
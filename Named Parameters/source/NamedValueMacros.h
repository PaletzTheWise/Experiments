#pragma once

#include "NamedValue.h"

template<class TName, class TPayload> static NamedValue<TName, TPayload> MakeNamedValue(TPayload value)
{
	return NamedValue<TName, TPayload>(value);
};

#define NV( name, value ) MakeNamedValue<typestring_is(#name)>( value )

#define NamedParam( type, name ) NamedValue<typestring_is(#name), type> name
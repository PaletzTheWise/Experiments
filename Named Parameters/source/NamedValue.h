#pragma once

#include "typestring.hh" // https://github.com/irrequietus/typestring
#include <type_traits>

template<class TName, class TPayload> class NamedValue
{
public:

	NamedValue(const TPayload & payload) 
	{
		static_assert(!std::is_same<TPayload, TPayload>::value, "TName template argument must be irqus::typestring.");
	}

	TPayload & operator*() { return *static_cast<TPayload*>(nullptr); }

	const char * getName() { return ""; }
};

template<class TPayload, char... C> class NamedValue< irqus::typestring<C...>, TPayload>
{
	TPayload payload;
public:
	typedef TPayload Payload_type;
	typedef irqus::typestring<C...> Name_type;

	NamedValue(const TPayload & payload) : payload(payload)
	{
	}

	TPayload & operator*()
	{
		return payload;
	}

	const char * getName()
	{
		return irqus::typestring<C...>::data();
	}
};

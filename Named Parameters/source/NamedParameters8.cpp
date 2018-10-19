#include <iostream>
#include <string>
#include <memory>
using namespace std;

#include "NamedValueMacros.h"
#include "CompileTimeList.h"

static wstring toString(const unique_ptr<bool> & value)
{
	if (value.get() != NULL)
	{
		return (*value ? L"true" : L"false");
	}
	else
	{
		return L"null";
	}
}

// Stage 8: Make named parameters functions easy to write

template<bool isRequired, typename TSpecificRequiredParameterChecker>
class RequiredParameterChecker
{
public:
	static void run()
	{
	}
};

template<typename TSpecificRequiredParameterChecker>
class RequiredParameterChecker<true, TSpecificRequiredParameterChecker>
{
public:
	static void run()
	{
		TSpecificRequiredParameterChecker::required();
	}
};

template<
	bool p1Set = false,
	bool p2Set = false,
	bool p3Set = false,
	bool p4Set = false,
	bool p5Set = false,
	bool p6Set = false,
	bool p7Set = false,
	bool p8Set = false,
	bool p9Set = false,
	bool p10Set = false,
	bool p11Set = false,
	bool p12Set = false,
	bool p13Set = false,
	bool p14Set = false,
	bool p15Set = false
>
class ParameterAvailability
{
public:
	typedef ParameterAvailability<
		true, 
		p2Set,
		p3Set,
		p4Set,
		p5Set,
		p6Set,
		p7Set,
		p8Set,
		p9Set,
		p10Set,
		p11Set,
		p12Set,
		p13Set,
		p14Set,
		p15Set
	> WithP1Set;
	typedef ParameterAvailability<
		p1Set,
		true,
		p3Set,
		p4Set,
		p5Set,
		p6Set,
		p7Set,
		p8Set,
		p9Set,
		p10Set,
		p11Set,
		p12Set,
		p13Set,
		p14Set,
		p15Set
	> WithP2Set;
	typedef ParameterAvailability<
		p1Set,
		p2Set,
		true,
		p4Set,
		p5Set,
		p6Set,
		p7Set,
		p8Set,
		p9Set,
		p10Set,
		p11Set,
		p12Set,
		p13Set,
		p14Set,
		p15Set
	> WithP3Set;
	typedef ParameterAvailability<
		p1Set,
		p2Set,
		p3Set,
		true,
		p5Set,
		p6Set,
		p7Set,
		p8Set,
		p9Set,
		p10Set,
		p11Set,
		p12Set,
		p13Set,
		p14Set,
		p15Set
	> WithP4Set;
	typedef ParameterAvailability<
		p1Set,
		p2Set,
		p3Set,
		p4Set,
		true,
		p6Set,
		p7Set,
		p8Set,
		p9Set,
		p10Set,
		p11Set,
		p12Set,
		p13Set,
		p14Set,
		p15Set
	> WithP5Set;
	typedef ParameterAvailability<
		p1Set,
		p2Set,
		p3Set,
		p4Set,
		p5Set,
		true,
		p7Set,
		p8Set,
		p9Set,
		p10Set,
		p11Set,
		p12Set,
		p13Set,
		p14Set,
		p15Set
	> WithP6Set;
	typedef ParameterAvailability<
		p1Set,
		p2Set,
		p3Set,
		p4Set,
		p5Set,
		p6Set,
		true,
		p8Set,
		p9Set,
		p10Set,
		p11Set,
		p12Set,
		p13Set,
		p14Set,
		p15Set
	> WithP7Set;
	typedef ParameterAvailability<
		p1Set,
		p2Set,
		p3Set,
		p4Set,
		p5Set,
		p6Set,
		p7Set,
		true,
		p9Set,
		p10Set,
		p11Set,
		p12Set,
		p13Set,
		p14Set,
		p15Set
	> WithP8Set;
	typedef ParameterAvailability<
		p1Set,
		p2Set,
		p3Set,
		p4Set,
		p5Set,
		p6Set,
		p7Set,
		p8Set,
		true,
		p10Set,
		p11Set,
		p12Set,
		p13Set,
		p14Set,
		p15Set
	> WithP9Set;
	typedef ParameterAvailability<
		p1Set,
		p2Set,
		p3Set,
		p4Set,
		p5Set,
		p6Set,
		p7Set,
		p8Set,
		p9Set,
		true,
		p11Set,
		p12Set,
		p13Set,
		p14Set,
		p15Set
	> WithP10Set;
	typedef ParameterAvailability<
		p1Set,
		p2Set,
		p3Set,
		p4Set,
		p5Set,
		p6Set,
		p7Set,
		p8Set,
		p9Set,
		p10Set,
		true,
		p12Set,
		p13Set,
		p14Set,
		p15Set
	> WithP11Set;
	typedef ParameterAvailability<
		p1Set,
		p2Set,
		p3Set,
		p4Set,
		p5Set,
		p6Set,
		p7Set,
		p8Set,
		p9Set,
		p10Set,
		p11Set,
		true,
		p13Set,
		p14Set,
		p15Set
	> WithP12Set;
	typedef ParameterAvailability<
		p1Set,
		p2Set,
		p3Set,
		p4Set,
		p5Set,
		p6Set,
		p7Set,
		p8Set,
		p9Set,
		p10Set,
		p11Set,
		p12Set,
		true,
		p14Set,
		p15Set
	> WithP13Set;
	typedef ParameterAvailability<
		p1Set,
		p2Set,
		p3Set,
		p4Set,
		p5Set,
		p6Set,
		p7Set,
		p8Set,
		p9Set,
		p10Set,
		p11Set,
		p12Set,
		p13Set,
		true,
		p15Set
	> WithP14Set;
	typedef ParameterAvailability<
		p1Set,
		p2Set,
		p3Set,
		p4Set,
		p5Set,
		p6Set,
		p7Set,
		p8Set,
		p9Set,
		p10Set,
		p11Set,
		p12Set,
		p13Set,
		p14Set,
		true
	> WithP15Set;

	static void p1SingleAssignmentCheck()
	{
		static_assert(!p1Set, "Multiple values for Parameter 1.");
	}

	static void p2SingleAssignmentCheck()
	{
		static_assert(!p2Set, "Multiple values for Parameter 2.");
	}

	static void p3SingleAssignmentCheck()
	{
		static_assert(!p3Set, "Multiple values for Parameter 3.");
	}

	static void p4SingleAssignmentCheck()
	{
		static_assert(!p4Set, "Multiple values for Parameter 4.");
	}

	static void p5SingleAssignmentCheck()
	{
		static_assert(!p5Set, "Multiple values for Parameter 5.");
	}

	static void p6SingleAssignmentCheck()
	{
		static_assert(!p6Set, "Multiple values for Parameter 6.");
	}

	static void p7SingleAssignmentCheck()
	{
		static_assert(!p7Set, "Multiple values for Parameter 7.");
	}

	static void p8SingleAssignmentCheck()
	{
		static_assert(!p8Set, "Multiple values for Parameter 8.");
	}

	static void p9SingleAssignmentCheck()
	{
		static_assert(!p9Set, "Multiple values for Parameter 9.");
	}

	static void p10SingleAssignmentCheck()
	{
		static_assert(!p10Set, "Multiple values for Parameter 10.");
	}

	static void p11SingleAssignmentCheck()
	{
		static_assert(!p11Set, "Multiple values for Parameter 11.");
	}

	static void p12SingleAssignmentCheck()
	{
		static_assert(!p12Set, "Multiple values for Parameter 12.");
	}

	static void p13SingleAssignmentCheck()
	{
		static_assert(!p13Set, "Multiple values for Parameter 13.");
	}

	static void p14SingleAssignmentCheck()
	{
		static_assert(!p14Set, "Multiple values for Parameter 14.");
	}

	static void p15SingleAssignmentCheck()
	{
		static_assert(!p15Set, "Multiple values for Parameter 15.");
	}

	class P1RequiredParameterChecker {
	public:
		static void required()
		{
			static_assert(p1Set, "Required Parameter 1 not provided.");
		}
	};

	class P2RequiredParameterChecker {
	public:
		static void required()
		{
			static_assert(p2Set, "Required Parameter 2 not provided.");
		}
	};

	class P3RequiredParameterChecker {
	public:
		static void required()
		{
			static_assert(p3Set, "Required Parameter 3 not provided.");
		}
	};

	class P4RequiredParameterChecker {
	public:
		static void required()
		{
			static_assert(p4Set, "Required Parameter 4 not provided.");
		}
	};

	class P5RequiredParameterChecker {
	public:
		static void required()
		{
			static_assert(p5Set, "Required Parameter 5 not provided.");
		}
	};

	class P6RequiredParameterChecker {
	public:
		static void required()
		{
			static_assert(p6Set, "Required Parameter 6 not provided.");
		}
	};

	class P7RequiredParameterChecker {
	public:
		static void required()
		{
			static_assert(p7Set, "Required Parameter 7 not provided.");
		}
	};

	class P8RequiredParameterChecker {
	public:
		static void required()
		{
			static_assert(p8Set, "Required Parameter 8 not provided.");
		}
	};

	class P9RequiredParameterChecker {
	public:
		static void required()
		{
			static_assert(p9Set, "Required Parameter 9 not provided.");
		}
	};

	class P10RequiredParameterChecker {
	public:
		static void required()
		{
			static_assert(p10Set, "Required Parameter 10 not provided.");
		}
	};

	class P11RequiredParameterChecker {
	public:
		static void required()
		{
			static_assert(p11Set, "Required Parameter 11 not provided.");
		}
	};

	class P12RequiredParameterChecker {
	public:
		static void required()
		{
			static_assert(p12Set, "Required Parameter 12 not provided.");
		}
	};

	class P13RequiredParameterChecker {
	public:
		static void required()
		{
			static_assert(p13Set, "Required Parameter 13 not provided.");
		}
	};

	class P14RequiredParameterChecker {
	public:
		static void required()
		{
			static_assert(p14Set, "Required Parameter 14 not provided.");
		}
	};

	class P15RequiredParameterChecker {
	public:
		static void required()
		{
			static_assert(p15Set, "Required Parameter 15 not provided.");
		}
	};
};

template<class TName, class TPayload, bool TIsRequired = false>
class NamedParameterDeclaration
{
public:
	typedef NamedValue<TName, TPayload> NamedValue_type;
	typedef TName Name_type;
	typedef TPayload Payload_type;
	static const bool isRequired = TIsRequired;
};

class UnusedParameter
{
public:
	typedef UnusedParameter NamedValue_type;
	typedef UnusedParameter Payload_type;
	static const bool isRequired = false;
};

template<
	class TParameter1Declaration = UnusedParameter,
	class TParameter2Declaration = UnusedParameter,
	class TParameter3Declaration = UnusedParameter,
	class TParameter4Declaration = UnusedParameter,
	class TParameter5Declaration = UnusedParameter,
	class TParameter6Declaration = UnusedParameter,
	class TParameter7Declaration = UnusedParameter,
	class TParameter8Declaration = UnusedParameter,
	class TParameter9Declaration = UnusedParameter,
	class TParameter10Declaration = UnusedParameter,
	class TParameter11Declaration = UnusedParameter,
	class TParameter12Declaration = UnusedParameter,
	class TParameter13Declaration = UnusedParameter,
	class TParameter14Declaration = UnusedParameter,
	class TParameter15Declaration = UnusedParameter
>
class NamedParameterFunction
{
	class ParameterStructure
	{
	public:
		unique_ptr<typename TParameter1Declaration::Payload_type> p1;
		unique_ptr<typename TParameter2Declaration::Payload_type> p2;
		unique_ptr<typename TParameter3Declaration::Payload_type> p3;
		unique_ptr<typename TParameter4Declaration::Payload_type> p4;
		unique_ptr<typename TParameter5Declaration::Payload_type> p5;
		unique_ptr<typename TParameter6Declaration::Payload_type> p6;
		unique_ptr<typename TParameter7Declaration::Payload_type> p7;
		unique_ptr<typename TParameter8Declaration::Payload_type> p8;
		unique_ptr<typename TParameter9Declaration::Payload_type> p9;
		unique_ptr<typename TParameter10Declaration::Payload_type> p10;
		unique_ptr<typename TParameter11Declaration::Payload_type> p11;
		unique_ptr<typename TParameter12Declaration::Payload_type> p12;
		unique_ptr<typename TParameter13Declaration::Payload_type> p13;
		unique_ptr<typename TParameter14Declaration::Payload_type> p14;
		unique_ptr<typename TParameter15Declaration::Payload_type> p15;
	};

	// Fallback if list is not a CTL
	template<class TParameterAvailability, class TList>
	class ParamCtlToStruct
	{
	public:
		static bool run(TList list, ParameterStructure & params)
		{
			static_assert(!std::is_same<TList, TList>::value, "NamedParameterFunction::ParamCtlToStruct::run(): List must be a CompileTimeList of NamedValue<name,value> or EmptyCompileTimeList.");
		}
	};

	// Fallback if CTL head is not recognized
	template<class TParameterAvailability, class THead, class TTail>
	class ParamCtlToStruct<TParameterAvailability, CompileTimeList< THead, TTail> >
	{
	public:
		static void run(CompileTimeList< THead, TTail> list, ParameterStructure & params)
		{
			static_assert(!std::is_same<THead, THead>::value, "NamedParameterFunction::ParamCtlToStruct::run(): Invalid argument provided.");
		}
	};

	// when all parameters have been extracted from CompileTimeList
	template<class TParameterAvailability>
	class ParamCtlToStruct<TParameterAvailability, EmptyCompileTimeList >
	{
	public:
		typedef EmptyCompileTimeList TList;

		static void run(TList list, ParameterStructure & params)
		{
			RequiredParameterChecker<TParameter1Declaration::isRequired, typename TParameterAvailability::P1RequiredParameterChecker>::run();
			RequiredParameterChecker<TParameter2Declaration::isRequired, typename TParameterAvailability::P2RequiredParameterChecker>::run();
			RequiredParameterChecker<TParameter3Declaration::isRequired, typename TParameterAvailability::P3RequiredParameterChecker>::run();
			RequiredParameterChecker<TParameter4Declaration::isRequired, typename TParameterAvailability::P4RequiredParameterChecker>::run();
			RequiredParameterChecker<TParameter5Declaration::isRequired, typename TParameterAvailability::P5RequiredParameterChecker>::run();
			RequiredParameterChecker<TParameter6Declaration::isRequired, typename TParameterAvailability::P6RequiredParameterChecker>::run();
			RequiredParameterChecker<TParameter7Declaration::isRequired, typename TParameterAvailability::P7RequiredParameterChecker>::run();
			RequiredParameterChecker<TParameter8Declaration::isRequired, typename TParameterAvailability::P8RequiredParameterChecker>::run();
			RequiredParameterChecker<TParameter9Declaration::isRequired, typename TParameterAvailability::P9RequiredParameterChecker>::run();
			RequiredParameterChecker<TParameter10Declaration::isRequired, typename TParameterAvailability::P10RequiredParameterChecker>::run();
			RequiredParameterChecker<TParameter11Declaration::isRequired, typename TParameterAvailability::P11RequiredParameterChecker>::run();
			RequiredParameterChecker<TParameter12Declaration::isRequired, typename TParameterAvailability::P12RequiredParameterChecker>::run();
			RequiredParameterChecker<TParameter13Declaration::isRequired, typename TParameterAvailability::P13RequiredParameterChecker>::run();
			RequiredParameterChecker<TParameter14Declaration::isRequired, typename TParameterAvailability::P14RequiredParameterChecker>::run();
			RequiredParameterChecker<TParameter15Declaration::isRequired, typename TParameterAvailability::P15RequiredParameterChecker>::run();
		}
	};

	// specialization for each recognized name/type
	
	template<class TParameterAvailability, class TTail>
	class ParamCtlToStruct<TParameterAvailability, CompileTimeList< typename TParameter1Declaration::NamedValue_type, TTail> >
	{
	public:
		typedef CompileTimeList< typename TParameter1Declaration::NamedValue_type, TTail> TList;
		typedef typename TParameter1Declaration::Payload_type Payload_type;

		static void run(TList list, ParameterStructure & params)
		{
			TParameterAvailability::p1SingleAssignmentCheck();
			params.p1.reset(new Payload_type(*(list.head)));
			ParamCtlToStruct<typename TParameterAvailability::WithP1Set, typename TList::TTail>::run(list.tail, params);
		}
	};
	
	template<class TParameterAvailability, class TTail>
	class ParamCtlToStruct<TParameterAvailability, CompileTimeList< typename TParameter2Declaration::NamedValue_type, TTail> >
	{
	public:
		typedef CompileTimeList< typename TParameter2Declaration::NamedValue_type, TTail> TList;
		typedef typename TParameter2Declaration::Payload_type Payload_type;

		static void run(TList list, ParameterStructure & params)
		{
			TParameterAvailability::p2SingleAssignmentCheck();
			params.p2.reset(new Payload_type(*(list.head)));
			ParamCtlToStruct<typename TParameterAvailability::WithP2Set, typename TList::TTail>::run(list.tail, params);
		}
	};
	
	template<class TParameterAvailability, class TTail>
	class ParamCtlToStruct<TParameterAvailability, CompileTimeList< typename TParameter3Declaration::NamedValue_type, TTail> >
	{
	public:
		typedef CompileTimeList< typename TParameter3Declaration::NamedValue_type, TTail> TList;
		typedef typename TParameter3Declaration::Payload_type Payload_type;

		static void run(TList list, ParameterStructure & params)
		{
			TParameterAvailability::p3SingleAssignmentCheck();
			params.p3.reset(new Payload_type(*(list.head)));
			ParamCtlToStruct<typename TParameterAvailability::WithP3Set, typename TList::TTail>::run(list.tail, params);
		}
	};
	
	template<class TParameterAvailability, class TTail>
	class ParamCtlToStruct<TParameterAvailability, CompileTimeList< typename TParameter4Declaration::NamedValue_type, TTail> >
	{
	public:
		typedef CompileTimeList< typename TParameter4Declaration::NamedValue_type, TTail> TList;
		typedef typename TParameter4Declaration::Payload_type Payload_type;

		static void run(TList list, ParameterStructure & params)
		{
			TParameterAvailability::p4SingleAssignmentCheck();
			params.p4.reset(new Payload_type(*(list.head)));
			ParamCtlToStruct<typename TParameterAvailability::WithP4Set, typename TList::TTail>::run(list.tail, params);
		}
	};
	
	template<class TParameterAvailability, class TTail>
	class ParamCtlToStruct<TParameterAvailability, CompileTimeList< typename TParameter5Declaration::NamedValue_type, TTail> >
	{
	public:
		typedef CompileTimeList< typename TParameter5Declaration::NamedValue_type, TTail> TList;
		typedef typename TParameter5Declaration::Payload_type Payload_type;

		static void run(TList list, ParameterStructure & params)
		{
			TParameterAvailability::p5SingleAssignmentCheck();
			params.p5.reset(new Payload_type(*(list.head)));
			ParamCtlToStruct<typename TParameterAvailability::WithP5Set, typename TList::TTail>::run(list.tail, params);
		}
	};
	
	template<class TParameterAvailability, class TTail>
	class ParamCtlToStruct<TParameterAvailability, CompileTimeList< typename TParameter6Declaration::NamedValue_type, TTail> >
	{
	public:
		typedef CompileTimeList< typename TParameter6Declaration::NamedValue_type, TTail> TList;
		typedef typename TParameter6Declaration::Payload_type Payload_type;

		static void run(TList list, ParameterStructure & params)
		{
			TParameterAvailability::p6SingleAssignmentCheck();
			params.p6.reset(new Payload_type(*(list.head)));
			ParamCtlToStruct<typename TParameterAvailability::WithP6Set, typename TList::TTail>::run(list.tail, params);
		}
	};

	template<class TParameterAvailability, class TTail>
	class ParamCtlToStruct<TParameterAvailability, CompileTimeList< typename TParameter7Declaration::NamedValue_type, TTail> >
	{
	public:
		typedef CompileTimeList< typename TParameter7Declaration::NamedValue_type, TTail> TList;
		typedef typename TParameter7Declaration::Payload_type Payload_type;

		static void run(TList list, ParameterStructure & params)
		{
			TParameterAvailability::p7SingleAssignmentCheck();
			params.p7.reset(new Payload_type(*(list.head)));
			ParamCtlToStruct<typename TParameterAvailability::WithP7Set, typename TList::TTail>::run(list.tail, params);
		}
	};

	template<class TParameterAvailability, class TTail>
	class ParamCtlToStruct<TParameterAvailability, CompileTimeList< typename TParameter8Declaration::NamedValue_type, TTail> >
	{
	public:
		typedef CompileTimeList< typename TParameter8Declaration::NamedValue_type, TTail> TList;
		typedef typename TParameter8Declaration::Payload_type Payload_type;

		static void run(TList list, ParameterStructure & params)
		{
			TParameterAvailability::p8SingleAssignmentCheck();
			params.p8.reset(new Payload_type(*(list.head)));
			ParamCtlToStruct<typename TParameterAvailability::WithP8Set, typename TList::TTail>::run(list.tail, params);
		}
	};

	template<class TParameterAvailability, class TTail>
	class ParamCtlToStruct<TParameterAvailability, CompileTimeList< typename TParameter9Declaration::NamedValue_type, TTail> >
	{
	public:
		typedef CompileTimeList< typename TParameter9Declaration::NamedValue_type, TTail> TList;
		typedef typename TParameter9Declaration::Payload_type Payload_type;

		static void run(TList list, ParameterStructure & params)
		{
			TParameterAvailability::p9SingleAssignmentCheck();
			params.p9.reset(new Payload_type(*(list.head)));
			ParamCtlToStruct<typename TParameterAvailability::WithP9Set, typename TList::TTail>::run(list.tail, params);
		}
	};

	template<class TParameterAvailability, class TTail>
	class ParamCtlToStruct<TParameterAvailability, CompileTimeList< typename TParameter10Declaration::NamedValue_type, TTail> >
	{
	public:
		typedef CompileTimeList< typename TParameter10Declaration::NamedValue_type, TTail> TList;
		typedef typename TParameter10Declaration::Payload_type Payload_type;

		static void run(TList list, ParameterStructure & params)
		{
			TParameterAvailability::p10SingleAssignmentCheck();
			params.p10.reset(new Payload_type(*(list.head)));
			ParamCtlToStruct<typename TParameterAvailability::WithP10Set, typename TList::TTail>::run(list.tail, params);
		}
	};

	template<class TParameterAvailability, class TTail>
	class ParamCtlToStruct<TParameterAvailability, CompileTimeList< typename TParameter11Declaration::NamedValue_type, TTail> >
	{
	public:
		typedef CompileTimeList< typename TParameter11Declaration::NamedValue_type, TTail> TList;
		typedef typename TParameter11Declaration::Payload_type Payload_type;

		static void run(TList list, ParameterStructure & params)
		{
			TParameterAvailability::p11SingleAssignmentCheck();
			params.p11.reset(new Payload_type(*(list.head)));
			ParamCtlToStruct<typename TParameterAvailability::WithP11Set, typename TList::TTail>::run(list.tail, params);
		}
	};

	template<class TParameterAvailability, class TTail>
	class ParamCtlToStruct<TParameterAvailability, CompileTimeList< typename TParameter12Declaration::NamedValue_type, TTail> >
	{
	public:
		typedef CompileTimeList< typename TParameter12Declaration::NamedValue_type, TTail> TList;
		typedef typename TParameter12Declaration::Payload_type Payload_type;

		static void run(TList list, ParameterStructure & params)
		{
			TParameterAvailability::p12SingleAssignmentCheck();
			params.p12.reset(new Payload_type(*(list.head)));
			ParamCtlToStruct<typename TParameterAvailability::WithP12Set, typename TList::TTail>::run(list.tail, params);
		}
	};

	template<class TParameterAvailability, class TTail>
	class ParamCtlToStruct<TParameterAvailability, CompileTimeList< typename TParameter13Declaration::NamedValue_type, TTail> >
	{
	public:
		typedef CompileTimeList< typename TParameter13Declaration::NamedValue_type, TTail> TList;
		typedef typename TParameter13Declaration::Payload_type Payload_type;

		static void run(TList list, ParameterStructure & params)
		{
			TParameterAvailability::p13SingleAssignmentCheck();
			params.p13.reset(new Payload_type(*(list.head)));
			ParamCtlToStruct<typename TParameterAvailability::WithP13Set, typename TList::TTail>::run(list.tail, params);
		}
	};

	template<class TParameterAvailability, class TTail>
	class ParamCtlToStruct<TParameterAvailability, CompileTimeList< typename TParameter14Declaration::NamedValue_type, TTail> >
	{
	public:
		typedef CompileTimeList< typename TParameter14Declaration::NamedValue_type, TTail> TList;
		typedef typename TParameter14Declaration::Payload_type Payload_type;

		static void run(TList list, ParameterStructure & params)
		{
			TParameterAvailability::p14SingleAssignmentCheck();
			params.p14.reset(new Payload_type(*(list.head)));
			ParamCtlToStruct<typename TParameterAvailability::WithP14Set, typename TList::TTail>::run(list.tail, params);
		}
	};

	template<class TParameterAvailability, class TTail>
	class ParamCtlToStruct<TParameterAvailability, CompileTimeList< typename TParameter15Declaration::NamedValue_type, TTail> >
	{
	public:
		typedef CompileTimeList< typename TParameter15Declaration::NamedValue_type, TTail> TList;
		typedef typename TParameter15Declaration::Payload_type Payload_type;

		static void run(TList list, ParameterStructure & params)
		{
			TParameterAvailability::p15SingleAssignmentCheck();
			params.p15.reset(new Payload_type(*(list.head)));
			ParamCtlToStruct<typename TParameterAvailability::WithP15Set, typename TList::TTail>::run(list.tail, params);
		}
	};
	
public:

	template<
		class T1 = IgnoredCtlElement *,
		class T2 = IgnoredCtlElement *,
		class T3 = IgnoredCtlElement *,
		class T4 = IgnoredCtlElement *,
		class T5 = IgnoredCtlElement *,
		class T6 = IgnoredCtlElement *,
		class T7 = IgnoredCtlElement *,
		class T8 = IgnoredCtlElement *,
		class T9 = IgnoredCtlElement *,
		class T10 = IgnoredCtlElement *,
		class T11 = IgnoredCtlElement *,
		class T12 = IgnoredCtlElement *,
		class T13 = IgnoredCtlElement *,
		class T14 = IgnoredCtlElement *,
		class T15 = IgnoredCtlElement *
	>
	static ParameterStructure ParamsToStructure(
			T1 p1 = nullptr,
			T2 p2 = nullptr,
			T3 p3 = nullptr,
			T4 p4 = nullptr,
			T5 p5 = nullptr,
			T6 p6 = nullptr,
			T7 p7 = nullptr,
			T8 p8 = nullptr,
			T9 p9 = nullptr,
			T10 p10 = nullptr,
			T11 p11 = nullptr,
			T12 p12 = nullptr,
			T13 p13 = nullptr,
			T14 p14 = nullptr,
			T15 p15 = nullptr
		)
	{
		auto paramCtl = MakeCtl(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p15);
		ParameterStructure retval;
		ParamCtlToStruct< ParameterAvailability<>, decltype(paramCtl) >::run(paramCtl, retval);
		return retval;
	}
};


#define NV_SIGNATURE_TEMPLATE_ARGS \
class T1 = IgnoredCtlElement *,\
class T2 = IgnoredCtlElement *,\
class T3 = IgnoredCtlElement *,\
class T4 = IgnoredCtlElement *,\
class T5 = IgnoredCtlElement *,\
class T6 = IgnoredCtlElement *,\
class T7 = IgnoredCtlElement *,\
class T8 = IgnoredCtlElement *,\
class T9 = IgnoredCtlElement *,\
class T10 = IgnoredCtlElement *,\
class T11 = IgnoredCtlElement *,\
class T12 = IgnoredCtlElement *,\
class T13 = IgnoredCtlElement *,\
class T14 = IgnoredCtlElement *,\
class T15 = IgnoredCtlElement *

#define NV_SIGNATURE_PARAMETERS \
T1 p1 = nullptr,\
T2 p2 = nullptr,\
T3 p3 = nullptr,\
T4 p4 = nullptr,\
T5 p5 = nullptr,\
T6 p6 = nullptr,\
T7 p7 = nullptr,\
T8 p8 = nullptr,\
T9 p9 = nullptr,\
T10 p10 = nullptr,\
T11 p11 = nullptr,\
T12 p12 = nullptr,\
T13 p13 = nullptr,\
T14 p14 = nullptr,\
T15 p15 = nullptr

#define NV_EXTRACT_PARAMETERS( \
	p1Name, p1Type, p1IsRequired, \
	p2Name, p2Type, p2IsRequired, \
	p3Name, p3Type, p3IsRequired, \
	p4Name, p4Type, p4IsRequired, \
	p5Name, p5Type, p5IsRequired, \
	p6Name, p6Type, p6IsRequired, \
	p7Name, p7Type, p7IsRequired, \
	p8Name, p8Type, p8IsRequired, \
	p9Name, p9Type, p9IsRequired, \
	p10Name, p10Type, p10IsRequired, \
	p11Name, p11Type, p11IsRequired, \
	p12Name, p12Type, p12IsRequired, \
	p13Name, p13Type, p13IsRequired, \
	p14Name, p14Type, p14IsRequired, \
	p15Name, p15Type, p15IsRequired \
) \
	unique_ptr<p1Type> p1Name; \
	unique_ptr<p2Type> p2Name; \
	unique_ptr<p3Type> p3Name; \
	unique_ptr<p4Type> p4Name; \
	{ \
		auto paramStruct = NamedParameterFunction< \
			NamedParameterDeclaration<typestring_is(#p1Name), p1Type, p1IsRequired>, \
			NamedParameterDeclaration<typestring_is(#p2Name), p2Type, p2IsRequired>, \
			NamedParameterDeclaration<typestring_is(#p3Name), p3Type, p3IsRequired>, \
			NamedParameterDeclaration<typestring_is(#p4Name), p4Type, p4IsRequired> \
		>::ParamsToStructure( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p15 ); \
		p1Name = move( paramStruct.p1 ); \
		p2Name = move( paramStruct.p2 ); \
		p3Name = move( paramStruct.p3 ); \
		p4Name = move( paramStruct.p4 ); \
	}


#define NV_EXTRACT_PARAMETERS4( \
	p1Name, p1Type, p1IsRequired, \
	p2Name, p2Type, p2IsRequired, \
	p3Name, p3Type, p3IsRequired, \
	p4Name, p4Type, p4IsRequired \
) \
NV_EXTRACT_PARAMETERS( \
	p1Name, p1Type, p1IsRequired, \
	p2Name, p2Type, p2IsRequired, \
	p3Name, p3Type, p3IsRequired, \
	p4Name, p4Type, p4IsRequired, \
	unusedNameParameter5, void *, false, \
	unusedNameParameter6, void *, false, \
	unusedNameParameter7, void *, false, \
	unusedNameParameter8, void *, false, \
	unusedNameParameter9, void *, false, \
	unusedNameParameter10, void *, false, \
	unusedNameParameter11, void *, false, \
	unusedNameParameter12, void *, false, \
	unusedNameParameter13, void *, false, \
	unusedNameParameter14, void *, false, \
	unusedNameParameter15, void *, false \
)

// user defined

template<NV_SIGNATURE_TEMPLATE_ARGS>
bool readBooleanFromRegistry( const wstring & name, NV_SIGNATURE_PARAMETERS)
{
	NV_EXTRACT_PARAMETERS4(
		defaultV, bool, true,
		doWrite, bool, false,
		caseSens, bool, false,
		doThrow, bool, false
	);
	
	wcout
		<< "readBooleanFromRegistry(" << endl
		<< "    name:     " << name << endl
		<< "    defaultV: " << toString(defaultV) << endl
		<< "    doWrite:  " << toString(doWrite) << endl
		<< "    caseSens: " << toString(caseSens) << endl
		<< "    doThrow:  " << toString(doThrow) << endl
		<< ")" << endl;
	// look up the registry value
	return true;
}

void stage8()
{
	cout << "Stage 8" << endl;

	readBooleanFromRegistry(L"godMode", NV(caseSens, true), NV(defaultV, false));// , NV(doWrite, false), NV(doThrow, true));
	//readBooleanFromRegistry(L"godMode", NV(caseSens, true) );// Error	C2338	Required Parameter 1 not provided.
}
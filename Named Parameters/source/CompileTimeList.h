#pragma once

#include <type_traits>

template<class THead, class TTail>
class CompileTimeList
{
public:
	THead head;
	TTail tail;

	CompileTimeList(THead head, TTail tail) : head(head), tail(tail)
	{
		static_assert(!std::is_same<THead,THead>::value, "CompileTimeList tail must be CompileTimeList or EmptyCompileTimeList.");
	}
};

class EmptyCompileTimeList
{
};

template<class THead, class TTailHead, class TTailTail>
class CompileTimeList<THead, CompileTimeList<TTailHead, TTailTail> >
{
public:
	typedef CompileTimeList<TTailHead, TTailTail> TTail;

	THead head;
	TTail tail;

	CompileTimeList(THead head, TTail tail) : head(head), tail(tail)
	{
	}
};

template<class THead>
class CompileTimeList<THead, EmptyCompileTimeList>
{
public:
	typedef EmptyCompileTimeList TTail;

	THead head;
	TTail tail;

	CompileTimeList(THead head, TTail tail) : head(head), tail(tail)
	{
	}
};

class IgnoredCtlElement
{
};

template<class TLeft, class TRight>
auto ConcatenateCtl(TLeft left, TRight right )
{
	return CompileTimeList<TLeft,TRight>( left, right );
}

template<class TLeft>
auto ConcatenateCtl(TLeft left)
{
	return CompileTimeList<TLeft, EmptyCompileTimeList>(left, EmptyCompileTimeList());
}

template<class TRight>
auto ConcatenateCtl(IgnoredCtlElement * ignoredLeft, TRight right)
{
	return right;
}

EmptyCompileTimeList ConcatenateCtl(IgnoredCtlElement * ignoredLeft, IgnoredCtlElement * ignoredRight);
EmptyCompileTimeList ConcatenateCtl(IgnoredCtlElement * ignoredLeft);

template<class TLeftHead, class TLeftTail, class TRightHead, class TRightTail>
auto ConcatenateCtl(CompileTimeList<TLeftHead, TLeftTail> left, CompileTimeList<TRightHead, TRightTail> right)
{
	ConcatenateCtl( left.head, ConcatenateCtl(left.tail, right) );
}

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
auto MakeCtl(
	T1 e1 = nullptr,
	T2 e2 = nullptr,
	T3 e3 = nullptr,
	T4 e4 = nullptr,
	T5 e5 = nullptr,
	T6 e6 = nullptr,
	T7 e7 = nullptr,
	T8 e8 = nullptr,
	T9 e9 = nullptr,
	T10 e10 = nullptr,
	T11 e11 = nullptr,
	T12 e12 = nullptr,
	T13 e13 = nullptr,
	T14 e14 = nullptr,
	T15 e15 = nullptr
)
{
	return (
		ConcatenateCtl(e1,
		 ConcatenateCtl(e2,
		  ConcatenateCtl(e3,
		   ConcatenateCtl(e4,
		    ConcatenateCtl(e5,
		     ConcatenateCtl(e6,
		      ConcatenateCtl(e7,
		       ConcatenateCtl(e8,
		        ConcatenateCtl(e9,
		         ConcatenateCtl(e10,
		          ConcatenateCtl(e11,
		           ConcatenateCtl(e12,
		            ConcatenateCtl(e13,
		             ConcatenateCtl(e14,
		              ConcatenateCtl(e15
		)))))))))))))))
	);
}
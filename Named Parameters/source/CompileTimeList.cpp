#include "CompileTimeList.h"

EmptyCompileTimeList ConcatenateCtl(IgnoredCtlElement * ignoredLeft, IgnoredCtlElement * ignoredRight)
{
	return EmptyCompileTimeList();
}

EmptyCompileTimeList ConcatenateCtl(IgnoredCtlElement * ignoredLeft)
{
	return EmptyCompileTimeList();
}
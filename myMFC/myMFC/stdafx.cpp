
// stdafx.cpp : 只包括标准包含文件的源文件
// myMFC.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"
#ifdef _MSC_VER // This check can be removed if you only build for Windows
#pragma warning (push)
#pragma warning (disable : 4005)
#include <safeint.h>
#include <stdint.h>
#pragma warning (default : 4005)
#pragma warning (pop)
#endif


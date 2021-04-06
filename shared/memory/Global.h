#pragma once

// ? Can this be done better?
//namespace {

#include <WinDef.h>

//}

namespace buffer_global {
	// Note that this represents only the low-order DWORD for the buffer size
	constexpr DWORD BUF_SIZE = 256;
	const TCHAR bufName[] = TEXT("Local\\IGCBuffer");
}
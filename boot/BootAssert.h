#pragma once

#define BootAssert(a) if (!(a)) {Print(L"ASSERT at: %s:%d\r\n", __FILEW__, __LINE__);}
#pragma once
// if is <a> is false then print a assert message
#define BootAssert(a) if (!(a)) {Print(L"ASSERT at: %s:%d\r\n", __FILEW__, __LINE__);}
#define BootAssert_Msg(a, b) if (!(a)) {Print(L"ASSERT at: %s:%d\r\n%s", __FILEW__, __LINE__, b);}
// same thing but if true
#define BootAssert_True(a) if (a) {Print(L"ASSERT at: %s:%d\r\n", __FILEW__, __LINE__);}
#define BootAssert_True_Msg(a, b) if (a) {Print(L"ASSERT at: %s:%d\r\n%s", __FILEW__, __LINE__, b);}
#pragma once

// misc 
#define EXTERNC extern "C"
#define NORETURN __declspec(noreturn)

typedef enum _MK2STATUS {
	MK2_SUCCESS,
	MK2_ERROR,
	MK2_UNSUPPORTED,
	MK2_NOTFOUND
} MK2STATUS;

enum KernelProperties {
	BaseAddress = 0xFFFF800001000000
};
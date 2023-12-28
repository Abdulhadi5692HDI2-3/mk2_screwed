#pragma once

#define _stop() while(1);

typedef enum _MK2_STATUS {
	OK,
	ERROR,
	UNSUPPORTED,
	UNINITALIZED
} MK2_STATUS;
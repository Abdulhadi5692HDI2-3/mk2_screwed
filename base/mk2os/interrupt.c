#ifndef _MSC_VER
#include <mk2/interrupts/interrupt.h>
#include <mk2/mk2krnlos.h>
#include <printf.h>
#endif
#ifdef _MSC_VER
#include "../inc/mk2/interrupts/interrupt.h"
#include "../inc/mk2/mk2krnlos.h"
#include "../../external/printf.h"
#endif


#ifndef _MSC_VER
__attribute__((interrupt)) void PageFault_Handler(struct interrupt_frame* frame) {
	printf("\r\nOHNO: Page fault happened\r\nHalting :( \r\n");
	_stop();
}
#endif
#ifdef _MSC_VER
// todo: usable interrupt handler in msvc
void PageFault_Handler(struct interrupt_frame* frame) {
	printf("\r\nOHNO: Page fault happened\r\nHalting :( \r\n");
	_stop();
}
#endif
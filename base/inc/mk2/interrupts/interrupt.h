#pragma once

#ifndef _MSC_VER
struct interrupt_frame;
__attribute__((interrupt)) void PageFault_Handler(struct interrupt_frame* frame);
#endif
#ifdef _MSC_VER
// TODO: implement for msvc
// for now no interrupt attribute
struct interrupt_frame;
void PageFault_Handler(struct interrupt_frame* frame);
#endif
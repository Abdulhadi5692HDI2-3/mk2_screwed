#pragma once

// the BOOTBOOT bootloader has already initalized the serial port for us.
// This is good as we don't need to fiddle around with the initalization
// We can send debug messages from the start

// reading from the serial port

// Should be used in a loop
// if returns 0 nothing has been received
// from the serial port.
int serial_received();

// reads a character from the serial port
char read_serial();

// writing to the serial port

int is_transmit_empty();

// writes a char to the serial port
void write_serial(char a);
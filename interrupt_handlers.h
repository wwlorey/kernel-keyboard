#pragma once
#include "screen.h"
#include "ps2.h"
#include "interrupt.h"

/* Print the scancode for a keyboard event to the screen */
void keypress(void* frame);

/* Print 'hi' to the screen */
void hi(void* frame);

/* Convert an array of hex chars to int */
int hex_to_int(const char* hex);

/* Return the charcter from kbdus at index. If caps is true, 
 * return uppercase (or the character itself if uppercase
 * is not valid). Otherwise return lowercase character. */
char get_char(const int index, const unsigned char caps);

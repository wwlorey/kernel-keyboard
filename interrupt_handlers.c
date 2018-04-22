#include "interrupt_handlers.h"
#include "kbdus.h"

char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};		

__attribute__((interrupt))
void keypress(void* frame)
{
  char buf[3];
  getScancodeByte(buf);

  // TODO: I think this is wrong...
  // If the scancode represents the END of a press, just make a newline
  if (buf[0] & 0x8)
    terminal_writestring("\n");
  else {
    // Translate hex digits from buffer into integer index
    int index = 0;
    index += (buf[0] - '0');
    index = index << 4;
    index += (buf[1] - '0');

    // Load the key value into a char array for writing to the screen
    char key_val[2] = {kbdus[index]};

    // Write the key value
    terminal_writestring(key_val);
  }

  // End the ISR (send end of interrupt)
  PIC_sendEOI(0x1);
}

__attribute__((interrupt))
void hi(void* frame)
{
  terminal_writestring("hi!\n");
}

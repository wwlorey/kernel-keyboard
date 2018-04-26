#include "interrupt_handlers.h"
#include "kbdus.h"

#define TRUE	0x01
#define FALSE	0x00

// Scancode lookup table credit: www.osdever.net/bkerndev/Docs/keyboard.htm
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
  static unsigned char caps = FALSE;
  static unsigned int caps_count = 0;
  
  char buf[3];
  getScancodeByte(buf);

  // Translate hex digits from buffer into integer index
  int index = hex_to_int(buf);
  
  // Deal with a key release scancode
  if (index & 0x80) {
    if ((caps_count >= 2 && caps && index == 186) || index == 170 || index == 182) { // The stopcode for caps has been seen, so disable it
      caps = FALSE;
      caps_count = 0;
    }
  }
  else {
    // Determine if CAPSLOCK or shift is pressed
    if (index == 58) { // CAPSLOCK
      caps = TRUE;
      caps_count += 1;
    } 

    if (index == 42 || index == 54) { // shift
      caps = TRUE;
    }

    // Load the key value into a char array for writing to the screen
    char key_val[2] = {get_char(index, caps)};
  
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

int hex_to_int(const char* hex) {
  unsigned int k;
  unsigned int digit = 0;
  int result = 0;

  // Convert the 2-digit hex number, digit by digit, to int
  for (k = 0; k < 2; k++) {
    if (hex[k] == '0')
	digit = 0;
    else if (hex[k] == '1') 
	digit = 1;
    else if (hex[k] == '2') 
	digit = 2;
    else if (hex[k] == '3') 
	digit = 3;
    else if (hex[k] == '4') 
	digit = 4;
    else if (hex[k] == '5') 
	digit = 5;
    else if (hex[k] == '6') 
	digit = 6;
    else if (hex[k] == '7') 
	digit = 7;
    else if (hex[k] == '8') 
	digit = 8;
    else if (hex[k] == '9') 
	digit = 9;
    else if (hex[k] == 'A') 
	digit = 10;
    else if (hex[k] == 'B') 
	digit = 11;
    else if (hex[k] == 'C') 
	digit = 12;
    else if (hex[k] == 'D') 
	digit = 13;
    else if (hex[k] == 'E') 
	digit = 14;
    else if (hex[k] == 'F') 
	digit = 15;

    // Shift the current contents of result left 4 bit-positions
    // to make room for incoming nibbles
    result = result << 4;
    result += digit;
  }

  return result;
}

char get_char(const int index, const unsigned char caps) {
  char ret = kbdus[index];
  
  // If CAPSLOCK or shift is engaged, capitalize letters/symbols
  if (caps) {
    if (ret == 'a')
      return 'A';
    else if (ret == 'b')
      return 'B';
    else if (ret == 'c')
      return 'C';
    else if (ret == 'd')
      return 'D';
    else if (ret == 'e')
      return 'E';
    else if (ret == 'f')
      return 'F';
    else if (ret == 'g')
      return 'G';
    else if (ret == 'h')
      return 'H';
    else if (ret == 'i')
      return 'I';
    else if (ret == 'j')
      return 'J';
    else if (ret == 'k')
      return 'K';
    else if (ret == 'l')
      return 'L';
    else if (ret == 'm')
      return 'M';
    else if (ret == 'n')
      return 'N';
    else if (ret == 'o')
      return 'O';
    else if (ret == 'p')
      return 'P';
    else if (ret == 'q')
      return 'Q';
    else if (ret == 'r')
      return 'R';
    else if (ret == 's')
      return 'S';
    else if (ret == 't')
      return 'T';
    else if (ret == 'u')
      return 'U';
    else if (ret == 'v')
      return 'V';
    else if (ret == 'w')
      return 'W';
    else if (ret == 'x')
      return 'X';
    else if (ret == 'y')
      return 'Y';
    else if (ret == 'z')
      return 'Z';
    else if (ret == '1')
      return '!';
    else if (ret == '2')
      return '@';
    else if (ret == '3')
      return '#';
    else if (ret == '4')
      return '$';
    else if (ret == '5')
      return '%';
    else if (ret == '6')
      return '^';
    else if (ret == '7')
      return '&';
    else if (ret == '8')
      return '*';
    else if (ret == '9')
      return '(';
    else if (ret == '0')
      return ')';
    else if (ret == '`')
      return '~';
    else if (ret == '-')
      return '_';
    else if (ret == '=')
      return '+';
    else if (ret == '[')
      return '{';
    else if (ret == ']')
      return '}';
    else if (ret == '\\')
      return '|';
    else if (ret == ';')
      return ':';
    else if (ret == '\'')
      return '"';
    else if (ret == ',')
      return '<';
    else if (ret == '.')
      return '>';
    else if (ret == '/')
      return '?';
  }
  
  // Otherwise, return the original character
  return ret;
}

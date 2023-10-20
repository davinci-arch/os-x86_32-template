#include "kernel/kernel.h"
#include "drivers/keyboard/keyboard.h"
#include "drivers/timer/timer.h"
#include "drivers/serial_port/serial_port.h"
#include "data/dataUtils.h"
#include "data/commandUtils.h"
#include "stringUtils/stringHandler.h";

#define lengthSignLine 4
#define startAddress 0xb8000
#define amountOfLine 25
#define amountOfColumn 80

char *currentAddress = (char *) startAddress;
// int currentRow = 1;
int cursorPosition = 2;

void resetParam();
void moveNextLine();

void exception_handler(u32 interrupt, u32 error, char *message) {
    serial_log(LOG_ERROR, message);
}

void init_kernel() {
    init_gdt();
    init_idt();
    init_exception_handlers();
    init_interrupt_handlers();
    register_timer_interrupt_handler();
    register_keyboard_interrupt_handler();
    configure_default_serial_port();
    set_exception_handler(exception_handler);
    enable_interrupts();
	clearTerminal((char*)startAddress, amountOfColumn, amountOfLine);
	resetParam();
	fillCommandStrucutre();
}

void resetParam() {

	// currentRow = 1;
	cursorPosition = lengthSignLine / 2;
	currentAddress = startAddress;
	put_cursor(cursorPosition);
	currentAddress += lengthSignLine;
}


/**
 * Puts cursors in a given position. For example, position = 20 would place it in
 * the first line 20th column, position = 80 will place in the first column of the second line.
 */
void put_cursor(unsigned short pos) {
    out(0x3D4, 14);
    out(0x3D5, ((pos >> 8) & 0x00FF));
    out(0x3D4, 15);
    out(0x3D5, pos & 0x00FF);
}

/**
 * In order to avoid execution of arbitrary instructions by CPU we halt it.
 * Halt "pauses" CPU and puts it in low power mode until next interrupt occurs.
 */
_Noreturn void halt_loop() {
    while (1) { halt(); }
}

void key_handler(struct keyboard_event event) {

   if (event.key_character && event.type == EVENT_KEY_PRESSED) {
		
		if (event.key == KEY_BACKSPACE) {
			removeCharacter();

		} else if (event.key == KEY_ENTER)  {

			int currentLine = defineCurrentLine(startAddress, currentAddress, amountOfColumn) - 1;

			char *adr = startAddress + (amountOfColumn * 2 * currentLine);
			adr += lengthSignLine;

			int k = defineCommand(adr);

			if (k == 0) {
				adr -= lengthSignLine;
				currentAddress = helpCommand(adr, amountOfColumn);
				moveNextLine();
			}

		} else {
			writeCharacter(event.key_character);
		}

   }
}

void removeCharacter() {

	int currentLine = defineCurrentLine(startAddress, currentAddress, amountOfColumn) - 1;

	char *startAdr = startAddress + (amountOfColumn * 2 * currentLine);
	startAdr += lengthSignLine;

	if (currentAddress > startAdr) {
		currentAddress -= 2;
		*currentAddress = ' ';
		--cursorPosition;
		put_cursor(cursorPosition);
	}
}



void writeCharacter(char letter) {

	char *bound = startAddress + ((amountOfColumn * 2) * defineCurrentLine(startAddress, currentAddress, amountOfColumn) - 2);

	if (currentAddress < bound) {
		*currentAddress = letter;
		currentAddress += 2;
		cursorPosition++;
		put_cursor(cursorPosition);	
	}
}

void moveNextLine() {

	int currentLine = defineCurrentLine(startAddress, currentAddress, amountOfColumn);

	currentAddress = startAddress + (amountOfColumn * 2 * currentLine);
	char *sign = "$ ";

	while (*sign != '\0') {
		
		*currentAddress = *sign;
		*(currentAddress + 1) = 0x2;
		currentAddress += 2;
		sign++; 
	}

	cursorPosition = amountOfColumn * currentLine + lengthSignLine / 2;
	put_cursor(cursorPosition);
}

void timer_tick_handler() {
    // do something when timer ticks
}


/**
 * This is where the bootloader transfers control to.
 */
void kernel_entry() {
    init_kernel();
    keyboard_set_handler(key_handler);

    timer_set_handler(timer_tick_handler);

    halt_loop();
}

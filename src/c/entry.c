#include "kernel/kernel.h"
#include "drivers/keyboard/keyboard.h"
#include "drivers/timer/timer.h"
#include "drivers/serial_port/serial_port.h"

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
    /*if (event.key_character && event.type == EVENT_KEY_PRESSED) {
	char *message = &event.key_character;
        char *framebuffer = (char *) 0xb8000;

        while (*message != '\0') {
            *framebuffer = *message;
            *(framebuffer + 1) = 0x2;
            framebuffer += 2;
            message++;
        }
    } */
}

char *firstPosition = (char *) 0xb8000;
int cursor_position = 0;
int current_row = 0;

void write_letter(struct keyboard_event event) {

   if (event.key_character && event.type == EVENT_KEY_PRESSED) { 
	char *message = &event.key_character;

	if (*message == '\b') {
	    removeSymbol();
	} else {
	    writeSymbol(message);
	}

	if (*message == '\n') {
	    choseCommand();		
		move_next_line();
		current_row++;
	}
	
	
   }
}

void removeSymbol() {

    char *message = " ";

    if (firstPosition > 0xb8000) {

		firstPosition -= 2;
	
		*firstPosition = *message;

		put_cursor(--cursor_position + (80 * current_row));
	}
        
     
}


void writeSymbol(char *character) {


    *firstPosition = *character;
    *(firstPosition + 1) = 0x2;
    firstPosition += 2;

    put_cursor(++cursor_position + (80 * current_row));
    

}

void choseCommand() {

    resetPosition();

	char *position = firstPosition;

    int count = 0;
    char *array = "clear";

    while (*position != '\0' && *array != '\0') {
		
		if (*position == *array) {
			position += 2;
			array++;
			
		} else {

			return;
		}
		
    }
	
	clear_terminal();
    
}



void timer_tick_handler() {
    // do something when timer ticks
}

/**
* This is procedure which cleared a terminal
*/
void clear_terminal() {
    // demo of printing hello world to screen using framebuffer
    char *message = " ";
    char *framebuffer = (char *) 0xb8000;
    int amout_of_iteration = 0;
    while (amout_of_iteration < (80*25)) {
        *framebuffer = *message;
        *(framebuffer + 1) = 0x2;
        framebuffer += 2;
		amout_of_iteration++;
    }
	
	cursor_position = 0;

	resetPosition();
 	
}

void resetPosition() {
	
	firstPosition = (char *) 0xb8000 + (160 * current_row);
	put_cursor(80 * current_row);
}

void move_next_line() {
	resetPosition();
	firstPosition = firstPosition + 160;
	
}

/**
 * This is where the bootloader transfers control to.
 */
void kernel_entry() {
    init_kernel();
    keyboard_set_handler(write_letter);

    timer_set_handler(timer_tick_handler);
    /*char *list_command = {"help", "clear"};
    // demo of printing hello world to screen using framebuffer
    char *message = "Hello world!";
    char *framebuffer = (char *) 0xb8000;

    while (*message != '\0') {
        *framebuffer = *message;
        *(framebuffer + 1) = 0x2;
        framebuffer += 2;
        message++;
    } */
    clear_terminal(); 
    put_cursor(cursor_position);

    halt_loop();
}

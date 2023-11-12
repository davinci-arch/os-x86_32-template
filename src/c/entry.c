#include "kernel/kernel.h"
#include "drivers/keyboard/keyboard.h"
#include "drivers/timer/timer.h"
#include "drivers/serial_port/serial_port.h"
#include "data/dataUtils.h"
#include "data/commandUtils.h"
#include "stringUtils/stringHandler.h"
#include "file/fileHandler.h"
#include "states/stateUtil.h"

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
	init_base_configuration();
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

       
        if (isScreensaver() == 1) {
            returnFromSleep();
            moveNextLine();

            if (getCurrentLine() <= getAmountOfLine()) {
                overflowView();
            }
        }

        if (event.key == KEY_BACKSPACE) {
            removeCharacter();
        
        } else if (event.key == KEY_ENTER)  {

            if (fileOn.isEdit == -1 || fileOn.isEdit == 0) {
                executeCommand();
            } else {
                moveNextLineWithoutSign();
            }
        } else if (event.key == KEY_TAB) {
            saveChanges(); //save changes in file
            
        } else {
            writeCharacter(event.key_character);
        }
        
        
   }
}



void timer_tick_handler() {
    // do something when timer ticks
    if (isScreensaver() == 1) {
        move();
    }
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

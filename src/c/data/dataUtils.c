#include "dataUtils.h"
#include "../stringUtils/stringHandler.h"
#define START_ADDRESS 0xb8000


const char *lineSign = "$ ";
const int amountOfLine = 25;
const int amountOfColumn = 80;
const int lengthSignLine = 4;

char *currentAddress = (char *)START_ADDRESS;
int cursorPosition = 2;
int currentLine = 0;

void put_cursor(unsigned short pos) {
    out(0x3D4, 14);
    out(0x3D5, ((pos >> 8) & 0x00FF));
    out(0x3D4, 15);
    out(0x3D5, pos & 0x00FF);
}

void saveCurrentState() {

}

void init_base_configuration() {

    
    fillCommandStrucutre();
    clearTerminal(START_ADDRESS, lineSign, amountOfColumn, amountOfLine);
    resetParam();
}



int defineCurrentLine() {

    int start = (int) START_ADDRESS;
    int end = (int) currentAddress;

    int result = (end % start) / 160;

    return result + 1;

}

void removeCharacter() {


	char *startAdr = START_ADDRESS + (amountOfColumn * 2 * currentLine);
	startAdr += lengthSignLine;
    

	if (currentAddress != startAdr) {
		currentAddress -= 2;
		*currentAddress = ' ';
		--cursorPosition;
		put_cursor(cursorPosition);
	}
}

void writeCharacter(char letter) {

	// char *bound = START_ADDRESS + ((amountOfColumn * 2) * defineCurrentLine() - 2);
    
    *currentAddress = letter;
    currentAddress += 2;
    cursorPosition++;
    put_cursor(cursorPosition);	
	
}

void moveNextLine() {

	currentLine = defineCurrentLine();

	currentAddress = START_ADDRESS + (amountOfColumn * 2 * currentLine);
	char *sign = lineSign;

	while (*sign != '\0') {
		
		*currentAddress = *sign;
		*(currentAddress + 1) = 0x2;
		currentAddress += 2;
		sign++; 
	}

	cursorPosition = amountOfColumn * currentLine + lengthSignLine / 2;
	put_cursor(cursorPosition);
}

void resetParam() {

	cursorPosition = lengthSignLine / 2;
	currentAddress = START_ADDRESS;
    currentLine = 0;
	put_cursor(cursorPosition);
	currentAddress += lengthSignLine;
}

void executeCommand() {
    int currentLine = defineCurrentLine();

    char *adr = START_ADDRESS + (amountOfColumn * 2 * (currentLine - 1));
    adr += lengthSignLine;

    int numberCommand = defineCommand(adr);

    switch (numberCommand) {
        case 0:
            currentAddress = helpCommand(adr, amountOfColumn);
            moveNextLine();
            break;
        case 1:
            //clear
            clearTerminal(START_ADDRESS, lineSign, amountOfColumn, amountOfLine);
            resetParam();
            break;
        default:
            // printWrongMessage
            currentAddress = getWrongMessage(adr, amountOfColumn);
            moveNextLine();
            break;
    }

}




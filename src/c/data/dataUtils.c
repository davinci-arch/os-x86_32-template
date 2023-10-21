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

    int result = (end - start) / 160;

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

	char *bound = START_ADDRESS + ((amountOfColumn * 2) * amountOfLine) - 2; // max length (80 * 2) * 25
    
    if (currentAddress < bound) {
        *currentAddress = letter;
        currentAddress += 2;
        cursorPosition++;
        put_cursor(cursorPosition);	
	
    }
    
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

    int numberCommand = defineCommand(adr, lengthSignLine);


    switch (numberCommand) {

        case 0:
            currentAddress = helpCommand(adr, amountOfColumn);
            moveNextLine();
            break;

        case 1:

            clearTerminal(START_ADDRESS, lineSign, amountOfColumn, amountOfLine);
            resetParam();
            break;

        default:
            currentAddress = getWrongMessage(adr, amountOfColumn);
            moveNextLine();
            break;
    }

    if (currentLine <= amountOfLine) {
        overflowView();
    }
}


void overflowView() {

    int cnt = defineCurrentLine() - amountOfLine;
        
    int counter = 0;
    while(counter < cnt) {
        
        moveAllLineUp();
        counter++;
    }


}

void moveAllLineUp() {

    char *addressBefore = (char *) 0xb7F60;
    char *addressAfter = (char *) START_ADDRESS;



    for (int i = 1; i <= amountOfColumn; i++) {

        int counter = 0;

        while (counter < amountOfColumn) {
            *addressBefore = *addressAfter;
            *(addressBefore + 1) = *(addressAfter + 1); // Move a style text too
            addressBefore += 2;
            addressAfter += 2;
            counter++;
        }

    }

    currentLine = amountOfLine - 1;
    cursorPosition = amountOfColumn * currentLine + lengthSignLine / 2;
    put_cursor(cursorPosition);

    currentAddress = START_ADDRESS + (amountOfColumn * 2 * currentLine) + lengthSignLine;
    currentLine = defineCurrentLine();
}




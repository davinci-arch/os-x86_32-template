#include "dataUtils.h"
#include "../stringUtils/stringHandler.h"
#include "blockDatautils.h"
#include "../states/stateUtil.h"
#include "../file/fileHandler.h"

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



void init_base_configuration() {

    changeStartBlock(0, START_ADDRESS);
    fillCommandStrucutre();
    clearTerminal(START_ADDRESS, amountOfColumn, amountOfLine);
    printSignLine(START_ADDRESS, lineSign);
    resetParam();
}


int defineCurrentLine() {

    int start = (int) START_ADDRESS;
    int end = (int) currentAddress;

    int result = (end - start) / 160;

    return result + 1;

}

void removeCharacter() {


	char *startAdr = START_ADDRESS + ((amountOfColumn * 2) * currentLine) + lengthSignLine;
    

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

            clearTerminal(START_ADDRESS, amountOfColumn, amountOfLine);
            printSignLine(START_ADDRESS, lineSign);
            resetParam();
            break;
        case 2:

            createFile(adr, lengthSignLine);
            moveNextLine();
            //create file

            // saveCurrentState(0, 1, cursorPosition, amountOfColumn, amountOfLine, 0);
            // printSignLine(START_ADDRESS, lineSign);
            // resetParam();

            break;

        case 3:
            // delete file
            // saveCurrentState(1, 0, cursorPosition, amountOfColumn, amountOfLine, 1);
            

        //    int saveValue = states[0].cursorPosition;

        //     currentLine = saveValue / amountOfColumn;   // move to previous current position;

        //     int positionOnLine = (saveValue % amountOfColumn) * 2;

        //     currentAddress = START_ADDRESS + (amountOfColumn * 2) * currentLine + positionOnLine;

        //     cursorPosition = saveValue;
        //     put_cursor(saveValue);
        //     moveNextLine();
            
            break;
        case 4:

            // const int fileNumber = fileIsExist(defineStartFileName(adr, lengthSignLine));

            editFile(adr, lengthSignLine, cursorPosition, amountOfColumn, amountOfLine, START_ADDRESS);
            
            break;

        case 5:
            //display all createad files
            currentAddress = ls(adr);
            moveNextLine();
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


void saveChanges() {
    saveChangeFile(cursorPosition, amountOfColumn, amountOfLine);
    
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



    for (int i = 0; i < amountOfLine * 2; i++) { // 

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

}

void changeAddress(char *newAdr) {
    currentAddress = newAdr;
}

void changeValueCursorPosition(int value) {
    cursorPosition = value;
}

char *getAddress() {
    return currentAddress;
}

int getCursorPosition() {
    return cursorPosition;
}

int getAmountOfColumnt() {
    return amountOfColumn;
}

int getAmountOfLine() {
    return amountOfLine;
}

int getLengthLineSign() {
    return lengthSignLine;
}

char *getLineSign() {
    return lineSign;
} 

char *getBaseAddress() {
    return START_ADDRESS;
}

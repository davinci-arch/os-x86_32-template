#include "commandUtils.h"
#include "dataUtils.h";
#include "../file/fileHandler.h"
#include "../states/stateUtil.h";
#include "../stringUtils/stringHandler.h"

void fillCommandStrucutre() {

    commands[0].command = "help";
    commands[1].command = "clear";
    commands[2].command = "create";
    commands[3].command = "delete";
    commands[4].command = "edit";
    commands[5].command = "ls";
    commands[6].command = "read";


}



void clearTerminal(char *startAddress, int amountOfColumn, int amountOfLine) {
    char clearSymbol = ' ';

	char *frameBuffer = (char *) startAddress;
	
	int count = 0;
	while (count <= (amountOfColumn * amountOfLine)) {

		*frameBuffer = clearSymbol;
        *(frameBuffer + 1) = 0x7;
		frameBuffer += 2;
		count++;
	}
}

void printSignLine(char *startAddress, char *lineSign) {
    char *sign = lineSign;

	while (*sign != '\0') {
		
		*startAddress = *sign;
		*(startAddress + 1) = 0x2;
		startAddress += 2;
		sign++; 
	}
}

char *helpCommand(char *currentAddress, int amountOfColumn) {

    char *saveAdr = currentAddress;
    for (int i = 0; i < 7; i++) {

        currentAddress += amountOfColumn * 2;
        
        char *currentCommand = commands[i].command;

        while (*currentCommand != '\0') {

            *currentAddress = *currentCommand;

            currentAddress += 2;
            currentCommand++;
        }
        currentAddress = saveAdr + (amountOfColumn * 2 * (i + 1));
    }

    return currentAddress;
}

char *getWrongMessage(char *currentAddress, int amountOfColumn) {

    currentAddress += amountOfColumn * 2;

    char *message = "You wrote wrong command!";

    while (*message != '\0') {
        
        *currentAddress = *message;
        *(currentAddress + 1) = 0x4;
        message++;
        currentAddress += 2;
    }

    return currentAddress;

}


void createFile(char *currentAddress, int lengthSignLine) {

    createNewFile(currentAddress, lengthSignLine);
    
}

char *ls(char *currentAddress) {
    return printAllFiles(currentAddress);
}

void editFile(char *currentAddress, int lengthSignLine, int currentCursorPosition, int amountOfColumn, int amountOfLine, char *baseAddress) {

 

}

void saveChangeFile(int currentCursorPosition, int amountOfColumn, int amountOfLine) {

    
 
    

}



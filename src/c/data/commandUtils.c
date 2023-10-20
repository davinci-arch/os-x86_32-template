#include "commandUtils.h"

void fillCommandStrucutre() {

    commands[0].command = "help";
    commands[1].command = "clear"; 
}



void clearTerminal(char *startAddress, char *lineSign, int amountOfColumn, int amountOfLine) {
    char clearSymbol = ' ';

	char *frameBuffer = (char *) startAddress;
	
	int count = 0;
	while (count <= (amountOfColumn * amountOfLine)) {

		*frameBuffer = clearSymbol;
		frameBuffer += 2;
		count++;
	}

	printSignLine(startAddress, lineSign);
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
    for (int i = 0; i < 2; i++) {

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



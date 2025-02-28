#include "commandUtils.h"
#include "dataUtils.h";
#include "../file/fileHandler.h"
#include "../states/stateUtil.h";
#include "../stringUtils/stringHandler.h"
#include "../screensaver/screensaver.h"

#include "blockDatautils.h"

void fillCommandStrucutre() {

    commands[0].command = "help";
    commands[1].command = "clear";
    commands[2].command = "create";
    commands[3].command = "delete";
    commands[4].command = "edit";
    commands[5].command = "ls";
    commands[6].command = "read";
    commands[7].command = "sleep";


}



void clearTerminal(char *startAddress) {
    char clearSymbol = ' ';

	char *frameBuffer = (char *) startAddress;
	
	int count = 0;
	while (count <= (getAmountOfColumn() * getAmountOfLine())) {

		*frameBuffer = clearSymbol;
        *(frameBuffer + 1) = 0x7;
		frameBuffer += 2;
		count++;
	}
}

void printSignLine(char *startAddress) {
    char *sign = getLineSign();

	while (*sign != '\0') {
		
		*startAddress = *sign;
		*(startAddress + 1) = 0x2;
		startAddress += 2;
		sign++; 
	}
}

char *helpCommand(char *currentAddress) {

    char *saveAdr = currentAddress;
    int amountOfColumn = getAmountOfColumn();

    for (int i = 0; i < 8; i++) {

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

char *getMessage(char *msg, char *color) {

    int cursor = getCurrentLine();
    
    char *address = getBaseAddress() + ((getAmountOfColumn() * 2) * cursor) + (getAmountOfColumn() * 2);

    char *message = msg;

    while (*message != '\0') {
        
        *address = *message;
        *(address + 1) = color;
        message++;
        address += 2;
    }

    return address;

}


void createFile(char *currentAddress) {

    createNewFile(currentAddress);
    
}

char *ls(char *currentAddress) {
    return printAllFiles(currentAddress);
}

void editFile(char *currentAddress) {

    char *filename = defineStartFileName(currentAddress);
    int positionMainWindowBlock = 0;
    int positionFile = fileIsExist(filename);

    if (positionFile >= 0) {

        changeCurrentAddress(positionMainWindowBlock, currentAddress);
    

        fileOn.isEdit = 1;
        fileOn.index = positionFile;

        saveCurrentState(positionMainWindowBlock, positionFile + 1);
        put_cursor(states[positionFile + 1].cursorPosition);

        updateTerminal(positionFile);

    } else {
        setCurrentAddress(getMessage("File dosen't exist!", 0x4));
        moveNextLine();
    }
    

    

}

void saveChangeFile(int currentCursorPosition) {

    int positionMainWindowBlock = 0;
    int activeFileIndex = fileOn.index;

    changeCurrentAddress(activeFileIndex + 1, getAddress());
    changeCursor(activeFileIndex + 1, getCursorPosition());
    
    saveCurrentState(activeFileIndex + 1, positionMainWindowBlock);

    updateTerminal(positionMainWindowBlock - 1);
    moveNextLine();
    fileOn.isEdit = -1;
    fileOn.index = -1;

}


void updateTerminal(int index) {

    if (states[index + 1].currentAddress == '\0') {
        states[index + 1].currentAddress = getBaseAddress();
    }
    
    setCurrentAddress(states[index + 1].currentAddress);
    setCursorPositoin(states[index + 1].cursorPosition);
    put_cursor(states[index + 1].cursorPosition);

    
}

void *readFileContent(char *address) {

    char *filename = defineStartFileName(address);

    int index = fileIsExist(filename);

    if (index >= 0) {
        
        int cursorPos = states[index + 1].cursorPosition;

        address += getAmountOfColumn() * 2;

        char *adrBlock = states[index + 1].startBlock;

        if (cursorPos > 0) {

            for (int i = 0; i < cursorPos; i++) {
                *address = *adrBlock;
                *(address + 1) = *(adrBlock + 1);
                address += 2;
                adrBlock += 2;
            }

            setCurrentAddress(address);
        }

    } else {
        setCurrentAddress(getMessage("File dosen't exist!", 0x4));

    }

}

void deleteFile(char *address) {

    char *filename = defineStartFileName(address);

    int indexFile = fileIsExist(filename);

    if (indexFile >= 0) {

        deleteFilename(indexFile);
        setCurrentAddress(getMessage("File succsess deleted!", 0x2));

    } else {
        setCurrentAddress(getMessage("File dosen't exist!", 0x4));
    }

}

void activateSleep() {
    int startPositionX = 52;
    int startPositionY = 6;
    int positionMainWindowBlock = 0;

    changeScreensaver(1); // run timer code

    changeCurrentAddress(positionMainWindowBlock, getAddress());
    changeCursor(positionMainWindowBlock, getCursorPosition());

    changeCurrentAddress(10, getBaseAddress());

    saveCurrentState(positionMainWindowBlock, 10); // swap displays
    
    setCurrentAddress(states[10].currentAddress);
    put_cursor(states[10].cursorPosition);

    run(startPositionX, startPositionY);
    move();

}

void returnFromSleep() {
    int positionMainWindowBlock = 0;

    changeScreensaver(0);
    clearTerminal(getBaseAddress());
    saveCurrentState(10, positionMainWindowBlock);
    setCurrentAddress(states[0].currentAddress);
    put_cursor(states[0].cursorPosition);

}
#include "stringHandler.h"
#include "../data/commandUtils.h";

int defineCommand(char *currentAddress) {

    currentAddress += getLengthLineSign();

    char *startCommand = defineStartCommand(currentAddress);

    int t = -1;

    char *tempAddr = startCommand;

    for (int i = 0; i < 7; i++) {

        char *currentCommand = commands[i].command;

        while (*tempAddr != ' ') {

            if (*tempAddr == *currentCommand) {
                currentCommand++;
                tempAddr += 2;
                t = i;
            } else {
                t = -1;
                break;
            }
        }

        if (t >= 0) {
            return t;
        } else {
            tempAddr = startCommand;
        }
    }
    return t;

}

char *defineStartCommand(char *currentAddress) {

    while (*currentAddress == ' ') {
        currentAddress += 2;
    }

    return currentAddress;

}

char *defineStartFileName(char *currentAddress) {

    currentAddress += getLengthLineSign();

    char *fileName = defineStartCommand(currentAddress);

    fileName = skipWord(fileName);

    
    while (*fileName == ' ') {
        fileName += 2;
    }

    return fileName;
    

}

char *skipWord(char *address) {

    while (*address != ' ') {
        address += 2;
    }

    return address;
    
}

char *defineAddresLastWord(char *address) {
    
    int isLast = 0;
    char *adrLastWord;
    for (int i = 0; i < getAmountOfLine(); i++) {

        for (int j = 0; j < getAmountOfColumn(); j++) {

            if (*address != ' ' && *address != '\n') {
                adrLastWord = address;
            }
            address += 2;
        }
        
    }

    if (adrLastWord != '\0') {

        return adrLastWord;

    } else {
        return '\0';
    }
}



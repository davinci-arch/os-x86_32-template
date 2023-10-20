#include "stringHandler.h"
#include "../data/commandUtils.h";

int defineCommand(char *currentAddress) {
    char *startCommand = defineStartCommand(currentAddress);

    for (int i = 0; i < 2; i++) {

        char *currentCommand = commands[i].command;

        while (*currentCommand != '\0') {

            if (*startCommand == *currentCommand) {
                currentCommand++;
                startCommand += 2;
            } else {
                break;
            }
            return i;
        }
    }
    return -1;

}

char *defineStartCommand(char *currentAddress) {

    while (*currentAddress == ' ') {
        currentAddress += 2;
    }

    return currentAddress;

}



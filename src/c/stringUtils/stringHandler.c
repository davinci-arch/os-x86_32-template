#include "stringHandler.h"
#include "../data/commandUtils.h";

int defineCommand(char *currentAddress) {
    char *startCommand = defineStartCommand(currentAddress);

    int t = -1;
    for (int i = 0; i < 2; i++) {

        char *currentCommand = commands[i].command;

        while (*currentCommand != '\0') {

            if (*startCommand == *currentCommand) {
                currentCommand++;
                startCommand += 2;
                t = i;
            } else {
                t = -1;
                break;
            }
        }

        if (t >= 0) {
            return t;
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



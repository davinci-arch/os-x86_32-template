#include "dataUtils.h"


void saveCurrentState(char *startAddress) {

}

int defineCurrentLine(char *startAddress, char *currentAddres, int amountOfColumn) {

    int start = (int) startAddress;
    int end = (int) currentAddres;

    int result = (end % start) / 160;

    return result + 1;

}


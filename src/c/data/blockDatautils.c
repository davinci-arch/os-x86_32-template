#include "blockDatautils.h"


void copyBlockIntoNewSection(char *startFirstBlock, char *startSecondBlock, int amountOfColumn, int amountOfLine) {

    char *firstBlock = startFirstBlock;
    char *secondBlock = startSecondBlock;

    for (int i = 0; i < amountOfLine; i++) {
        
        for (int j = 0; j < amountOfColumn; j++) {
            char tempChar = *secondBlock;

            *secondBlock = *firstBlock;
            *(secondBlock + 1) = *(firstBlock + 1);
            *firstBlock = tempChar;
            
            firstBlock += 2;
            secondBlock += 2;
        }
    }

}

void clearBlock(char *startAddress, int amountOfLine) {

    char clear = ' ';

    for(int i = 0; i < amountOfLine; i++) {
        *startAddress += clear;
        *(startAddress + 1) = 0x0;
        startAddress += 2;
    }
}


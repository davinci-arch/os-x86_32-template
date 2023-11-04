#include "blockDatautils.h"
#include "../data/dataUtils.h"

void copyBlockIntoNewSection(char *startFirstBlock, char *startSecondBlock) {

    char *firstBlock = startFirstBlock;
    char *secondBlock = startSecondBlock;

    for (int i = 0; i < getAmountOfLine(); i++) {
        
        for (int j = 0; j < getAmountOfColumn(); j++) {
            char tempChar = *secondBlock;
            char tempStyle = *(secondBlock + 1);

            *secondBlock = *firstBlock;
            *(secondBlock + 1) = *(firstBlock + 1);
            *firstBlock = tempChar;
            *(firstBlock + 1) = tempStyle;
            firstBlock += 2;
            secondBlock += 2;
        }
    }

}

void clearBlock(char *startAddress) {

    char clear = ' ';

    for(int i = 0; i < getAmountOfLine(); i++) {
        for (int j = 0; j < getAmountOfColumn(); j++) {
            *startAddress = clear;
            startAddress += 2;

        }
    }
}


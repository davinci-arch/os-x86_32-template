#include "stateUtil.h"
#include "../data/blockDatautils.h"

//0xcb880

void addNewStateBlock(char *startBlock, int cursorPos) {

    int definePosition = defineEmptyBlock();

    states[definePosition].startBlock = startBlock;
    states[definePosition].cursorPosition = cursorPos; 

}

void changeCursor(int pos, int newCursorPos) {

    states[pos].cursorPosition = newCursorPos;
}

void changeStartBlock(int pos, char *newStartBlock) {

    states[pos].startBlock = newStartBlock;
}

void changeCurrentAddress(int pos, char *currAdress) {
    states[pos].currentAddress = currAdress;
}


int defineEmptyBlock() {

    for (int i = 0; i < 10; i++) {
        if (states[i].startBlock == '\0') {
            return i;
        }
    }
    return -1;
}

void saveCurrentState(int firstBlock, int secondBlock) {
    
    if (states[firstBlock].startBlock != '\0' && states[secondBlock].startBlock != '\0') {
        copyBlockIntoNewSection(states[firstBlock].startBlock, states[secondBlock].startBlock);
    }

}






#include "stateUtil.h"
#include "../data/blockDatautils.h"

void fillTerminalState(char *startAddress, int cursorPos, int pos) {
    states[pos].startBlock = startAddress;
    states[pos].cursorPosition = cursorPos;
}

void initMainTerminalStateBlock(char *mainBlock, char *bufferMainBlock) {
    
    states[0].startBlock = mainBlock;
    states[1].startBlock = bufferMainBlock;

}

void saveCurrentState(int firstBlock, int secondBlock, int cursorPos, int amountOfColumn, int amountOfLine, int pos) {
    
    states[pos].cursorPosition = cursorPos;


    copyBlockIntoNewSection(states[firstBlock].startBlock, states[secondBlock].startBlock, amountOfColumn, amountOfLine);

    
}






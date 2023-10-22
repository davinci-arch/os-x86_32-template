#ifndef STATEUTIL_H
#define STATEUTIL_H

struct TerminalState{

    char *startBlock;
    int cursorPosition;
    
}states [5];

void fillTerminalState(char *startAddress, int cursorPos, int pos);
void initMainTerminalStateBlock(char *mainBlock, char *bufferMainBlock);
void saveCurrentState(int firstBlock, int secondblock, int cursorPos, int amountOfColumn, int amountOfLine, int pos);

#endif
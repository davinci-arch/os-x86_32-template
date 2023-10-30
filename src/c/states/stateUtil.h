#ifndef STATEUTIL_H
#define STATEUTIL_H

struct TerminalState{

    char *startBlock;
    char *currentAddress;
    int cursorPosition;
    
}states [11];


void addNewStateBlock(char *startBlock, int cursorPos);
void changeCursor(int pos, int newCursorPos);
void changeStartBlock(int pos, char *newStartBlock);
void saveCurrentState(int firstBlock, int secondblock);
void changeCurrentAddress(int pos, char *currAdress);
#endif
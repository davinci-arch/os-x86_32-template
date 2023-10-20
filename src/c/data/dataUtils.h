#ifndef DATAUTILS_H
#define DATAUTILS_H


struct TerminalState{

    int c;
}states [5];



void saveCurrentState(char *startAddress);

int defineCurrentLine(char *startAddress, char *currentAddres, int amountOfColumn);

#endif
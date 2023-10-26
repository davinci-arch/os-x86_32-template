#ifndef COMMANDUTILS_H
#define COMMANDUTILS_H


struct Command {

    char *command;
    char *keys_to_command[5];


} commands[6];

void fillCommandStrucutre();
void clearTerminal(char *startAddress, char *lineSign, int amountOfColumn, int amountOfLine);
void printSignLine(char *startAddress, char *lineSign);

char *helpCommand(char *currentAddress, int amountOfColumn);
char *getWrongMessage(char *currentAddress, int amountOfColumn);
void createFile(char *currentAddress, int lengthSignLine);
char *ls(char *currentAddress);
#endif;
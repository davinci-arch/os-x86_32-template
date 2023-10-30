#ifndef COMMANDUTILS_H
#define COMMANDUTILS_H


struct Command {

    char *command;
    char *keys_to_command[5];


} commands[6];

void fillCommandStrucutre();
void clearTerminal(char *startAddress, int amountOfColumn, int amountOfLine);
void printSignLine(char *startAddress, char *lineSign);
void editFile(char *currentAddress, int lengthSignLine, int currentCursorPosition, int amountOfColumn, int amountOfLine, char *baseAddress);
void saveChangeFile(int currentCursorPosition, int amountOfColumn, int amountOfLine);

char *helpCommand(char *currentAddress, int amountOfColumn);
char *getWrongMessage(char *currentAddress, int amountOfColumn);
void createFile(char *currentAddress, int lengthSignLine);
char *ls(char *currentAddress);
#endif;
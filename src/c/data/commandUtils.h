#ifndef COMMANDUTILS_H
#define COMMANDUTILS_H


struct Command {

    char *command;
    char *keys_to_command[5];


} commands[6];

void fillCommandStrucutre();
void clearTerminal(char *startAddress);
void printSignLine(char *startAddress);
void editFile(char *currentAddress);
void saveChangeFile(int currentCursorPosition);

char *helpCommand(char *currentAddress);
char *getWrongMessage(char *currentAddress);
void createFile(char *currentAddress);
char *ls(char *currentAddress);
#endif;
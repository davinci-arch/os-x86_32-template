#ifndef COMMANDUTILS_H
#define COMMANDUTILS_H


struct Command {

    char *command;
    char *keys_to_command[5];


} commands[5];

void fillCommandStrucutre();
void clearTerminal(char *startAddress, int amountOfColumn, int amountOfLine);
void printSignLine(char *startAddress);

char *helpCommand(char *currentAddress, int amountOfColumn);


#endif;
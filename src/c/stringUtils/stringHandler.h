#ifndef STRINGUTILS_H
#define STRINGUTILS_H

int defineCommand(char *currentAddress);

char *defineStartCommand(char *currentAddress);
char *defineStartFileName(char *currentAddress);
char *skipWord(char *address);
char *defineAddresLastWord(char *address);
#endif
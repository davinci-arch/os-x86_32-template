#ifndef STRINGUTILS_H
#define STRINGUTILS_H

int defineCommand(char *currentAddress, int lengthSignLine);

char *defineStartCommand(char *currentAddress);
char *defineStartFileName(char *currentAddress, int lengthSignLine);
char *skipWord(char *address);

#endif
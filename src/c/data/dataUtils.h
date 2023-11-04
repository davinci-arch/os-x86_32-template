#ifndef DATAUTILS_H
#define DATAUTILS_H


void put_cursor(unsigned short pos);
void saveCurrentState();
void init_base_configuration();
void removeCharacter();
void writeCharacter(char letter);
void moveNextLine();
void resetParam();
int defineCurrentLine();
void executeCommand();
void overflowView();
void moveAllLineUp();
void saveCurrentState();
void saveChanges();
void setCursorPositoin(int value);
void setCurrentAddress(char *newAdr);
char *getAddress();
int getCursorPosition();
int getAmountOfColumn();
int getAmountOfLine();
int getLengthLineSign();
char *getLineSign();
char *getBaseAddress();
int getCurrentLine();
void moveNextLineWithoutSign();
/**
 * Puts cursors in a given position. For example, position = 20 would place it in
 * the first line 20th column, position = 80 will place in the first column of the second line.
 */


#endif
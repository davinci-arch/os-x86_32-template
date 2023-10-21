#ifndef DATAUTILS_H
#define DATAUTILS_H


struct TerminalState{

    int c;
}states [5];


void put_cursor(unsigned short pos);
void saveCurrentState();
void init_base_configuration();
void removeCharacter();
void writeCharacter(char letter);
void moveNextLine();
void resetParam();
int defineCurrentLine();
void executeCommand();
void moveAllLineUp();
/**
 * Puts cursors in a given position. For example, position = 20 would place it in
 * the first line 20th column, position = 80 will place in the first column of the second line.
 */


#endif
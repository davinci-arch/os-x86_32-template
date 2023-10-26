#ifndef FILEHANDLER_H
#define FILEHANDLER_H


struct FileBlock {

    char *fileNameAddress;
    char *startBlock;
    int currentCursor;

} files[10];


void createNewFile(char *currentAddress, int lengthSignLine);
char *defineEmptyAddressForFile();
void setAddressForNewFile(char *startFileName);
void setNameIntoAddress(char *startFileName, char *startBufferFilename);
char *printAllFiles(char *currentAddress);
#endif
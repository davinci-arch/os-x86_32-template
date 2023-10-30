#ifndef FILEHANDLER_H
#define FILEHANDLER_H


struct FileBlock {

    char *fileNameAddress;
    char *startBlock;
    int currentCursor;

} files[10];

struct FileAction {

    int isEdit;
    int index;
    
} fileOn;

void createNewFile(char *currentAddress, int lengthSignLine);
char *defineEmptyAddressForFile();
void setAddressForNewFile(char *startFileName);
void setNameIntoAddress(char *startFileName, char *startBufferFilename);
char *printAllFiles(char *currentAddress);
int fileIsExist(char *filename);
#endif
#include "fileHandler.h"
#include "../stringUtils/stringHandler.h"

#define START_BLOCK_FILES 0xbaee0
#define START_BLOCK_FILENAME 0xb9f40

const int maxAmountOfFiles = 10;

int amountOfCreatedFiles = 0;

void createNewFile(char *currentAddress, int lengthSignLine) {


    if (amountOfCreatedFiles == maxAmountOfFiles) {

        // printErrorFile();

    } else {
        char *startFileName = defineStartFileName(currentAddress, lengthSignLine);

       

        setAddressForNewFile(startFileName);

        amountOfCreatedFiles++;    
        
        
    }
    
}

void setAddressForNewFile(char *startFileName) {

    for (int i = 0; i < maxAmountOfFiles; i++) {

        if (files[i].fileNameAddress == '\0') {
            files[i].fileNameAddress = defineEmptyAddressForFile();
            setNameIntoAddress(startFileName, files[i].fileNameAddress);
            break;
        }
    }
}

char *defineEmptyAddressForFile() {
    
    char *fileNameBuffer = START_BLOCK_FILENAME;

    int foundEmptyLine;

    for (int i = 0; i < maxAmountOfFiles; i++) {

        for (int j = 0; j < 80; j++) {

            if (*fileNameBuffer == ' ') {

                fileNameBuffer += 2;
                foundEmptyLine = 1;

            } else {
                foundEmptyLine = 0;
                break;
            }
        }

        if (foundEmptyLine >= 1) {
            return (char *)(START_BLOCK_FILENAME + (160 * i)); // empty address was define;
        } else {
            fileNameBuffer = START_BLOCK_FILENAME + (160 * (i + 1)); // move to next line for check an empty address
        }
    }


}

void setNameIntoAddress(char *startFileName, char *startBufferFilename) {

    for(int i = 0; i < 80; i++) {
        *startBufferFilename = *startFileName;
        *(startBufferFilename + 1) = *(startFileName + 1);

        startBufferFilename += 2;
        startFileName += 2;
        
    }
}


char *printAllFiles(char *currentAddress) {

    char *saveAdr = currentAddress;
    char *startFileName = START_BLOCK_FILENAME;

    for (int i = 0; i < amountOfCreatedFiles; i++) {
        currentAddress += 160;
        
         while (*startFileName != ' ') {

            *currentAddress = *startFileName;

            currentAddress += 2;
            startFileName +=2;
        }
        currentAddress = saveAdr + (160 * (i + 1));
        startFileName = START_BLOCK_FILENAME + (160 * (i + 1));
    }    

    return currentAddress;
}

#include "fileHandler.h"
#include "../stringUtils/stringHandler.h"
#include "../states/stateUtil.h"
#include "../data/dataUtils.h"

#define START_BLOCK_FILES 0xbaee0
#define START_BLOCK_FILENAME 0xb9f40

const int maxAmountOfFiles = 10;

int amountOfCreatedFiles = 0;

void createNewFile(char *currentAddress) {


    if (amountOfCreatedFiles == maxAmountOfFiles) {

        // printErrorFile();

    } else {

        char *startFileName = defineStartFileName(currentAddress);

        setAddressForNewFile(startFileName);

        
        changeStartBlock((amountOfCreatedFiles + 1), (START_BLOCK_FILES + (160 * (25 * amountOfCreatedFiles))));
        amountOfCreatedFiles++;

        
    }
    
}

void setAddressForNewFile(char *startFileName) {

    for (int i = 0; i < maxAmountOfFiles; i++) {

        if (files[i].fileNameAddress == '\0') {
            files[i].fileNameAddress = defineEmptyAddressForFile();
            files[i].startBlock = START_BLOCK_FILES + (160 * amountOfCreatedFiles);
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
        
        while (*startFileName != ' ') {
            *startBufferFilename = *startFileName;
            *(startBufferFilename + 1) = *(startFileName + 1);

            startBufferFilename += 2;
            startFileName += 2;
        }
        
        
    
}

int fileIsExist(char *filename) { // get index file block if files doesn't exist it return -1
    

    int t = -1;

    char *tempAddr = filename;

    for (int i = 0; i < amountOfCreatedFiles; i++) {

        char *file = files[i].fileNameAddress;
      
        
        for (int j = 0; j < 80; j++) {
            
            if (*tempAddr == *file) {
                file += 2;
                tempAddr += 2;
                
                t = i;
            } else {
                t = -1;
                
                break;
            }
        }

        if (t >= 0) {
            return t;
        } else {
            tempAddr = filename;
        }

    }
    return t;
    
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

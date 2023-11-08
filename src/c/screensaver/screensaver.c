#include "screensaver.h"
#include "../data/dataUtils.h"


#define screensaverLetters "xx\nxx";

void run() {

}

void moveLeftBottom() {
    
 
    int x = points[1][0].x;
    int y = points[1][0].y;

    int leftBound = 0;
    int bottomBound = 0;

    if (x >= leftBound && y >= bottomBound) {

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                char *adrN = points[i][j].addressPoint;
                int xN = points[i][j].x;
                int xY = points[i][j].y;
                char *temp = adrN;
                //  = (points[i][j].addressPoint - 2) - (getAmountOfColumn() * 2);
            

                adrN += (getAmountOfColumn() * 2) - 2;
                
                *adrN = *temp;
                *temp = ' ';
                

                points[i][j].x = --xN;
                points[i][j].y = --xY;
                
                points[i][j].addressPoint = adrN;
            }

        }
    }
    
}

void printSaver(char *startAddress) {

    char *frameBuffer = startAddress;
    
    char *screen = (char *) screensaverLetters;

    int j = 0;
    int i = 0;
    
    while (*screen != '\0') {

        if (*screen == '\n') {
            frameBuffer = startAddress + (160 * 1);
            screen++;
            j++;
            i = 0;
            continue;
        }
        
        *frameBuffer = *screen;
        *(frameBuffer + 1) = 0x7;

        initPoints(i, j, frameBuffer);

        frameBuffer += 2;
        screen++;

        i++;
    }

    
}

void initPoints(int i, int j, char *address) {

    int rowPosition = defineLine(address);
    int columnPosition = defineColumn(address);

    points[i][j].addressPoint = address;
    points[i][j].x = columnPosition;
    points[i][j].y = rowPosition;


}

int defineLine(char *address) {

    return (address - getBaseAddress()) / (getAmountOfColumn() * 2);
}

int defineColumn(char *address) {

    int currLine = defineLine(address);

    return (address - (getBaseAddress() + ((getAmountOfColumn() * 2) * currLine))) / 2;
}


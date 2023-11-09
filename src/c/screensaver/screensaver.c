#include "screensaver.h"
#include "../data/dataUtils.h"

// xxx xxx\nx x x  \nx x xxx\nx x   x\nxxx xxx
// x x    x     x   x x  \nx   x   x   x    x   x\nx   x    x x     x   x\nx x       x      x x  
#define screensaverLetters "x x    x     x   x x  \nx   x   x   x    x   x\nx   x    x x     x   x\nx x       x      x x  ";

int collision = 0;
int currentXCollision;
int currentYCollistion;

void run() {


    int x = points[3][0].x;
    int y = points[3][0].y;

    int boundX = 1;
    int boundY = 1;

    
    if (y == boundY || currentYCollistion == 1) {
        currentYCollistion = 1;

        collision = 1;

        for(int i = 0; i < 22; i++) {//amount of column
            for (int j = 0; j < 4; j++) { // amount of line

                char *adr = points[j][i].addressPoint;
                char temp = *adr;

                *adr  = ' ';
                adr -= (getAmountOfColumn() * 2) + 2;
                *adr = temp;

                points[j][i].addressPoint = adr;
                points[j][i].x -= 1;
                points[j][i].y += 1;
            }
        }
        

    } else if(x == boundX) {
        currentYCollistion = 0;

    } else if (collision == 0){
        startVectorMove();
    }

    
// else if (x == 1 || currentXCollision == 1) {
        
//         currentYCollistion = 0;

//         collision = 1;

//         for (int i = 21; i >= 0; i--) {//amount of columns
//             for (int j = 0; j < 4; j++) { //amount of lines

//                 char *adr = points[j][i].addressPoint;
//                 char temp = *adr;

//                 *adr  = ' ';
//                 adr -= (getAmountOfColumn() * 2) - 2;
//                 *adr = temp;

//                 points[j][i].addressPoint = adr;
//                 points[j][i].x += 1;
//                 points[j][i].y += 1;
//             }
//         }
//     } 

}

void startVectorMove() {

    for(int i = 0; i < 22; i++) {//amount of column
        for (int j = 0; j < 4; j++) { // amount of line

            char *adr = points[j][i].addressPoint;
            char temp = *adr;

            *adr  = ' ';
            adr += (getAmountOfColumn() * 2) - 2;
            *adr = temp;

            points[j][i].addressPoint = adr;
            points[j][i].x -= 1;
            points[j][i].y -= 1;
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
            frameBuffer = startAddress + (160 * (i + 1));
            screen++;
            i++;
            j = 0;
            continue;
        }
        
        *frameBuffer = *screen;
        *(frameBuffer + 1) = 0x7;

        initPoints(i, j, frameBuffer);

        frameBuffer += 2;
        screen++;

        j++;
    }

    
}

void initPoints(int i, int j, char *address) {

    int rowPosition = getAmountOfLine() - defineLine(address);
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


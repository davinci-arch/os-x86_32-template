#include "screensaver.h"

// xxx xxx\nx x x  \nx x xxx\nx x   x\nxxx xxx
// x x    x     x   x x  \nx   x   x   x    x   x\nx   x    x x     x   x\nx x       x      x x  
#define screensaverLetters "x x    x     x   x x  \nx   x   x   x    x   x\nx   x    x x     x   x\nx x       x      x x  ";

#define baseAddress 0xb8000;

char *startAddress = (char *) baseAddress;

int collision = 0;
int xN;
int yN;
int currentBound = -1;

void run(int x, int y) {
    
    initPoint(x, y);
    putPoint();
}


void initPoint (int x, int y) {

    point.width = 22;
    point.height = 4;

    if (x < 0) {
        x = 1;
    } else if (x + point.width > 80) {
        x = 80 - point.width;
    }

    if (y < 0) {
        y = 0;
    } else if  (y + point.height > 25) {
        y = 25 - point.height;
    }


    point.x = x;
    point.y = y;
    

}

void putPoint() {

    int pos = (160 * point.y) + (point.x * 2);

    char *letters = screensaverLetters;

    for (int i = 0; i < point.height; i++) {
        for (int j = 0; j < point.width; j++) {

            if (*letters == '\n') {
                pos += 160 - (point.width * 2);
                letters++;
            }
            
            startAddress[pos] = *letters;

            letters++;
            pos += 2;            
        }
    }

}

void move() {

    
    
    if (currentBound == -1) {
        xN = point.x;
        yN = point.y;
        changeDirection(point.x += 1, point.y += 1);
    }

    if (point.y == 0 || point.y + point.height == 25 ||
        point.x == 0 || point.x + point.width == 80) {
            
        
        
        

        if (point.y == 0) {
            currentBound = 0;

        } else if (point.y + point.height == 25) {
            currentBound = 1;

        } else if (point.x == 0) {
            currentBound = 2;
            
        } else if (point.x + point.width == 80) {
            currentBound = 3;
        }
        
    }


    if (currentBound == 0 && xN < point.x) {
        xN = point.x;
        yN = point.y;
        changeDirection(point.x += 1, point.y += 1);
        
    } else if (currentBound == 0 && xN > point.x) {
        xN = point.x;
        yN = point.y;
        changeDirection(point.x -= 1, point.y += 1);
        
    } else if (currentBound == 1 && xN < point.x) {
        xN = point.x;
        yN = point.y;
        changeDirection(point.x += 1, point.y -= 1);
        
    } else if (currentBound == 1 && xN > point.x) {
        xN = point.x;
        yN = point.y;
        changeDirection(point.x -= 1, point.y -= 1);
    } else if (currentBound == 2 && yN < point.y) {
        xN = point.x;
        yN = point.y;
        changeDirection(point.x += 1, point.y += 1);
    } else if (currentBound == 2 && yN > point.y) {
        xN = point.x;
        yN = point.y;
        changeDirection(point.x += 1, point.y -= 1);
    } else if (currentBound == 3 && yN < point.y) {
        xN = point.x;
        yN = point.y;
        changeDirection(point.x -= 1, point.y += 1);
    } else if (currentBound == 3 && yN > point.y) {
        xN = point.x;
        yN = point.y;
        changeDirection(point.x -= 1, point.y -= 1);
    }
        
    
    moveLeft();
}


/**
* if you want to move left, turn [point.x--/++, point.y--/++], posX = ... + ((point.x + i) * 2), startAddress[...] = startAddress(posX+ (160 * j) + 2 -+ 160) if up -160, else +160
* if you want to move right, turn [point.x--/++, point.y--/++], posX = ... + ((point.x + point.width - 1) * 2) - (i * 2), startAddress[...] = startAddress(posX+ (160 * j) - 2 -+ 160) if up -160, else +160;
*/
void moveLeft() {

    int posX = 0;

    // point.x += 1; // - move left, + move rigth
    // point.y += 1; // - move up, + move down

    // if (point.y >= 0 && point.x + point.width <= 80 &&
    //     point.y + point.height <= 25 && point.x + point.width <= 80) {

        for (int i = 0; i < point.width; i++) {

            if (xN < point.x) {

                posX = (160 * point.y) + ((point.x + point.width - 1) * 2) - (i * 2);

            } else if (xN > point.x) {

                posX = (160 * point.y) + ((point.x + i) * 2);

            }

            for (int j = 0; j < point.height; j++) {

                if (yN > point.y && xN < point.x) {
                    startAddress[posX + (160 * j)] = startAddress[posX + (160 * j) - 2 + 160]; // + 160 move up, -160 move down
                    startAddress[posX + (160 * j) - 2 + 160] = ' '; // + 160 move up, -160 move down

                } else if (yN < point.y && xN < point.x) {
                    startAddress[posX + (160 * j)] = startAddress[posX + (160 * j) - 2 - 160]; // + 160 move up, -160 move down
                    startAddress[posX + (160 * j) - 2 - 160] = ' '; // + 160 move up, -160 move down

                } else if (yN > point.y && xN > point.x) {
                    startAddress[posX + (160 * j)] = startAddress[posX + (160 * j) + 2 + 160]; // + 160 move up, -160 move down
                    startAddress[posX + (160 * j) + 2 + 160] = ' '; // + 160 move up, -160 move down

                }   else if (yN < point.y && xN > point.x) {
                    startAddress[posX + (160 * j)] = startAddress[posX + (160 * j) + 2 - 160]; // + 160 move up, -160 move down
                    startAddress[posX + (160 * j) + 2 - 160] = ' '; // + 160 move up, -160 move down
                }
                

            }
        }
    // }

}

void changeDirection(int x, int y) {
    point.x = x;
    point.y = y;
}




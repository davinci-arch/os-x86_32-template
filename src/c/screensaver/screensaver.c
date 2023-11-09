#include "screensaver.h"

// xxx xxx\nx x x  \nx x xxx\nx x   x\nxxx xxx
// x x    x     x   x x  \nx   x   x   x    x   x\nx   x    x x     x   x\nx x       x      x x  
#define screensaverLetters "x x    x     x   x x  \nx   x   x   x    x   x\nx   x    x x     x   x\nx x       x      x x  ";

#define baseAddress 0xb8000;

char *startAddress = (char *) baseAddress;

int collision = 0;
int currentXCollision;
int currentYCollistion;



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

/**
* if you want to move left, turn [point.x--/++, point.y--/++], posX = ... + ((point.x + 1) * 2), startAddress[...] = startAddress(posX+ (160 * j) + 2 -+ 160) if up -160, else +160
* if you want to move right, turn [point.x--/++, point.y--/++], posX = ... + ((point.x + point.width - 1) * 2) - (i - 2), startAddress[...] = startAddress(posX+ (160 * j) - 2 -+ 160) if up -160, else +160;
*/
void moveLeft() {

    int posX = 0;

    point.x += 1; // - move left, + move rigth
    point.y -= 1; // - move up, + move down
    // TODO: define method that will help move to right side 
    if (point.y >= 0 && point.x + point.width <= 80) {

        for (int i = 0; i < point.width; i++) {

            posX = (160 * point.y) + ((point.x + point.width - 1) * 2) - (i * 2);

            for (int j = 0; j < point.height; j++) {
                startAddress[posX + (160 * j)] = startAddress[posX + (160 * j) - 2 + 160]; // + 160 move up, -160 move down
                startAddress[posX + (160 * j) - 2 + 160] = ' '; // + 160 move up, -160 move down

            }
        }
    }

}




#include "screensaver.h"

// #define screensaverLetters "xxx xxx\nx x x  \nx x xxx\nx x   x\nxxx xxx"
#define screensaverLetters "x x    x     x   x x  \nx   x   x   x    x   x\nx   x    x x     x   x\nx x       x      x x  ";


#define baseAddress 0xb8000;

char *startAddress = (char *) baseAddress;

int collision = -1;
int xN;
int yN;


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
            startAddress[pos + 1] = 0x3;
            letters++;
            pos += 2;            
        }
    }

}

void move() {

    if (collision == -1) {
        changeDirection(1, -1);
        collision = 0;
    }

    if (collision == 0 && point.x > 0 && (point.x + point.width) < 80 &&
        point.y > 0 && (point.y + point.height) < 25 &&
        (point.y != 0 && (point.x + point.width) != 80) &&
        (point.y != 0 && point.x != 0) &&
        (point.y != 25 && (point.x + point.width) != 80) &&
        (point.y != 25 && point.x != 0)) {
        
        moveNext();

    } else {
        collision = 1;

        if ((point.y == 0 && (point.x + point.width)) == 80 ||
            (point.y == 0 && point.x == 0) ||
            (point.y == 25 && (point.x + point.width) == 80) ||
            (point.y == 25 && point.x == 0)) {

            changeDirection(-xN, -yN);

        } else if (point.x == 0 || (point.x + point.width) == 80) {

            changeDirection(-xN, yN);

        } else if (point.y == 0 || (point.y + point.height) == 25) {

            changeDirection(xN, -yN);
        } 
        
        collision = 0;
        moveNext();
    }

    
}

int position;
int nextX;


void moveNext() {

        for (int i = 0; i < point.height; i++) {

            if (xN == -1 && yN == 1) {
                position = ((160 * (point.y + point.height - 1 - i)) + point.x * 2);

            } else if (xN == -1 && yN == -1) {

                position = (160 * (point.y + i)) + point.x * 2;
            } else if (xN == 1 && yN == 1) {

                position = (160 * (point.y + point.height - 1 - i)) + (point.x + point.width - 1) * 2;

            } else if (xN == 1 && yN == -1) {
                position = (160 * (point.y + i)) + (point.x + point.width - 1) * 2;
            }

            for (int j = 0; j < point.width; j++) {

                if (xN == -1 && yN == 1) {

                    nextX = (position + 2 * j) + 160 - 2;
                    startAddress[nextX] = startAddress[position + 2 * j];
                    startAddress[nextX+1] = startAddress[position + 2 * j + 1];
                    startAddress[position + 2 * j] = ' ';
                    startAddress[position + 2 * j + 1] = 0x7;

                } else if (xN == -1 && yN == -1) {

                    nextX = (position + 2 * j) - 160 - 2;
                    startAddress[nextX] = startAddress[position + 2 * j];
                    startAddress[nextX+1] = startAddress[position + 2 * j+1];

                    startAddress[position + 2 * j] = ' ';
                    startAddress[position + 2 * j + 1] = 0x7;

                } else if (xN == 1 && yN == 1) {

                    nextX = (position - 2 * j) + 160 + 2;
                    startAddress[nextX] = startAddress[position - 2 * j];
                    startAddress[nextX+1] = startAddress[position - 2 * j+1];

                    startAddress[position - 2 * j] = ' ';
                    startAddress[position - 2 * j + 1] = 0x7;

                } else if (xN == 1 && yN == -1) {

                    nextX = (position - 2 * j) - 160 + 2;
                    startAddress[nextX] = startAddress[position - 2 * j];
                    startAddress[nextX+1] = startAddress[position - 2 * j+1];

                    startAddress[position - 2 * j] = ' ';
                    startAddress[position - 2 * j + 1] = 0x7;

                }
            }
        }
        point.x += xN;
        point.y += yN;

}



void changeDirection(int x, int y) {
    xN = x;
    yN = y;
}




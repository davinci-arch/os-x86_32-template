#ifndef SCREENSAVER_H
#define SCREENSAVER_H

struct ScreenSaverPoint {
    int x;
    int y;
    int width;
    int height;
} point;


void run();
void moveLeft();
void move();
void changeDirection(int x, int y);
void moveNext();
#endif SCREENSAVER_H
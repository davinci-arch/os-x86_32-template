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

#endif SCREENSAVER_H
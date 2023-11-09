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
#endif SCREENSAVER_H
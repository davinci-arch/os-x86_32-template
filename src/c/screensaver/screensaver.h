#ifndef SCREENSAVER_H
#define SCREENSAVER_H

struct ScreenSaverPoint {
    char *addressPoint;
    int x;
    int y;

} points[4][22];


void printSaver(char *startAddress);
void moveLeftBottom();
#endif SCREENSAVER_H
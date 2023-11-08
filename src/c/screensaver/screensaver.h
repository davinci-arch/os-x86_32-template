#ifndef SCREENSAVER_H
#define SCREENSAVER_H

struct ScreenSaverPoint {
    char *addressPoint;
    int x;
    int y;

} points[2][2];


void printSaver(char *startAddress);
void moveLeftBottom();
#endif SCREENSAVER_H
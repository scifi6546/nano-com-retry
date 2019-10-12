#include <string>
#include <SDL2/SDL.h>
#ifndef Display_H
#define Display_H
int initDisplay(int width, int height, std::string title);
void updateDisplay();
void delDisplay();
void clearDisplay(float r, float g, float b, float a);
char getKey();


#endif
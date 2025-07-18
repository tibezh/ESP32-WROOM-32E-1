#ifndef DISPLAY_H
#define DISPLAY_H

#include <U8g2lib.h>

// Define display object as extern
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;

// Functions define.
void displayInit();
void displayClear();
void displayShowText(const char* text, int x, int y);
void displayShowNumber(int number, int x, int y);
void displayShowBootScreen();
void displayShowCounter(int count);
void displayUpdate();

#endif

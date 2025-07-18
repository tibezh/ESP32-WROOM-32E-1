#include "display.h"

// Create display object.
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void displayInit() {
    u8g2.begin();
    u8g2.clearBuffer();
    u8g2.sendBuffer();
}

void displayClear() {
    u8g2.clearBuffer();
}

void displayShowText(const char* text, int x, int y) {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(x, y, text);
}

void displayShowNumber(int number, int x, int y) {
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.setCursor(x, y);
    u8g2.print(number);
}

void displayShowBootScreen() {
    displayClear();
    
    // Inverse title.
    u8g2.drawBox(0, 0, 128, 20);
    u8g2.setDrawColor(0);
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(18, 14, "ESP32 BOOT");
    u8g2.setDrawColor(1);
    
    // Loading text.
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(28, 44, "Loading...");
    
    displayUpdate();
}

void displayShowCounter(int count) {
    displayClear();
    
    // Title in yellow zone
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 10, "Button counter:");
    
    // Number in blue zone
    u8g2.setFont(u8g2_font_ncenB18_tr);
    u8g2.setCursor(40, 45);
    u8g2.print(count);
    
    displayUpdate();
}

void displayUpdate() {
    u8g2.sendBuffer();
}
#include <Arduino.h>
#include "display.h"
#include "common.h"

#define LED 2

#define BUTTON_YEL 4
#define BUTTON_RED 15

#define GLOBAL_DELAY 20

#define RESET_COUNTER_VALUE 150

int counter = 0;
int resetCounter = 0;

bool lastYelButtonState = HIGH;
bool lastRedButtonState = HIGH;


void setup() {
    // Init Serial.
    Serial.begin(115200);
    while (!Serial) { ; }
    delay(1000);
    
    pinMode(LED, OUTPUT);

    pinMode(BUTTON_YEL, INPUT_PULLUP);
    pinMode(BUTTON_RED, INPUT_PULLUP);
    
    Serial.println("Starting...");
    
    // Init the display.
    displayInit();
    displayShowBootScreen();
    delay(2000);
    
    // Show initial counter screen.
    showCounter(counter);
}

void loop() {
    bool currentYelButtonState = digitalRead(BUTTON_YEL);
    bool currentRedButtonState = digitalRead(BUTTON_RED);
    
    // Increase counter.
    if (lastYelButtonState == HIGH && currentYelButtonState == LOW) {
        counter++;
        digitalWrite(LED, HIGH);
        showCounter(counter);
    }
    else if (lastYelButtonState == LOW && currentYelButtonState == HIGH) {
        digitalWrite(LED, LOW);
    }

    // Decrease counter.
    if (lastRedButtonState == HIGH && currentRedButtonState == LOW) {
        counter--;
        digitalWrite(LED, HIGH);
        showCounter(counter);
    }
    else if (lastRedButtonState == LOW && currentRedButtonState == HIGH) {
        digitalWrite(LED, LOW);
    }

    // Reset counter.
    if (currentYelButtonState == LOW && currentRedButtonState == LOW) {
        resetCounter++;
    }
    else {
        resetCounter = 0;
    }

    if (resetCounter == RESET_COUNTER_VALUE) {
        counter = 0;
        resetCounter = 0;
        showCounter(counter);
    }
    
    lastYelButtonState = currentYelButtonState;
    lastRedButtonState = currentRedButtonState;

    delay(GLOBAL_DELAY);
}



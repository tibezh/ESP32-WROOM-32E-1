#include <Arduino.h>
#include "display.h"
#include "common.h"


#define LED 2
#define BUTTON 4
#define GLOBAL_DELAY 20
#define RESET_COUNTER_VALUE 60

int counter = 0;
int resetCounter = 0;
bool lastButtonState = HIGH;


void setup() {
    Serial.begin(115200);
    while (!Serial) { ; }
    delay(1000);
    
    pinMode(LED, OUTPUT);
    pinMode(BUTTON, INPUT_PULLUP);
    
    Serial.println("Starting...");
    
    // Init the display.
    displayInit();
    displayShowBootScreen();
    delay(2000);
    
    // Show initial counter screen.
    showCounter(counter);
}

void loop() {
    bool currentButtonState = digitalRead(BUTTON);
    
    if (lastButtonState == HIGH && currentButtonState == LOW) {
        counter++;
        digitalWrite(LED, HIGH);
        showCounter(counter);
    }
    else if (lastButtonState == LOW && currentButtonState == HIGH) {
        digitalWrite(LED, LOW);
    }

    if (currentButtonState == LOW) {
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
    
    lastButtonState = currentButtonState;
    delay(GLOBAL_DELAY);
}



#include <Arduino.h>

#include "display.h"
#include "common.h"

#define LED 2

#define BUTTON_YEL 4
#define BUTTON_RED 15

#define GLOBAL_DELAY 20

#define RESET_COUNTER_VALUE 60

int counter = 0;
int resetCounter = 0;
const char* resetMessage = "Reset in";

bool lastYelButtonState = HIGH;
bool lastRedButtonState = HIGH;


void setup() {
    // Init Serial.
    Serial.begin(115200);
    while (!Serial) { ; }
    delay(1000);

    initStorage();
    
    pinMode(LED, OUTPUT);

    pinMode(BUTTON_YEL, INPUT_PULLUP);
    pinMode(BUTTON_RED, INPUT_PULLUP);
    
    Serial.println("Starting...");
    
    // Init the display.
    displayInit();
    displayShowBootScreen();
    delay(2000);

    counter = getCounter();
    
    // Show initial counter screen.
    showCounter(counter);
}

void loop() {
    bool currentYelButtonState = digitalRead(BUTTON_YEL);
    bool currentRedButtonState = digitalRead(BUTTON_RED);
    
    // Increase counter.
    if (currentRedButtonState == HIGH) {
        if (lastYelButtonState == HIGH && currentYelButtonState == LOW) {
            if (updateCounter(counter, UpdateCounterMode::AVERS)) {
                digitalWrite(LED, HIGH);
                showCounter(counter);
            }
        }
        else if (lastYelButtonState == LOW && currentYelButtonState == HIGH) {
            digitalWrite(LED, LOW);
        }
    }

    // Decrease counter.
    if (currentYelButtonState == HIGH) {
        if (lastRedButtonState == HIGH && currentRedButtonState == LOW) {
            if (updateCounter(counter, UpdateCounterMode::REVERSE)) {
                digitalWrite(LED, HIGH);
                showCounter(counter);
            }
        }
        else if (lastRedButtonState == LOW && currentRedButtonState == HIGH) {
            digitalWrite(LED, LOW);
        }
    }

    // Reset counter.
    if (currentYelButtonState == LOW && currentRedButtonState == LOW && counter != 0) {
        displayClear();
        displayShowText(resetMessage, 5, 30);
        
        int resetCounterNumber = 3 - ceil(resetCounter / 20);
        char resetCounterNumberValue[2];
        sprintf(resetCounterNumberValue, "%d", resetCounterNumber);
        displayShowText(resetCounterNumberValue, 70, 30);

        displayShowText(resetCounterNumberValue, 70, 30);
        displayUpdate();
        resetCounter++;
    }
    else if (resetCounter > 0) {
        resetCounter = 0;
        showCounter(counter);
    }

    if (resetCounter == RESET_COUNTER_VALUE) {
        if (updateCounter(counter, UpdateCounterMode::RESET)) {
            resetCounter = 0;
            showCounter(counter);
        }
    }
    
    lastYelButtonState = currentYelButtonState;
    lastRedButtonState = currentRedButtonState;

    delay(GLOBAL_DELAY);
}

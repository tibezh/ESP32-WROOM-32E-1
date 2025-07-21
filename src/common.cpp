#include "common.h"
#include "display.h"
#include <Preferences.h>

Preferences preferences;

void showCounter(int counter) {
    displayShowCounter(counter);
    Serial.print("Counter: ");
    Serial.println(counter);
}

void showError(const char* message) {
    Serial.println(message);
    displayShowText(message, 5, 30);
}

bool updateCounter(int &counter, UpdateCounterMode mode) {
    if (mode == UpdateCounterMode::AVERS) {
        counter++;
    }
    else if (mode == UpdateCounterMode::REVERSE) {
        counter--;
    }
    else if (mode == UpdateCounterMode::RESET) {
        counter = 0;
    }
    else {
        showError("Undefined mode");
        return false;
    }
    preferences.putInt("counter_val", counter);
    return true;
}

void initStorage() {
    preferences.begin("counter-app", false);
}

int getCounter() {
    return preferences.getInt("counter_val", 0);
}

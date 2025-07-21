#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h> 
#include <Preferences.h>

void showCounter(int counter);

void showError(const char* message);

enum class UpdateCounterMode {
    AVERS,
    REVERSE,
    RESET
};
bool updateCounter(int &counter, UpdateCounterMode direction);

void initStorage();

int getCounter();

#endif

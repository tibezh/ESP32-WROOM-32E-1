#include "common.h"
#include "display.h"

void showCounter(int counter) {
    displayShowCounter(counter);
    Serial.print("Counter: ");
    Serial.println(counter);
}
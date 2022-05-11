#include <Arduino.h>
#include "../config.h"
#include "buttons.h"

bool rightPressed() {
  return digitalRead(RIGHT_BUTTON_PIN) == HIGH;
}

bool startButtonDebounce = false;
bool startPressed() {
  if (digitalRead(START_BUTTON_PIN) == HIGH && startButtonDebounce == false) {
    startButtonDebounce == true;
  }
  if (digitalRead(START_BUTTON_PIN) == LOW && startButtonDebounce == true) {
    startButtonDebounce == false;
  }
  return startButtonDebounce;
}

void initButtons() {
  pinMode(RIGHT_BUTTON_PIN, INPUT);
  pinMode(START_BUTTON_PIN, INPUT);
}

#include <Arduino.h>
#include <Stepper.h>
#include <math.h>
#include "../config.h"
#include "dial.h"
#include "debug.h"

#define STEPS_PER_TICK STEPS_PER_REVOLUTION / 40.0

Stepper dialStepper = Stepper(STEPS_PER_REVOLUTION, STEPPER_PIN1, STEPPER_PIN2, STEPPER_PIN3, STEPPER_PIN4);

float stepperPosition = 0;

// used to get back to 0 after each combination to avoid error creep
float stepsFromZero = 0.0;

void initDial() {
  dialStepper.setSpeed(STEPPER_RPM);
}

// To counteract rounding drift, keep track of our position relative to boot-time origin
// as a float, and round the delta to an int for the actual move.
void moveStepper(float delta) {
  float newPos = stepperPosition + delta;
  int steps = round(newPos - stepperPosition);
  stepperPosition = newPos;
  stepsFromZero += delta;
  // This method blocks until the stepper has moved as requested.
  dialStepper.step(steps);
}

void setDialZero() {
  stepsFromZero = 0;
}

void moveStepperToZero() {
  DEBUG("returning to zero");
  DEBUG(-stepsFromZero);
  moveStepper(-stepsFromZero);
}

void moveDialBy(int ticks) {
  float exactSteps = STEPS_PER_TICK * ticks;
  DEBUG("exact steps");
  DEBUG(exactSteps);
  moveStepper(exactSteps);
  DEBUG("steps from zero");
  DEBUG(stepsFromZero);
  delay(200);
}

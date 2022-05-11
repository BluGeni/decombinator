#include <Arduino.h>
#include <Servo.h>
#include "../config.h"
#include "clasp.h"
#include "debug.h"

// Actuator to pull on the clasp
Servo claspServo;

// Whether the lock has opened.  This will latch to `true` once the lock button has been pushed.
bool lockSwitchState = false;

// Interrupt handler for the unlock button
void int__unlocked() {
  DEBUG("Combo found!");
  lockSwitchState = true;
}

void initClasp() {
  pinMode(UNLOCK_BUTTON_PIN, INPUT_PULLUP);
  // Enable the internal pullup
  digitalWrite(UNLOCK_BUTTON_PIN, HIGH);
  
  // For the unlock button, trigger an interrupt when button pressed, but not when released.
  attachInterrupt(digitalPinToInterrupt(UNLOCK_BUTTON_PIN), int__unlocked, CHANGE);

  // Initialize the clasp servo
  claspServo.attach(SERVO_PIN);
  claspServo.write(SERVO_IDLE);
}

bool lockHasOpened() {
  return lockSwitchState;
}

void resetLockState() {
  lockSwitchState = false;
}

void tugClasp() {
  claspServo.write(SERVO_OPEN);
  // Wait so that the servo can actuate and the interrupt has a chance to fire
  delay(1000);
  // Release
  claspServo.write(SERVO_IDLE);
  // Give the servo time to do its thing
  delay(2000);
}

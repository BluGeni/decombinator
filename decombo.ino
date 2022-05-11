#include "config.h"
#include "src/display.h"
#include "src/dial.h"
#include "src/clasp.h"
#include "src/buttons.h"
#include "src/decombo.h"
#include "src/debug.h"

void setup() {
  initButtons();  
  initClasp();
  initDisplay();
  initDial();
  DEBUG_INIT;
}

void loop() {
  displayMessage("Decombinator");

  if (startPressed()) {
    DEBUG("Start Pressed");
    bruteForce();
  }

  if (rightPressed()) {
    DEBUG("move 1 number right");
    moveDialBy(-1);
    // Make the new position "zero"
    setDialZero();
    // Give the user time to let go of the button
    delay(100);
  }
}

#include "../config.h"
#include "decombo.h"
#include "types.h"
#include "display.h"
#include "dial.h"
#include "clasp.h"
#include "debug.h"

void tryCombo(combo_t combo) {
  displayCombo("Attempting:", combo);
  delay(200);

  // turn right twice to clear lock
  DEBUG("resetting by turning twice to 0");
  moveDialBy(-80);

  delay(200);

  // turn to first number
  DEBUG("turning to first number");
  DEBUG(combo[0]);

  moveDialBy(combo[0] - 40);

  // Rotate left by 1 full rotation
  moveDialBy(40);

  // turn to second number
  DEBUG("turning to second number");
  DEBUG(combo[1]);

  int a = 0;
  if (combo[0] > combo[1]) {
    a = 40;
  }
  moveDialBy(a + (40 - (combo[0] - combo[1])));

  // turn to third number
  
  DEBUG("turning to third number");
  DEBUG(combo[2]);
  DEBUG("third - second");
  DEBUG(combo[2] - combo[1]);

  if (combo[1] > combo[2]) {
    moveDialBy(combo[2] - combo[1]);
  } else {
    moveDialBy((combo[2] - combo[1]) - 40);
  }

  // Try opening lock
  tugClasp();

  // Display the code if the "unlocked" button was pushed.
  if (lockHasOpened()) {
    displayCombo("Code is:", combo);
    exit(0);
  }

  // return to zero
  moveStepperToZero();
  delay(500);
}

void bruteForce() {
  resetLockState();
  combo_t combo = { 0, 0, 0 };
  for (combo[3] = 0; combo[3] < 40; combo[3]++) {
    for (combo[0] = combo[3] % 4; combo[0] < 40; combo[0] += 4) {
      for (combo[1] = combo[0] + 2; combo[1] < 40; combo[1] += 4) {
        DEBUG("Trying combo:");
        DEBUG(COMBO_STRING(combo));
        DEBUG("-----");
        tryCombo(combo);
      }
    }
  }
}

#ifndef CONFIG_H
#define CONFIG_H

// To enable SSD1306
// If you just want a lock brute and don't care about displaying the code,
// or you plan on using serial as your feedback, you can disable this.
#define DISPLAY_SSD1306

// To enable interface output to serial, uncomment
#define DISPLAY_SERIAL

// Vars needed for an SSD1306 display
#ifdef DISPLAY_SSD1306
  // Edit the following file to configure an SSD1306 display
  #include "config_ssd1306.h"
#endif

// TODO: other displays and their concerns

// Stepper motor config

// Pins
#define STEPPER_PIN1 8
#define STEPPER_PIN2 10
#define STEPPER_PIN3 9
#define STEPPER_PIN4 11

// Varies per stepper, and is often not what's on the datasheet.
#define STEPS_PER_REVOLUTION 2038

// Stepper speed
#define STEPPER_RPM 12

// Pin number for the servo
#define SERVO_PIN 6

// Servo value for "try to open the lock"
#define SERVO_OPEN 100

// Servo value for "stop trying"
#define SERVO_IDLE 10

// Pin number for the "move right" button
#define RIGHT_BUTTON_PIN 4

// Pin number for the "start" button
#define START_BUTTON_PIN 3

// Pin number for the "unlock" button / sensor
#define UNLOCK_BUTTON_PIN 2

// Comment out to disable the serial debug output
#define DEBUGGING

#endif


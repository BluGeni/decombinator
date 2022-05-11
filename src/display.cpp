#include "../config.h"
#include "display.h"
#include "debug.h"

#ifdef DISPLAY_SSD1306
  #include <Adafruit_SSD1306.h>
  Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, DISPLAY_OLED_RESET);
#endif

#ifdef DISPLAY_SERIAL
  #include <Arduino.h>
#endif

void initDisplay() {
  #ifdef DISPLAY_SSD1306
    if (!display.begin(DISPLAY_SSD1306_VCC, DISPLAY_I2C_ADDRESS)) {
      DEBUG(F("SSD1306 allocation failed"));
      for (;;); // Don't proceed, loop forever
    }
  #endif
  // Avoid calling Serial.begin twice
  #ifdef DISPLAY_SERIAL && !DEBUGGING
    Serial.begin(9600);
  #endif
}

void _displayMessage(String message) {
  #ifdef DISPLAY_SSD1306
    display.fillScreen(DISPLAY_BACKGROUND);
    display.setTextSize(1);
    display.setTextColor(DISPLAY_MESSAGE);
    display.setCursor(2, 2);
    display.println(message);
  #endif
  #ifdef DISPLAY_SERIAL
    Serial.println(message);
  #endif
}

void displayMessage(String message) {
  _displayMessage(message);
  #ifdef DISPLAY_SSD1306
    display.display();
  #endif
}

void displayCombo(String message, combo_t combo) {
  _displayMessage(message);
  #ifdef DISPLAY_SSD1306
    display.setCursor(3, 15);
    display.setTextSize(2);
    display.setTextColor(DISPLAY_CODE);
    display.println(COMBO_STRING(combo));
    display.display();
  #endif
  #ifdef DISPLAY_SERIAL
    Serial.println(COMBO_STRING(combo));
  #endif
}

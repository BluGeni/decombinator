#ifndef DEBUG_H
#define DEBUG_H


#include "../config.h"

#ifdef DEBUGGING
  #include <Arduino.h>
  #define DEBUG(message) \
    Serial.print("[DEBUG] "); \
    Serial.println(message)
  #define DEBUG_INIT \
    Serial.begin(9600); \
    Serial.println("Debugging enabled")
#else
  #define DEBUG(message)
  #define DEBUG_INIT
#endif

#endif

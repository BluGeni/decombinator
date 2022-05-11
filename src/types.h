#ifndef TYPES_H
#define TYPES_H

#include <Arduino.h>

typedef uint8_t combo_t[3];
#define COMBO_STRING(combo) (String(combo[0]) + "-" + String(combo[1]) + "-" + String(combo[2]))

#endif

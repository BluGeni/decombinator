#ifndef CONFIG_SSD1306_H
#define CONFIG_SSD1306_H

// Voltage source: screen-internal power supply (3.3v)
#define DISPLAY_SSD1306_VCC SSD1306_SWITCHCAPVCC
// To use your own 3.3v source, comment above and uncomment below
// #define DISPLAY_VCC SSD1306_EXTERNALVCC

// OLED display width, in pixels
#define DISPLAY_WIDTH 128
// OLED display height, in pixels
#define DISPLAY_HEIGHT 32
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// Reset pin # (or -1 if sharing Arduino reset pin)
#define DISPLAY_OLED_RESET -1
// See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define DISPLAY_I2C_ADDRESS 0x3C

// Colors
#define DISPLAY_BACKGROUND SSD1306_BLACK
#define DISPLAY_MESSAGE SSD1306_WHITE
#define DISPLAY_CODE SSD1306_WHITE

#endif

#ifndef HARDWAREPINS_h
#define HARDWAREPINS_h

#define VOLTAGE_CHECK_PIN 27

#define SD_CS 14

/**
 * TFT DISPLAY Pin Configuration
 * -----------------
 * Note* If the display isn't working, it's likely the pins aren't configured properly.
 */
 #define DC_TFT_SCK 18
 #define DC_TFT_MOSI 23 // In some display driver board, it might be written as "SDA" and so on.
 #define DC_TFT_MISO 19
 #define DC_TFT_CS   13  // Chip select control pin
 #define DC_TFT_DC   12  // Data Command control pin
 #define DC_TFT_RST  2  // Reset pin (could connect to Arduino RESET pin)
 #define DC_TFT_BL   22

#endif /* _HARDWAREPINS_H_ */

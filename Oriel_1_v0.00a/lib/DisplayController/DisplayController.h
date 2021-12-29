/**
 * @file Display.h
 * @author Marcus Jefferson (you@domain.com)
 * @brief Wraps definitions and logic related to the device display
 * @version 0.1
 * @date 2021-12-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef DISPLAY_CONTROLLER_h
#define DISPLAY_CONTROLLER_h

#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <JpegClass.h>

// #define JSON "json"
// #define JPEG "jpeg"

// #define SD_CS 14
// #define VOLTAGE_PIN 27
// #define VOLTAGE_DIVIDER_R 51000

// #define JSON_FILE_BUFFER 1024

// #define ORIEL_CONFIG_FILENAME "/oriel_config.json"
// #define IMAGE_FOLDER_NAME "/image_downloads"

struct DisplayTheme {
  uint16_t background_color;
  uint16_t text_color;
};

/**
 * Pin Configuration
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

class DisplayController {
  private:
    static JpegClass jpegClass;
    Arduino_DataBus *bus = new Arduino_ESP32SPI(DC_TFT_DC, DC_TFT_CS, DC_TFT_SCK, DC_TFT_MOSI, DC_TFT_MISO);
    Arduino_GFX *gfx = new Arduino_ST7789(bus, 2, 0, false);
  public:
    DisplayTheme defaultTheme = { WHITE, BLACK };
    void initDisplay();
    void clearDisplay();
    void applyTheme();
};

#endif /* _DISPLAY_CONTROLLER_H_ */

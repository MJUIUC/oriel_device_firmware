/**
 * @file GraphicsController.h
 * @author Marcus Jefferson (you@domain.com)
 * @brief Wraps definitions and logic related to the device display
 * @version 0.1
 * @date 2021-12-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef GRAPHICS_CONTROLLER_h
#define GRAPHICS_CONTROLLER_h

#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <JpegClass.h>
#include <DeviceConfig.h>
#include <HardwarePins.h>

// #define JSON "json"
// #define JPEG "jpeg"

// #define VOLTAGE_PIN 27
// #define VOLTAGE_DIVIDER_R 51000

// #define JSON_FILE_BUFFER 1024

class GraphicsController {
  private:
    static JpegClass jpegClass;
    Arduino_DataBus *bus = new Arduino_ESP32SPI(DC_TFT_DC, DC_TFT_CS, DC_TFT_SCK, DC_TFT_MOSI, DC_TFT_MISO);
    /* Device Theme related vars */
    uint16_t display_background_color;
    uint16_t display_text_color;
  public:
    Arduino_GFX *Display = new Arduino_ST7789(bus, 2, 0, false);
    DisplayTheme defaultTheme = { BLACK, OLIVE };
    void initDisplay();
    void clearDisplay();
    void applyDisplayTheme(struct DisplayTheme *theme);
};

#endif /* _DISPLAY_CONTROLLER_H_ */

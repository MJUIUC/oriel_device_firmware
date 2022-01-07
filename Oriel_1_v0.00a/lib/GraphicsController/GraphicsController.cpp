#include <GraphicsController.h>
#include <OrielFirmware.h>

void GraphicsController::initDisplay(){
  this->Display->begin();
  this->Display->invertDisplay(1);
  this->applyDisplayTheme(&this->defaultTheme);
  this->Display->printf("Oriel Mira %d\n", DEVICE_VERSION);
  this->Display->printf("Firmware Version %s\n", FIRMWARE_VERSION);
}

void GraphicsController::clearDisplay(){
  this->Display->fillScreen(this->display_background_color);
  this->Display->setCursor(0,0);
}

void GraphicsController::applyDisplayTheme(struct DisplayTheme *theme){
  this->display_background_color = theme->background_color;
  this->display_text_color = theme->text_color;
  this->Display->fillScreen(theme->background_color);
  this->Display->setTextColor(theme->text_color);
}

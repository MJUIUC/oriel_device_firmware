#include <DisplayController.h>
#include <OrielFirmware.h>

void DisplayController::initDisplay(){
  this->gfx->begin();
  this->gfx->invertDisplay(1);
  this->applyDisplayTheme(&this->defaultTheme);
  this->gfx->printf("Oriel Mira %i\n", DEVICE_VERSION);
  this->gfx->printf("Firmware Version %s\n", FIRMWARE_VERSION);
}

void DisplayController::print(char * text){
  this->gfx->print(text);
}

void DisplayController::clearDisplay(){
  this->gfx->fillScreen(this->display_background_color);
}

void DisplayController::applyDisplayTheme(struct DisplayTheme *theme){
  this->display_background_color = theme->background_color;
  this->display_text_color = theme->text_color;
  this->gfx->fillScreen(theme->background_color);
  this->gfx->setTextColor(theme->text_color);
}

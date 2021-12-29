#include <DisplayController.h>

void DisplayController::initDisplay(){
  this->gfx->begin();
  this->gfx->fillScreen(WHITE);
  this->gfx->setTextColor(BLACK);
}

void DisplayController::clearDisplay(){
  this->gfx->fillScreen(WHITE);
}

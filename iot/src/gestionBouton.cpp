#include "gestionBouton.h"

const unsigned long DEBOUNCE_TIME = 50;

bool isButtonPressed(Button &b) {
  if (millis() - b.lastRead >= DEBOUNCE_TIME) {
    b.lastRead = millis();
    b.state = digitalRead(b.pin) == LOW;
  }
  return b.state;
}
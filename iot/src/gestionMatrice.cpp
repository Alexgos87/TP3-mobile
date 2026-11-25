#include "gestionMatrice.h"

uint16_t flashColor = 0;
int nbFlash = 0;
bool isOn = false;
unsigned long lastTime = 0;

void flashMatrix(uint16_t c, bool forever) {
  flashColor = c;
  if (forever) {
    nbFlash = -1;
  } else {
    nbFlash = 3;
  }
  isOn = false;
}

void updateFlash() {
  if (nbFlash == 0 || millis() - lastTime < 200) return;

  lastTime = millis();
  isOn = !isOn;
  if (isOn) {
    fillMatrix(flashColor);
  } else {
    fillMatrix(0);
  }
  if (!isOn && nbFlash > 0) nbFlash--;
}

void fillMatrix(uint16_t c) {
  matrix.fillScreen(c);
  matrix.show();
}

bool isFlashing() {
  return nbFlash != 0;
}
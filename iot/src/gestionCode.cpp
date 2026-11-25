#include "gestionCode.h"

int code[4];
int digit = 0;
int position = 0;
bool wasAPressed = false;
bool wasBPressed = false;

int savedCode[4];

void startEnteringCode() {
  digit = 0;
  position = 0;
  display.clear();
  display.showNumberDec(0, false, 1, 0);
  wasAPressed = true;
  wasBPressed = true;
}

bool enterCode() {
  bool isAPressed = isButtonPressed(btnA);
  bool isBPressed = isButtonPressed(btnB);
  bool done = false;

  if (isAPressed && !wasAPressed) {
    digit = (digit + 1) % 10;
    display.showNumberDec(digit, false, 1, position);
  }

  if (isBPressed && !wasBPressed) {
    code[position] = digit;
    position++;
    if (position == 4) {
      done = true;
    } else {
      digit = 0;
      display.showNumberDec(0, false, 1, position);
    }
  }

  wasAPressed = isAPressed;
  wasBPressed = isBPressed;
  return done;
}

bool sameCode(int a[4], int b[4]) {
  for (int i = 0; i < 4; i++) {
    if (a[i] != b[i]) return false;
  }
  return true;
}
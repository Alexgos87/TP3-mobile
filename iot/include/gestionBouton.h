#pragma once
#include <Arduino.h>

struct Button {
  int pin;
  bool state;
  unsigned long lastRead;
};

bool isButtonPressed(Button &b);
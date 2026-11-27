#pragma once
#include <Arduino.h>

#define DEL1_PIN 5
#define DEL2_PIN 16
#define DEL3_PIN 34

void initDels();
void setDels(bool del1, bool del2, bool del3);
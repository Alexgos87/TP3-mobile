#pragma once
#include <Arduino.h>
#include <TM1637Display.h>
#include "gestionBouton.h"

extern TM1637Display display;
extern Button btnA;
extern Button btnB;
extern int code[4];
extern int savedCode[4];


void startEnteringCode();
bool enterCode();
bool sameCode(int a[4], int b[4]);
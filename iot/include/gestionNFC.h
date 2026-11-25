#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PN532.h>

extern Adafruit_PN532 nfc;

bool initNFC();
bool lireTag(uint8_t* uid, uint8_t* uidLength);
void afficherUID(uint8_t* uid, uint8_t uidLength);
#pragma once
#include <Arduino.h>
#include <ESP32Servo.h>

extern Servo servo;

void lockServo();
void unlockServo();
void updateServo();
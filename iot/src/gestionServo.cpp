#include "gestionServo.h"

const unsigned long SERVO_TIME = 250;

bool isServoMoving = false;
unsigned long servoStart = 0;

void lockServo() {
  servo.write(180);
  isServoMoving = true;
  servoStart = millis();
}

void unlockServo() {
  servo.write(0);
  isServoMoving = true;
  servoStart = millis();
}

void updateServo() {
  if (isServoMoving && millis() - servoStart >= SERVO_TIME) {
    servo.write(90);
    isServoMoving = false;
  }
}
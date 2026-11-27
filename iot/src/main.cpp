#include <Arduino.h>
#include <Wire.h>
#include "DHT.h"
#include <TM1637Display.h>
#include <Adafruit_NeoMatrix.h>
#include <ESP32Servo.h>
#include <Adafruit_PN532.h>
#include "gestionMatrice.h"
#include "gestionBouton.h"
#include "gestionCode.h"
#include "gestionServo.h"
#include "gestionNFC.h"
#include "gestionMouvement.h"
#include "gestionFirestore.h"
#include "gestionDel.h"
#include "stateMachine.h"

// sans cette ligne, l'ESP32 plante a cause de Firebase
SET_LOOP_TASK_STACK_SIZE(16 * 1024);

//ecran 4 digits
#define CLK_PIN 25
#define DIO_PIN 26

//capteur temp
#define DHT_TYPE DHT22
#define DHT_PIN 16

//matrice
#define MATRIX_PIN 27
#define BRIGHTNESS 10

//servo
#define SERVO_PIN 13

//lecteur nfc
#define SDA_PIN 18
#define SCL_PIN 19

//boutons (A = rouge, B = blanc)
#define BTN_PIN_A 23
#define BTN_PIN_B 14

TM1637Display display(CLK_PIN, DIO_PIN);
DHT dht(DHT_PIN, DHT_TYPE);
Adafruit_NeoMatrix matrix(8, 8, MATRIX_PIN,
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS +
  NEO_MATRIX_PROGRESSIVE, NEO_GRB + NEO_KHZ800);
Servo servo;
Adafruit_PN532 nfc(-1, -1);

Button btnA = {BTN_PIN_A};
Button btnB = {BTN_PIN_B};

void setup() {
  Serial.begin(115200);
  //setup de l'ecran digital :
  display.setBrightness(0x0f);
  display.clear();
  //setup du capteur de temperature :
  dht.begin();
  //setup de la matrice :
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(BRIGHTNESS);
  matrix.fillScreen(0);
  matrix.show();
  //setup du servo :
  servo.attach(SERVO_PIN);
  servo.write(90);
  //setup des boutons :
  pinMode(BTN_PIN_A, INPUT_PULLUP);
  pinMode(BTN_PIN_B, INPUT_PULLUP);
  //setup du detecteur de mouvement :
  pinMode(PIR_PIN, INPUT);
  //setup du lecteur nfc :
  Wire.setPins(SDA_PIN, SCL_PIN);
  initNFC();
  //setup de firebase :
  setupFirestore();
  //setup des DEL :
  initDels();
  //etat de depart :
  initEtat();
}

void loop() {
  updateFlash();
  updateEtat();
}
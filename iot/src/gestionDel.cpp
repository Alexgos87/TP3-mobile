#include "gestionDel.h"

void initDels() {
  pinMode(DEL1_PIN, OUTPUT);
  pinMode(DEL2_PIN, OUTPUT);
  pinMode(DEL3_PIN, OUTPUT);
  setDels(false, false, false);
}

void setDels(bool del1, bool del2, bool del3) {
  digitalWrite(DEL1_PIN, del1);
  digitalWrite(DEL2_PIN, del2);
  digitalWrite(DEL3_PIN, del3);
}
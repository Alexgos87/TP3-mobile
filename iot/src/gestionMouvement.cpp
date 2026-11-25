#include "gestionMouvement.h"

bool mouvementDetecte() {
  return digitalRead(PIR_PIN) == HIGH;
}
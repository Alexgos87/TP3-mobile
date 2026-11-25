#include "gestionNFC.h"

bool initNFC() {
  nfc.begin();
  uint32_t versionData = nfc.getFirmwareVersion();
  if (!versionData) {
    Serial.println("PN532 introuvable !");
    return false;
  }
  Serial.print("PN532 detecte, firmware v");
  Serial.print((versionData >> 16) & 0xFF);
  Serial.print('.');
  Serial.println((versionData >> 8) & 0xFF);
  nfc.SAMConfig();
  return true;
}

bool lireTag(uint8_t* uid, uint8_t* uidLength) {
  return nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, uidLength, 100);
}

void afficherUID(uint8_t* uid, uint8_t uidLength) {
  for (uint8_t i = 0; i < uidLength; i++) {
    Serial.printf("0x%02X", uid[i]);
    if (i < uidLength - 1) {
      Serial.print(", ");
    }
  }
  Serial.println();
}
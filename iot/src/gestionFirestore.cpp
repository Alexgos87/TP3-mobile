#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include <time.h>
#include "gestionFirestore.h"
#include "secrets.h"

FirebaseAuth auth;
FirebaseConfig config;
FirebaseData fbdo;

void setupFirestore() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  configTime(0, 0, "pool.ntp.org");
  while (time(nullptr) < 1700000000) {
    delay(500);
    Serial.print("*");
  }
  Serial.println("Time OK");

  config.api_key = API_KEY;
  config.token_status_callback = tokenStatusCallback;
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase OK");
  } else {
    Serial.printf("Firebase error: %s\n", config.signer.signupError.message.c_str());
  }
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void logEvent(const char* type) {
  if (!Firebase.ready()) {
    Serial.println("Firebase not ready");
    return;
  }

  time_t currentTime = time(nullptr);
  char date[25];
  strftime(date, sizeof(date), "%Y-%m-%dT%H:%M:%SZ", gmtime(&currentTime));

  FirebaseJson content;
  content.set("fields/type/stringValue", type);
  content.set("fields/horodatage/timestampValue", date);
  content.set("fields/coffre/stringValue", "chambre-2355055");

  String documentPath = "evenements/" + String((long)currentTime) + "-" + String(millis());

  if (Firebase.Firestore.createDocument(&fbdo, PROJECT_ID, "", documentPath.c_str(), content.raw())) {
    Serial.println("Event saved: " + documentPath);
  } else {
    Serial.println("Firestore error: " + fbdo.errorReason());
  }
}
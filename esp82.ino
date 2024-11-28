#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// RFID setup
#define SS_PIN D8
#define RST_PIN D0
MFRC522 rfid(SS_PIN, RST_PIN);

// GPS setup
SoftwareSerial ss(D2, D1);  // RX, TX for GPS
TinyGPSPlus gps;

void setup() {
  // RFID initialization
  SPI.begin();
  rfid.PCD_Init();

  // GPS initialization
  ss.begin(9600);

  // Serial monitor
  Serial.begin(115200);
  Serial.println("Setup completed");
}

void loop() {
  // RFID reading
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    Serial.print("RFID UID: ");
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(rfid.uid.uidByte[i], HEX);
    }
    Serial.println();
    rfid.PICC_HaltA(); // Stop reading
  }

  // GPS reading
  while (ss.available() > 0) {
    gps.encode(ss.read());
    if (gps.location.isUpdated()) {
      Serial.print("Latitude: "); Serial.println(gps.location.lat(), 6);
      Serial.print("Longitude: "); Serial.println(gps.location.lng(), 6);
    }
  }

  delay(1000); // Delay between readings
}

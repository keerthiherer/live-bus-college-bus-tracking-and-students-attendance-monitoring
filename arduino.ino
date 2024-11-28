#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// GPS Pins
#define RXPin 8  // GPS TX to Arduino RX
#define TXPin 9  // GPS RX to Arduino TX (not used)
#define GPSBaud 9600

TinyGPSPlus gps;           // GPS library object
SoftwareSerial gpsSerial(RXPin, TXPin);  // GPS serial object

unsigned long previousMillis = 0; // Tracks the last print time
const unsigned long interval = 10000; // 20-second interval (20,000 ms)

void setup() {
  Serial.begin(115200);  // Initialize Serial Monitor
  gpsSerial.begin(GPSBaud);  // Initialize GPS Serial Communication

  Serial.println("NEO-6M GPS Module Test23 by gkb");
}

void loop() {
  // Continuously read data from GPS
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  // Get the current time
  unsigned long currentMillis = millis();

  // Print location every 20 seconds
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (gps.location.isValid()) {
      Serial.print("Latitude: ");
      Serial.println(gps.location.lat(), 6);
      Serial.print("Longitude: ");
      Serial.println(gps.location.lng(), 6);
    } else {
      Serial.println("GPS location not valid. Waiting for a fix...");
    }
  }
}

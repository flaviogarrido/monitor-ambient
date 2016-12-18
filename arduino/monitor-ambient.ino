#include <Adafruit_Sensor.h>
#include "DHT.h"

#define DHTPIN 2     // what digital pin we're connected to

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the analog resistor divider

void setup() {

  Serial.begin(9600);
  dht.begin();
  delay(2000);

}

void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  
  photocellReading = analogRead(photocellPin); 
 
  Serial.print("{ ");

  Serial.print("\"humidity\": \"");
  Serial.print(h);
  Serial.print("\", ");

  Serial.print("\"temperature\": \"");
  Serial.print(t);
  Serial.print("\", ");

  Serial.print("\"heatindex\": \"");
  Serial.print(hic);
  Serial.print("\", ");

  Serial.print("\"photocell\": \"");
  Serial.print(photocellReading);
  Serial.print("\", ");
  
  // We'll have a few threshholds, qualitatively determined
  Serial.print("\"light\": \"");
  if (photocellReading < 10) {
    Serial.print("dark");
  } else if (photocellReading < 200) {
    Serial.print("dim");
  } else if (photocellReading < 500) {
    Serial.print("light");
  } else if (photocellReading < 800) {
    Serial.print("bright");
  } else {
    Serial.print("very bright");
  }
  Serial.print("\"");

  Serial.println(" }");

  delay(2000);

}

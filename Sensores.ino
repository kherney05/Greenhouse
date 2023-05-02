#include "Sensores.h"
#include "DHT.h"

// implementacion de la funcion readLight
void readLight() {
  lightValue = map(analogRead(lightPin), 4092, 0, 0, 100);
  Serial.print(F("Luz: "));
  Serial.println(lightValue);
}

// implementacion de la funcion readHumeFloor
void readHumeFloor() {
  humeFloor = map(analogRead(humeFloorPin), 4092, 0, 0, 100);
  Serial.print(F("Humidity floor: "));
  Serial.println(humeFloor);
  //controlamos la bomba

}

// implementacion de la funcion readTemp 
void readTemp() {
  Serial.print(millis());
  // Wait a few seconds between measurements.
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  hume = dht.readHumidity();
  // Read temperature as Celsius (the default)
  temp = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(hume) || isnan(temp)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("\nHumidity: "));
  Serial.print(hume);
  Serial.print(F("%  \nTemperature: "));
  Serial.print(temp);
  Serial.print(F("°C "));
}

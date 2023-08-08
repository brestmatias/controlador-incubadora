#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2  
#define DHTTYPE    DHT22  
#define RELE1 3
DHT_Unified dht(DHTPIN, DHTTYPE);


void handleLamp(float temp);

void setup() {
  //int result = myFunction(2, 3);
  Serial.begin(9600);
  dht.begin();
  pinMode(RELE1, OUTPUT);
}

void loop() {

  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    handleLamp(event.temperature);
    /*Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.print(F("°C"));*/
    Serial.print(event.temperature);
    Serial.print(",");

    dht.humidity().getEvent(&event);
    /*Serial.print(" ");
    Serial.print(event.relative_humidity);
    Serial.println("%");*/
    Serial.println(event.relative_humidity);
    
  }
  delay(5000);
}

void handleLamp(float temp) {
  // LOW = prendido
  if (temp<=37) {
    digitalWrite(RELE1, LOW);
  } 
    // HIGH = apagado

  if(temp>38) {
    digitalWrite(RELE1, HIGH);
  }
}


// put function definitions here:
/*int myFunction(int x, int y) {
  return x + y;
}*/
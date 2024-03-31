#ifndef SENSOR_HANDLER_DHT
#define SENSOR_HANDLER_DHT
#include <ArduinoJson.h>
#include <DHT.h>
#include <DHT_U.h>

#define D6 12 // Pin D1 para el DHT11
DHT dht(D6, DHT11);

void initSensorHandler() {
  dht.begin();
}

void readDHT(DHT &sensor, const char *sensorName)  {

  float temperature = sensor.readTemperature();
    float humidity = sensor.readHumidity();

  Serial.print("\n ************Sensor ");
  Serial.print(sensorName);
  Serial.println("************ \n");

  if (!isnan(temperature)) {
    float temperatureFahrenheit = (temperature * 9.0 / 5.0) + 32.0;
    Serial.print("Temperature (C): ");
    Serial.println(temperature);
    Serial.print("Temperature (F): ");
    Serial.println(temperatureFahrenheit);
    Serial.print("Humidity: ");
    Serial.println(humidity);

    // Crear el objeto JSON
    StaticJsonDocument<256> jsonDocument;
    jsonDocument["sensor_id"] = "d80e520e-1d7b-4533-8433-999f22e38fc2";
    jsonDocument["temperatura (C):"] = temperature;
    jsonDocument["temperatura (F):"] = temperatureFahrenheit;
   jsonDocument["humedad"] = humidity;

    char msgBuffer[256];
    serializeJson(jsonDocument, msgBuffer);
    Serial.println("Mensaje JSON dht11:");
    Serial.println(msgBuffer);

    String topic = ("Externo/Upc/" + String(sensorName) + "/TH");
    Serial.println("topic:");
    Serial.println(topic);
    if (PublishMqtt(msgBuffer, topic, 2 )) {
      Serial.println("Mensaje publicado con éxito");
    }else {
    Serial.println("**************************");
    Serial.println("Fallo al publicar los datos del sensor DHT11");
    Serial.println("**************************");
  }
  } else {
    Serial.println("**************************");
    Serial.println("Fallo al leer los datos del sensor DHT11");
    Serial.println("**************************");
  }
}
#endif // SENSOR_HANDLER_DHT

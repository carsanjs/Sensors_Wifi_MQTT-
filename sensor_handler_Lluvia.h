#ifndef SENSOR_HANDLER_LLUVIA
#define SENSOR_HANDLER_LLUVIA
#include <Adafruit_ADS1X15.h>
#include <ArduinoJson.h>
#include <Wire.h>
Adafruit_ADS1115 ads;

void initializeFC() {
  Wire.begin();
  ads.begin();
}

void readPublicFC37(const char* SensorName) {
  int16_t adc1 = ads.readADC_SingleEnded(1);
  Serial.print(adc1);
  Serial.print("\n ************Sensor ");
  Serial.print(SensorName);
  Serial.println("************ \n");
  Serial.println(adc1);
  float lluvia = map(adc1, 0, 2000, 0, 1023);
  Serial.println(lluvia);
String estado;
if (lluvia <= 10) {
    estado = "Soleado";
  } else if (lluvia <= 40) {
    estado = "Lloviznando";
  } else if (lluvia <= 70) {
    estado = "Lloviendo";
  } else {
    estado = "Lloviendo duro";
  }
 Serial.print("mensaje de lluvia ");
Serial.println(estado);
//  const char* sensor_id = "d28544a9-e9b7-4cbb-b0e1-c910354f1370";

  // Crear el objeto JSON
  StaticJsonDocument<256> jsonDocument;
  jsonDocument["sensor_id"] = "d28544a9-e9b7-4cbb-b0e1-c910354f1370";
  jsonDocument["lluvia"] = lluvia;
  jsonDocument["mensaje"] = estado;
  
  char msgBuffer[256];
   serializeJson(jsonDocument, msgBuffer);
    Serial.println("Mensaje JSON fc-17:");
Serial.println(msgBuffer);

  // Publicar los datos en un solo tema MQTT
 String topic = ("Externo/Upc/" + String(SensorName) + "/Lluvia");
  Serial.println("topic:");
    Serial.println(topic);
  if (!PublishMqtt(msgBuffer, topic, 2)) {
    Serial.println("**************************");
    Serial.println("Fallo al publicar los datos del sensor FC-37 en MQTT");
    Serial.println("**************************");
  }
}
#endif // SENSOR_HANDLER_LLUVIA

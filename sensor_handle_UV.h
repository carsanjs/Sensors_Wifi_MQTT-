#ifndef SENSOR_HANDLE_GYML8511
#define SENSOR_HANDLE_GYML8511
#include <ArduinoJson.h>
int ADCO = A0;

void initializeUV(){pinMode(ADCO, INPUT);}
int averageAnalogRead(int pinToRead){
  byte numberOfReadings = 8;
  unsigned int runningValue = 0;

  for (int x = 0; x < numberOfReadings; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;

  return (runningValue);
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void readyPublicGYML8511(const char* SensorName){
  int uvLevel = averageAnalogRead(ADCO);

  float outputVoltage = 3.3 * uvLevel / 1024;
  float uvIntensity = mapfloat(outputVoltage, 0.99, 2.9, 0.0, 15.0);

 Serial.print("\n ************Sensor ");
  Serial.print(SensorName);
  Serial.println("************ \n");
  Serial.print(uvIntensity);
  Serial.print(" mW/cm^2");

  float bajo = 3.0;
  float moderado = 6.0;
  float alto = 8.0;
  float muy_alto = 11.0;
  float extremo = 14.0;

  // Determina en qué rango se encuentra la intensidad UV y muestra la etiqueta correspondiente
  String estado;
  if (uvIntensity < bajo)
  {
    estado = "Bajo";
  }
  else if (uvIntensity < moderado)
  {
    estado = "Moderado";
  }
  else if (uvIntensity < alto)
  {
   estado = "Alto";
  }
  else if (uvIntensity < muy_alto)
  {
    estado = "Muy Alto";
  }
  else
  {
   estado = "Extremo";
  }
  Serial.println(estado);

//  // Crear el objeto JSON
 StaticJsonDocument<256> jsonDocument;
  jsonDocument["sensor_id"] = "273c5cf4-fcc7-4fd5-932c-9c09479fa35b";
  jsonDocument["UV"] = uvIntensity;
  jsonDocument["mensaje"] = estado;
  char msgBuffer[256];
  serializeJson(jsonDocument, msgBuffer);
Serial.println("Mensaje JSON UV:");
Serial.println(msgBuffer);

  String topic = ("Externo/Upc/" + String(SensorName) + "/UV");
   Serial.println("topic:");
    Serial.println(topic);
  if (!PublishMqtt(msgBuffer, topic, 2)) {
    Serial.println("**************************");
    Serial.println("Fallo al publicar los datos del SENSOR UV en MQTT");
    Serial.println("**************************");
  }
 
    }
#endif

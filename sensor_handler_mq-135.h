#ifndef SENSOR_HANDLER_MQ135
#define SENSOR_HANDLER_MQ135
#include <Adafruit_ADS1X15.h>
#include <ArduinoJson.h>
#include <Wire.h>
Adafruit_ADS1115 mq135;


void initializemq() {
  Wire.begin();
  mq135.begin();
}

float readyPublishMQ135(const char *sensorName) {
  // Leemos el valor del canal 1 del módulo ADS1115 (conexión MQ-135)
  float adc1 = mq135.readADC_SingleEnded(0);
  Serial.print("\n ************Sensor ");
  Serial.println(sensorName);
  Serial.print("conversion");
  float data1 = adc1 * (5.0/1023.0);
  Serial.println(data1);
  Serial.println("************ \n");
  Serial.println(adc1);
  
  
  // Mapear los valores analógicos a una escala específica (ajusta los valores mínimo y máximo según sea necesario)
 float CO2_ppm;
  if (adc1 < 0) {
    CO2_ppm = 0; // Valor mínimo de CO2_ppm
  } else {
    CO2_ppm = map(adc1, 0, 5000, 0,10000 );
  }
  Serial.println(CO2_ppm);
  String message;

  if (CO2_ppm < 799) {
    message = "Nivel bajo de CO2";
  } else if (CO2_ppm >= 800 && CO2_ppm < 1499) {
    message = "Nivel moderado de CO2";
  } else if (CO2_ppm >= 1500 && CO2_ppm < 2499) {
    message = "Nivel alto de CO2";
  } else if (CO2_ppm >= 2500) {
    message = "Nivel muy alto de CO2";
  }
  Serial.println("mensaje mq-135 " + message);
//
//  String fecha = obtenerFecha();

//// Crear objeto JSON para el sensor MQ-135
    StaticJsonDocument<200> jsonDocument;
    jsonDocument["sensor_id"] = "16c395be-6027-4c99-bbe4-4b1981686e15";
    jsonDocument["CO2"] = CO2_ppm;
    jsonDocument["mensaje"] = message;

  char msgBuffer[256];
  serializeJson(jsonDocument, msgBuffer);
 Serial.println("Mensaje JSON dht11:");
Serial.println(msgBuffer);
  String topic = ("Externo/Upc/" + String(sensorName) + "/C02").c_str();
  if (!PublishMqtt(msgBuffer, topic,2)) {
    Serial.println("**************************");
    Serial.println("Fallo al publicar los datos del sensor MQ-135 en MQTT");
    Serial.println("**************************");
  }else{
     Serial.println("Mensaje publicado con éxito");
    }
}

#endif

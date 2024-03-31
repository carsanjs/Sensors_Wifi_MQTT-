#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClient.h>

#include "config.h"
#include "MQTT.hpp"
#include "ESP8266_Utils.hpp"
#include "ESP8266_Utils_MQTT_Async.hpp"
#include "sensor_handler_Lluvia.h" // archivo de la funcion del sensor de dioxido de carbono
#include "sensor_handler_dht.h"  //archivo de las funciones con el sensores dht11
//#include "sensor_handler_mq-135.h"
#include "sensor_handle_UV.h" //archivo de las funciones con el sensor c02 mq-135

#define D0 16  // Pin D0 para el LED VERDE

void setup() {
  pinMode(D0, OUTPUT);
  //  initializemq();
  initializeUV();
  initializeFC();
  initSensorHandler();
  Serial.begin(9600);
  ConnectWiFi_STA(true);
  InitMqtt();
}

void loop() {
  blinkLED(100);
  HandleMqtt();
  // readyPublishMQ135("MQ-135");
  readDHT(dht,"DHT11");
  readPublicFC37("FC-37");
  readyPublicGYML8511("GYML8511");
  delay(500);
}

void blinkLED(int duration) {
  digitalWrite(D0, HIGH);
  delay(duration / 2);
  digitalWrite(D0, LOW);
  delay(duration / 2);
}

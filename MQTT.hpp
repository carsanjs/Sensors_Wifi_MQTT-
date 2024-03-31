#ifndef MQTT_H
#define MQTT_H

WiFiClient espClient;
PubSubClient client(espClient);

const char *MQTT_BROKER_ADRESS = "broker.emqx.io";
const int MQTT_PORT = 1883;
const char *MQTT_CLIENT_NAME = "ESP8266Externo";
const char *MQTT_USERNAME = "pube";
const char *MQTT_PASSWORD = "toor";

//Hacemos uso del dato que se envia y el topic donde se publica
boolean PublishMqtt(const String& message, const String& topic, uint8_t qos) {
  if (client.connected()) {
  client.publish(topic.c_str(), message.c_str(),qos);
  Serial.println("Message published successfully");
  return true;
  } else {
    Serial.println("MQTT client not connected. Unable to publish message.");
    return false;
  }
}
#endif

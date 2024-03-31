void InitMqtt() 
{
  client.setServer(MQTT_BROKER_ADRESS, MQTT_PORT);
}

void ConnectMqtt() {
  while (!client.connected()) {
    Serial.println("Starting MQTT connection...");
    if (client.connect(MQTT_CLIENT_NAME, MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.print("connected successfull");
    } else {
      Serial.print("Failed MQTT connection, rc=");
      Serial.println(client.state());
      Serial.println(" try again in 2 seconds..");
      delay(2000);
    }
  }
}

void HandleMqtt() {
  if (!client.connected()) {
    Serial.println("MQTT client disconnected. Reconnecting...");
    ConnectMqtt();
  }
 client.loop();
}

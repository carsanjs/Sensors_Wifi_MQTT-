void ConnectWiFi_STA(bool useStaticIP = false)
{Serial.println("");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  unsigned long startTime = millis(); // Tiempo de inicio
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Estado de conexión WiFi: ");
    Serial.println(WiFi.status());
    Serial.println("Conectando a la red wifiz....");
    // Si han pasado más de 30 segundos y la conexión aún no se ha establecido, salir del bucle
    if (millis() - startTime > 30000) {
      Serial.println("Tiempo de conexión excedido. No se pudo conectar a la red WiFi.");
      break;
    }
    delay(500);
  }
  
  // Verificar si la conexión WiFi se estableció correctamente
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("Conexión WiFi establecida con éxito.");
    Serial.println(ssid);
    Serial.print("Dirección IP asignada:\t ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Fallo al conectar a la red WiFi.");
  }
}

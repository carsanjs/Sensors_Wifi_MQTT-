
### Instrucciones para Configurar y Ejecutar el Código en Arduino 🛠️
Para ejecutar este código, sigue los pasos a continuación:

## Descarga e instala Arduino IDE 🖥️, preferiblemente la version Arduino IDE 1.8.19
#link: (https://www.arduino.cc/en/software).

### Abre el Código en Arduino IDE 📝
Una vez que hayas descargado e instalado todas las bibliotecas necesarias y configurado el ESP8266 en Arduino IDE, abre el programa y carga los archivos proporcionados en tu repositorio. Los archivos que necesitas abrir son:

### Instala las Bibliotecas Necesarias 📚
Antes de abrir el código en Arduino IDE, necesitas instalar algunas bibliotecas adicionales. Abre Arduino IDE, ve a Sketch -> Incluir Biblioteca -> Administrar Bibliotecas... y busca las siguientes bibliotecas:

#ESP8266WiFi

#PubSubClient

#Adafruit_ADS1X15

#ArduinoJson

Instala estas bibliotecas si aún no están presentes en tu Arduino IDE.

##Configura el ESP8266 en Arduino IDE 🔌
Para poder cargar el código en un ESP8266, necesitas agregar el siguiente enlace a la configuración adicional de "Gestor de URLs Adicionales de Tarjetas" en Arduino IDE:
#link:(https://arduino.esp8266.com/stable/package_esp8266com_index.json)

Para hacer esto, ve a Archivo -> Preferencias en Arduino IDE, y en el campo Gestor de URLs Adicionales de Tarjetas, añade el enlace proporcionado arriba.

## Conecta tu Placa ESP8266 y Selecciona el Puerto 🛰️
Conecta tu placa ESP8266 a tu computadora mediante un cable USB. Luego, selecciona el puerto correcto en Arduino IDE haciendo clic en Herramientas -> Puerto y seleccionando el puerto al que está conectada tu placa.


## Compila y Carga el Código en tu Placa ESP8266 🚀
Una vez que hayas seleccionado el puerto correcto, simplemente haz clic en el botón "Verificar" (ícono de tilde) para compilar el código. Si la compilación se realiza con éxito, haz clic en el botón "Cargar" (ícono de flecha hacia la derecha) para cargar el código en tu placa ESP8266.

## Observa la Ejecución del Código 🧐
Una vez cargado el código en tu placa ESP8266, observa la ejecución del mismo. Asegúrate de tener correctamente conectados todos los sensores y dispositivos según lo especificado en el código.

¡Eso es todo! Ahora deberías poder ejecutar el código proporcionado en tu placa Arduino sin problemas. Si encuentras algún problema, revisa la consola de Arduino IDE para obtener mensajes de error y realiza las correcciones necesarias en el código.
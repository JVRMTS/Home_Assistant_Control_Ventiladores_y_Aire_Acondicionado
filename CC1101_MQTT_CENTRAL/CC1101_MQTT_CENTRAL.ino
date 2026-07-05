/*
 * @JMTS - www.jmts.es
 * Probado con ESP32 DEV MODULE
 * 19/01/2025
 */

#include "configuracion.h"
#include "conexionWiFi.h"
#include "ota.h"
#include "CC1101.h"
#include "MQTT.h"
#include "utilidades_MQTT.h"

void setup(){
  // Iniciamos el puerto serial y la función SPI
  Serial.begin(115200);
  SPI.begin();
 // pinMode(2, OUTPUT);
  
  // configuración mando del ventilador 433 MHz
  configuracionCC1101();

  // Conexion a la wifi y MQTT
	WiFi.onEvent(WiFiEvent);
	InitMqtt();

	conectarWiFi();

  // Configuramos la actualización via ota
  actualizacionOTA();
}

void loop(){
  //Si se ha perdido la conexión wifi llamamos a la función para conectar de nuevo
  if (WiFi.isConnected() == false){
    conectarWiFi();
  }
  PublishMqtt();
  // Llamamos a la actualización via OTA
  ArduinoOTA.handle();
}
/*
 * @JMTS - www.jmts.es
 * ESP32 DEVKIT
 * Reloj con fecha y hora más sensor de temperatura y humedad en pantalla LCD I2C 2004
 * Sensor de Temperatura-Humedad DHT22.
 * Hora a traves de servidor NTP basado en el ejemplo SimpleTime de la libreria del ESP32
 * Conexión a base de datos Mysql mediante php con el método POST para realizar un registro
 * La retroiluminación del LCD se gradua mediante LDR
 * Actualización del frimware via OTA con contraseña basado en el ejemplo ArduinoOTA
 * 16/10/2021
 */
 
#include "configuracion.h"
#include "conexionWiFi.h"
#include "sensorDHT.h"
#include "reloj.h"
#include "LCD.h"
#include "retroiluminacion.h"
#include "ota.h"
#include "MQTT.hpp"
#include "utilidades_MQTT.h"

void setup(){
  pinMode(PINLCD, OUTPUT);
  pinMode(PINLDR, INPUT);
  
  Serial.begin(115200);       // Se inicia el puerto serie y la velocidad
  lcd.init();                 // Se inicia el lcd
  lcd.backlight();            // Se enciende la retroiluminación del lcd
  lcd.clear();                // Se borra la pantalla del lcd

  dht.begin();                // Se inicia la lectura del dht

  //Conexion a la wifi y MQTT
	WiFi.onEvent(WiFiEvent);
	InitMqtt();

	conectarWiFi();

  // Configuranción del reloj
  configReloj();

  // Configuramos la actualización via ota
  actualizacionOTA();
}

void loop(){
  temperatura();
  fecha();

  //Si se ha perdido la conexión wifi llamamos a la función para conectar de nuevo y configuramos fecha y hora
  if (WiFi.isConnected() == false){
    conectarWiFi();
  }

  // Mostramos los datos en pantalla en cada loop
  mostrarPantalla(); 

  // Declaramos la variable para contar los segundos
  unsigned long currentMillis = millis();

  // Llamamos, cada dos segundos, a las función para enviar los datos a Home Assistant por MQTT
  if ((unsigned long) (currentMillis - previosMillis) >= intervalo){
      PublishMqtt();  // enviamos los datos por MQTT
      previosMillis = millis();
  }
  
  iluminacion();         // Controlamos la retroiluminación de la pantalla en cada loop
  ArduinoOTA.handle();   // Llamamos a la actualización via OTA
}
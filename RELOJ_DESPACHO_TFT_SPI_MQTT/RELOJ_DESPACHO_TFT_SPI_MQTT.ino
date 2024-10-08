/*
 * @JMTS - www.jmts.es
 * Probado con ESP32 DEV MODULE
 * Reloj con fecha y hora más sensor de temperatura y humedad en pantalla TFT con la libreria TFT_eSPI
 * Sensor de Temperatura-Humedad DHT22 o DHT11 solo has de configurarlo en su script
 * Hora a traves de servidor NTP basado en el ejemplo SimpleTime de la libreria del ESP32
 * Conexión a base de datos Mysql mediante php con el método POST para realizar un registro
 * Actualización del frimware via OTA con contraseña basado en el ejemplo ArduinoOTA
 * Envio y recepción de datos a traves de MQTT para mostrar otras temperaturas y controlar dos ventiladores y un aire acondicionado
 * 27/12/2023
 */

#include "configuracion.h"
#include "conexionWiFi.h"
#include "sensorDHT.h"
#include "ota.h"
#include "MQTT.h"
#include "utilidades_MQTT.h"
#include "reloj.h"
#include "tft.h"

#define LED_BUILTIN 2 // Led integrado en el PIN2

void setup(){
  // Iniciamos el puerto serial y la función SPI
  Serial.begin(115200);
  SPI.begin();

  // Ponemos el led integrado en OFF
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // Iniciamos el sensor DHT
  dht.begin();

  // Llamamos a la función para configurar la pantalla y calibrar el panel táctil
  configuracionPantalla(); // Función para configurar la pantalla
  touch_calibrate();       // Función para configurar el panel táctil
  
  // Conexion a la wifi y MQTT
	WiFi.onEvent(WiFiEvent);
  //suscripcion();
	InitMqtt();

	conectarWiFi();

  // Configuranción del reloj
  configReloj();

  // Configuramos la actualización via ota
  actualizacionOTA();
  
  // comprobamos si esta activo el sistema de archivos LittleFS
  if (!FILESYSTEM.begin()) {
    Serial.println("Formating file system");
    FILESYSTEM.format();
    FILESYSTEM.begin();
    touch_calibrate();
  }
  if (FILESYSTEM.exists(CALIBRATION_FILE)) {
    uint16_t calData[5];
    uint8_t calDataOK = 0;
    File f = FILESYSTEM.open(CALIBRATION_FILE, "r");
    if (f) {
      if (f.readBytes((char *)calData, 14) == 14)
        calDataOK = 1;
        f.close();
    }
  }
}

void loop(){
  fecha();
  temperatura();
  //Si se ha perdido la conexión wifi llamamos a la función para conectar de nuevo
  if (WiFi.isConnected() == false){
    conectarWiFi();
    configReloj();
  }
  unsigned long currentMillis = millis();
  // Llamamos, cada minuto, a la función para insertar los datos en la base de datos
  if ((unsigned long) (currentMillis - previosMillis) >= intervalo){
      PublishMqtt();
      previosMillis = millis();
  }
  switch(ventilador){
    case 0:
      mostrarPantalla();
    break;
    case 1:
      mostrarPantallaV1();
    break;
    case 2:
      mostrarPantallaV2();
    break;
  }
  // Llamamos a la actualización via OTA
  ArduinoOTA.handle();
 }

// Calibración de la pantalla táctil
void touch_calibrate()
{
  uint16_t calData[5];
  uint8_t calDataOK = 0;

  // check file system exists
  if (!FILESYSTEM.begin()) {
    Serial.println("Formating file system");
    FILESYSTEM.format();
    FILESYSTEM.begin();
  }

  // check if calibration file exists and size is correct
  if (FILESYSTEM.exists(CALIBRATION_FILE)) {
    if (REPEAT_CAL)
    {
      // Delete if we want to re-calibrate
      FILESYSTEM.remove(CALIBRATION_FILE);
    }
    else
    {
      File f = FILESYSTEM.open(CALIBRATION_FILE, "r");
      if (f) {
        if (f.readBytes((char *)calData, 14) == 14)
          calDataOK = 1;
        f.close();
      }
    }
  }

  if (calDataOK && !REPEAT_CAL) {
    // calibration data valid
    tft.setTouch(calData);
  } else {
    // data not valid so recalibrate
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(20, 0);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.println("Touch corners as indicated");

    tft.setTextFont(1);
    tft.println();

    if (REPEAT_CAL) {
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.println("Set REPEAT_CAL to false to stop this running again!");
    }

    tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println("Calibration complete!");

    // store data
    File f = FILESYSTEM.open(CALIBRATION_FILE, "w");
    if (f) {
      f.write((const unsigned char *)calData, 14);
      f.close();
    }
  }
}


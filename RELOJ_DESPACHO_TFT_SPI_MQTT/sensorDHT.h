/*
 / Configuración y función para la toma de datos de un sensor DHT, esta probado con DHT11 y DHT22 en Esp32 Dev Module
 / creado por JMTS
 / EL 01/04/2024
 */

#include <DHT.h>

#define DHTTYPE DHT22
#define DHTPIN 22         // Se define el PIN al que conectamos el Sensor DHT: pin 22

DHT dht(DHTPIN, DHTTYPE); // Creamos el objeto DHT

// Declaramos las variables que queremos mostrar
String t;
String h;
String s;

// Creamos la función para extraer los datos del sensor
void temperatura(){
  double te = dht.readTemperature();                // Leemos la temperatura del sensor
  t = String(te, 2);                                // La convertimos a un String  
  double hu = dht.readHumidity();                   // Leemos la humedad del sensor
  h = String(hu, 1);                                // La convertimos a un String
  double hic = dht.computeHeatIndex(te, hu, false); // Calculamos la sensación térmica
  s = String(hic, 2);                               // La convertimos a un String
}
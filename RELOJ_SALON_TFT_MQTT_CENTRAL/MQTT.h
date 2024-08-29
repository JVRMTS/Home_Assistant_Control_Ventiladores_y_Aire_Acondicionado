/*
 * Código adaptado de Luis LLamas https://luisllamas.es
 * 27/08/2024
*/

#pragma once
extern "C" {
	#include "freertos/FreeRTOS.h"
	#include "freertos/timers.h"
}

#include <AsyncMqttClient.h>
#include <ArduinoJson.h>

AsyncMqttClient mqttClient;

String GetPayloadContent(char* dato, size_t len)
{
	String content = "";
	for(size_t i = 0; i < len; i++)
	{
		content.concat(dato[i]);
	}
	return content;
}

void SuscribeMqtt(){
  
  //Serial.print("Subscribing at QoS 2, packetId: ");
	//Serial.println(packetIdSub);
}

// Publicamos por MQTT en formato JSON
void PublishMqtt()
{
	String payload = "";

	StaticJsonDocument<300> jsonDoc;
	jsonDoc["temperatura"] = t;
  jsonDoc["humedad"] = h;
  jsonDoc["sen_termica"] = s;

	serializeJson(jsonDoc, payload);

	mqttClient.publish(publicar, 0, true, (char*)payload.c_str());
}

// Definimos las variables para mostrar de otras estancias
double t1; double t2; double t3;
double h1; double h2; double h3;
double s1; double s2; double s3;

// Recepción de datos MQTT en formato JSON.
void OnMqttReceived(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
  String content = GetPayloadContent(payload, len);
  StaticJsonDocument<100> doc;
	  DeserializationError error = deserializeJson(doc, content);
    if(error) return;

  // Recibimos la opción para el control de los ventiladores. 
  long unsigned int dato = doc["opcion"];
  controlVentilador(dato, 32);
  
  // Recibimos el resto de tópicos y actuamos en consecuencia.
  if (strcmp(topic, suscribir1) == 0) {
    t1 = doc["temperatura"];
    h1 = doc["humedad"];
    s1 = doc["sen_termica"];
  } else if (strcmp(topic, suscribir2) == 0) {
    t2 = doc["temperatura"];
    h2 = doc["humedad"];
    s2 = doc["sen_termica"];
  } else if (strcmp(topic, suscribir3) == 0) {
    t3 = doc["temperatura"];
    h3 = doc["humedad"];
    s3 = doc["sen_termica"];
  }
}
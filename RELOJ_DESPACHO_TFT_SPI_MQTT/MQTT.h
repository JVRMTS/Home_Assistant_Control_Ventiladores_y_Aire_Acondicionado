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

// Suscriciones a los distintos topicos
void SuscribeMqtt(){
  mqttClient.subscribe(suscribir1,  0);
  mqttClient.subscribe(suscribir2,  0);
  mqttClient.subscribe(suscribir3,  0);
}

// Publicar los datos de temperatura, humedad y sensación térmica por MQTT
void PublishMqtt()
{
	String payload = "";
	StaticJsonDocument<100> jsonDoc;
	jsonDoc["temperatura"] = t;
  jsonDoc["humedad"] = h;
  jsonDoc["sen_termica"] = s;
	serializeJson(jsonDoc, payload);
	mqttClient.publish(publicar1, 2, true, (char*)payload.c_str());
}

// Control de ventiladores por MQTT
void ventiladorMQTT(const char* topico, unsigned long codigo){
  String payload = "";
	StaticJsonDocument<100> jsonDoc;
  jsonDoc["opcion"] = codigo;
  serializeJson(jsonDoc, payload);
  mqttClient.publish(topico, 2, true, (char*)payload.c_str());
}

// Definimos las variables para mostrar temperaturas de distintas ubicaciones
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
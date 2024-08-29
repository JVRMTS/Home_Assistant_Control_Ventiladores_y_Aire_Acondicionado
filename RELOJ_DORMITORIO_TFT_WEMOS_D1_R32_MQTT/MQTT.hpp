#pragma once

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

void SuscribeMqtt()
{
	uint16_t packetIdSub = mqttClient.subscribe(suscribir, 0);
	//Serial.print("Subscribing at QoS 2, packetId: ");
	//Serial.println(packetIdSub);
}

void PublishMqtt()
{
	String payload = "";

	StaticJsonDocument<300> jsonDoc;
	jsonDoc["temperatura"] = t;
  jsonDoc["humedad"] = h;
  jsonDoc["sen_termica"] = s;

	serializeJson(jsonDoc, payload);

	mqttClient.publish(publicar, 0, true, (char*)payload.c_str());
  //Serial.println(payload);
}

void OnMqttReceived(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
  /*
	Serial.print("Received on ");
	Serial.print(topic);
	Serial.println(": ");
*/
	String content = GetPayloadContent(payload, len);

	StaticJsonDocument<300> doc;
	DeserializationError error = deserializeJson(doc, content);
	if(error) return;
/*
  long unsigned int dato = doc["luz"];
  
  controlVentilador(dato, 32);
  Serial.println(dato);
*/
}
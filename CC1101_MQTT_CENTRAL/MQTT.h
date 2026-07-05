/*
 * Código adaptado de Luis LLamas https://luisllamas.es
 * 27/08/2024
*/
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
  mqttClient.subscribe(suscribir,  2);
  
  //Serial.print("Subscribing at QoS 2, packetId: ");
	//Serial.println(packetIdSub);
}

// Publicamos por MQTT en formato JSON
void PublishMqtt()
{
	//mqttClient.publish(publicar, 0, true, (char*)payload.c_str());
}

// Recepción de datos MQTT en formato JSON.
void OnMqttReceived(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
  String content = GetPayloadContent(payload, len);
  JsonDocument doc;
	  DeserializationError error = deserializeJson(doc, content);
    if(error) return;

  // Recibimos la opción para el control de los ventiladores. 
  long unsigned int dato = doc["opcion"];
  mySwitch.send(dato, 32);
}
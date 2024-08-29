/*
 * Código adaptado de Luis LLamas https://luisllamas.es
 * 08/08/2024
*/

#pragma once

TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer;

void ConnectToMqtt()
{
	//Serial.println("Connecting to MQTT...");
	mqttClient.connect();
}

void WiFiEvent(WiFiEvent_t event)
{
	Serial.printf("[WiFi-event] event: %d\n", event);
	switch(event)
	{
	case ARDUINO_EVENT_WIFI_STA_GOT_IP:
		/*Serial.println("WiFi connected");
		Serial.println("IP address: ");
		Serial.println(WiFi.localIP());*/
		ConnectToMqtt();
		break;
	case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
		//Serial.println("WiFi lost connection");
		xTimerStop(mqttReconnectTimer, 0); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
		xTimerStart(wifiReconnectTimer, 0);
		break;
	}
}

void OnMqttConnect(bool sessionPresent)
{
  SuscribeMqtt();
}

void OnMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
	//Serial.println("Disconnected from MQTT.");

	if(WiFi.isConnected())
	{
		xTimerStart(mqttReconnectTimer, 0);
	}
}

void OnMqttSubscribe(uint16_t packetId, uint8_t qos)
{
	/*Serial.println("Subscribe acknowledged.");
	Serial.print("  packetId: ");
	Serial.println(packetId);
	Serial.print("  qos: ");
	Serial.println(qos);*/
}

void OnMqttUnsubscribe(uint16_t packetId)
{/*
	Serial.println("Unsubscribe acknowledged.");
	Serial.print("  packetId: ");
	Serial.println(packetId);*/
}

void OnMqttPublish(uint16_t packetId)
{
	//Serial.println("Publish acknowledged.");
	//Serial.print("  packetId: ");
	//Serial.println(packetId);
}

void InitMqtt()
{
  mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(ConnectToMqtt));
	wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(5000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(conectarWiFi));

	mqttClient.onConnect(OnMqttConnect);
	mqttClient.onDisconnect(OnMqttDisconnect);

	mqttClient.onSubscribe(OnMqttSubscribe);
	mqttClient.onUnsubscribe(OnMqttUnsubscribe);

	mqttClient.onMessage(OnMqttReceived);
	mqttClient.onPublish(OnMqttPublish);
  
	mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  mqttClient.setCredentials(usuario, pass);
}
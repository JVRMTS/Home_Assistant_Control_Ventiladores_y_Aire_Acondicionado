/*
 * Conexión WiFi
 * 13/04/2024
 * @JMTS - www.jmts.es
 */

#include <WiFi.h>

// Conexión a la WiFi y configuración de fecha y hora
void conectarWiFi()
{
  //Serial.println("Arrancando");
  WiFi.mode(WIFI_STA);
  if (!WiFi.config(ip, gateway, subnet, dns)) {
    Serial.println("Fallo en la configuración.");
  }
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    //Serial.println("Conexion fallida! Reseteando...");
    delay(5000);
    ESP.restart();
  }
}


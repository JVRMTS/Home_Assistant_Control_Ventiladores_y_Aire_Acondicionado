/*
 * Fichero de configuración para el reloj con envío de datos por POST y actualización via OTA
 * Creado el 18/01/25
 * por @JMTS
 */

//Configuración IP fija
IPAddress ip(192,168,1,xxx);          // Se configura la dirección IP en base a la ubicación
IPAddress gateway(192,168,1,xxx);         // Puerta de enlace
IPAddress subnet(255,255,255,0);        // Mascara de red

// Nombre para actualizaciones OTA
const char* nombre = "CC1101";

//Configuración de la WiFi
const char* ssid = "xxx";             // Pon el nombre de tu WiFi
const char* password = "xxx"; // Pon la contraseña de tu WiFi

//Password para la actualización via OTA
const char* passwordOTA = "xxx";

//Configuración para MQTT
const char* usuario = "xxx";
const char* pass = "xxx";

const IPAddress MQTT_HOST(192,168,1,xxx);
const int MQTT_PORT = 1883;

const char* suscribir  = "casa/+/ventilador";
//const char* suscribir1 = "zigbee2mqtt/Interruptor Dormitorio/set";
//const char* suscribir2 = "zigbee2mqtt/Interruptor Ventilador Salón/set";
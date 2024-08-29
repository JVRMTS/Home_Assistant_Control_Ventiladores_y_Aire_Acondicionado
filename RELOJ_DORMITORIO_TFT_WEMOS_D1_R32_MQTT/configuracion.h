/*
 * Fichero de configuración para el reloj con envío de datos por POST y actualización via OTA
 * Creado el 31/07/24
 * por @JMTS
 */

// Iniciamos los contadores para insertar en la base de datos
unsigned long previosMillis;
unsigned long previosMillis1;
unsigned long intervalo  = 2000;

//Configuración IP fija
byte ub = 3;                            // Ubicación (1-despacho) (2-aseo) (3-dormitorio) (4-salón) (5-pruebas)
int finIP = 20+ub;                      // Se hace así para que no haya problemas con la base de datos y no tener que modificarla
IPAddress ip(192,168,1,finIP);          // Se configura la dirección IP en base a la ubicación
IPAddress gateway(192,168,1,1);         // Puerta de enlace
IPAddress subnet(255,255,255,0);        // Mascara de red
IPAddress dns(192, 168, 1, 9);   // DNS primario necesario para el envío de registros a la base de datos

// Configuración de la Ubicación
// tambien da nombre al puerto de actualizacion via OTA

char * ubicacion(){
  char * ubic;
  switch (ub){
    case 1:
      ubic = "RELOJ_DESPACHO";
    break;
    case 2:
      ubic = "RELOJ_ASEO";
    break;
    case 3:
      ubic = "RELOJ_DORMITORIO";
    break;
    case 4:
      ubic = "RELOJ_SALON";
    break;
    case 5:
      ubic = "RELOJ_PRUEBAS";
    break;
  }
  return ubic;
}

//Configuración de la WiFi
char * ssid = "****";             // Pon el nombre de tu WiFi
char * password = "****"; // Pon la contraseña de tu WiFi

//Password para la actualización via OTA
char * passwordOTA = "****";

//Configuración para MQTT pon los datos de tu instalación
const char* usuario = "****";
const char* pass = "****";

const IPAddress MQTT_HOST(192,168,1,9); // Pon la ip de tu instalación
const int MQTT_PORT = 1883;

const char* suscribir = "";
const char* publicar = "casa/dormitorio/variables";

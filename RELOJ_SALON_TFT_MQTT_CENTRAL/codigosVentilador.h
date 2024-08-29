/*
 * Funciones para manejar el ventilador de techo
 * @JMTS - www.jmts.es
 * 17/03/2024
 */


#include <ELECHOUSE_CC1101_SRC_DRV.h>   // se ha modificdo la libreria para que no de problemas de compilación con la libreria TFT_eSPI
#include <RCSwitch.h>

int pin = 14;                           // Definir pin de transmisión GDO0

byte ventilador = 0;
//byte a_a = 0;                           

RCSwitch mySwitch = RCSwitch();         // Declaramos el objeto mySwitch para transmitir por el CC1101

// Configuración del CC1101:
void configuracionCC1101(){
  ELECHOUSE_cc1101.Init();              // Debe configurarse para inicializar el cc1101
  ELECHOUSE_cc1101.setPA(10);           // configure TxPower. Son posibles los siguientes ajustes dependiendo de la banda de frecuencia. (-30 -20 -15 -10 -6 0 5 7 10 11 12) ¡El valor predeterminado es máximo!
  ELECHOUSE_cc1101.setMHZ(433.92);      // Aquí puede configurar su frecuencia básica. La lib calcula la frecuencia automáticamente (predeterminada = 433,92). El cc1101 puede: 300-348 MHZ, 387-464 MHZ y 779-928 MHZ. Lea más información de la hoja de datos.

  // Activamos la transmision en el pin correspondiente .
  mySwitch.enableTransmit(pin);

  // Configuramos el CC1101 en modo transmisión.
  ELECHOUSE_cc1101.SetTx();
    
  // Seleccionamos el protocolo de transmisión.
  mySwitch.setProtocol(6);

  // Seleccionamos tiempo del pulso en la transmisión.
  mySwitch.setPulseLength(390);
   
  // Numero de repeticiones de transmisión. En mi caso con 2 es suficiente.
  mySwitch.setRepeatTransmit(2);
}

// DECLARACIÓN DE VARIABLES PARA EL MANEJO DE LOS VENTILADORES
unsigned int b = 32;  // Bits de la variable
// Ventilador 1                 // Ventilador 2
unsigned long on_off_luz;       unsigned long on_off_luz2;
unsigned long on_off_vent;      unsigned long on_off_vent2;
unsigned long luz_amarilla;     unsigned long luz_amarilla2;
unsigned long luz_blanca;       unsigned long luz_blanca2;
unsigned long luz_azul;         unsigned long luz_azul2;
unsigned long brillo_bajar;     unsigned long brillo_bajar2;
unsigned long brillo_subir;     unsigned long brillo_subir2;
unsigned long invertir_vent;    unsigned long invertir_vent2;
unsigned long velo_1;           unsigned long velo_1_2;
unsigned long velo_2;           unsigned long velo_2_2;
unsigned long velo_3;           unsigned long velo_3_2;
unsigned long velo_4;           unsigned long velo_4_2;
unsigned long velo_5;           unsigned long velo_5_2;
unsigned long h_2;              unsigned long h_2_2;
unsigned long h_4;              unsigned long h_4_2;
unsigned long h_8;              unsigned long h_8_2;

void controlVentilador(unsigned long env, unsigned int b){

  // Ventilador 1                   // Ventilador 2
    on_off_luz      = 2780856078;   on_off_luz2     = 2780831953;
    on_off_vent     = 3972038414;   on_off_vent2    = 3972014289;
    luz_amarilla    = 1623228174;   luz_amarilla2   = 1623204049;
    luz_blanca      = 113278734;    luz_blanca2     = 113254609;
    luz_azul        = 230719246;    luz_azul2       = 230695121;
    brillo_bajar    = 4123033358;   brillo_bajar2   = 4123009233;
    brillo_subir    = 1606450958;   brillo_subir2   = 1606426833;
    invertir_vent   = 4257251086;   invertir_vent2  = 4257226961;
    velo_1          = 4223696654;   velo_1_2        = 4223672529;
    velo_2          = 4274028302;   velo_2_2        = 4274004177;
    velo_3          = 1522564878;   velo_3_2        = 1522540753;
    velo_4          = 4022370062;   velo_4_2        = 4022345937;
    velo_5          = 3217063694;   velo_5_2        = 3217039569;
    h_2             = 4156587790;   h_2_2           = 4156563665;
    h_4             = 2143321870;   h_4_2           = 2143297745;
    h_8             = 3753934606;   h_8_2           = 3753910481;
  
  mySwitch.send(env,b); // Función para enviar comandos al ventilador
}

/*
 * Funciones para manejar el ventilador de techo
 * @JMTS - www.jmts.es
 * 18/01/2025
 */

#include <SPI.h>
#include "ELECHOUSE_CC1101_SRC_DRV.h" // se ha modificdo la libreria para que no de problemas de compilación con la libreria TFT_eSPI
#include <RCSwitch.h>

int pin = 2;                           // Definir pin de transmisión GDO0

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


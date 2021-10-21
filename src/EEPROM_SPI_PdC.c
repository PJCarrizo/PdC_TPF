/*
 * EEPROM_SPI_PdC.c
 *
 *  Created on: 11 oct. 2021
 *      Author: Pablo Jesús Carrizo
 */


#include "sapi.h"        // <= Biblioteca sAPI
#include "sapi_board.h"        // <= Biblioteca sAPI
#include "sapi_gpio.h"
#include <string.h>
#include "board.h"
#include "EEPROM_SPI_PdC.h"
#include "EEPROM_25LC1024.h"
#include "EEPROM_Port.h"
/*==================[definiciones y macros]==================================*/
//#define PCA9633_ADD              0x3E
//#define PCA9633_REG_CONFIG_A     0x00
/*==================[definiciones de datos internos]=========================*/
/*
char* itoa(int value, char* result, int base) {
   // check that the base if valid
   if (base < 2 || base > 36) { *result = '\0'; return result; }

   char* ptr = result, *ptr1 = result, tmp_char;
   int tmp_value;

   do {
      tmp_value = value;
      value /= base;
      *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
   } while ( value );

   // Apply negative sign
   if (tmp_value < 0) *ptr++ = '-';
   *ptr-- = '\0';
   while(ptr1 < ptr) {
      tmp_char = *ptr;
      *ptr--= *ptr1;
      *ptr1++ = tmp_char;
   }
   return result;
}
*/
/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
	uint32_t input1 = 0;
	uint32_t exit;
	uint32_t dato = NULL;
	uint32_t cant_digitos = 0;
	uint8_t lec_uart = 0;
	uint32_t lec_eeprom = 0;
	uint32_t lec_uart_vect [3];
	uint8_t i = 0;
	uint32_t j = 0;
	uint32_t dato_vector [1024];

	// ---------- CONFIGURACIONES ------------------------------
	//uint8_t transmitDataBuffr[1];
	// Inicializar y configurar la plataforma
	//uint32_t state = 0;
	//uint32_t input1 = 0;
	boardConfig();

	// SPI configuration
	//spiConfig( SPI0 );
	ini_spi_uart ();
	gpioWrite( LEDR, ON );	// Indicador de puerta cerrada

	funcion_menu(input1);
	/*
	 * 	FIN MENU PRINCIPAL
	 */



	//write_data_EEPROM25LC1024 (state);
	//gpioWrite( LEDB, ON );
	delay( 2 );
		while (TRUE){


		}


}

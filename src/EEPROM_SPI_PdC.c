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

/*==================[definiciones de datos internos]=========================*/

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

	boardConfig();

	// SPI configuration
	// spiConfig( SPI0 );
	ini_spi_uart ();
	gpioWrite( LEDR, ON );	// Indicador de puerta abierta

	funcion_menu(input1);
	/*
	 * 	FIN MENU PRINCIPAL
	 */


	while (TRUE){

	}


}

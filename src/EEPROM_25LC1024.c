/*
 * 	EEPROM_25LC1024.c
 *	Funcion: Driver de EPROM 25LC1024
 *  Created on: 19 oct. 2021
 *      Author: Carrizo Pablo Jesús
 */
#include "sapi.h"     // <= sAPI header
#include "EEPROM_25LC1024.h"

/*=====[ Definitions of private data types ]===================================*/
#define MASTER_CODE   			1234
#define WREN					0x6		//	Set the write enable latch (enable write operations)
#define WRITE					0x2		//	Write data to memory array beginning at selected address
#define MSBADDRESS				0x00
#define MIDADDRESS				0x00
#define LSBADDRESS				0x00
#define READ					0x03

int32_t millisecs = 2;

void ini_spi_uart (void)
{
	spi_Config_EEPROM25LC1024 (SPI0);

	uartConfig( UART_USB, 115200 );
}


uint32_t write_data_EEPROM25LC1024 (uint8_t dato)
{
	bool res;
	int32_t millisecs = 3;
	/*
	 * 	MODO WREN
	*/
	//control_CS(CS_OFF);
	chipSelect(NULL);

	func_escritura (WRITE);			// WRITE = 0x02

	func_escritura (MSBADDRESS);	// address >> 16


	func_escritura (MIDADDRESS);	// address >> 8

	func_escritura (dato);		// address >> 16

	delay((tick_t)millisecs);

	chipSelect(TRUE);

	delay((tick_t)millisecs);

	return res;
}




uint8_t read_data_EEPROM25LC1024 (void)
{
	uint8_t lectura = 0;
	int32_t millisecs = 2;
	/*
	 * 	MODO WREN
	*/
	//control_CS(CS_OFF);
	chipSelect(NULL);

	func_escritura (READ);			// READ = 0x03

	func_escritura (MSBADDRESS);	// address >> 16

	func_escritura (MSBADDRESS);	// address >> 8

	func_escritura (MSBADDRESS);	// address

	lectura = func_lectura ();		// address >> 16

	delay((tick_t)millisecs);

	chipSelect(TRUE);

	delay((tick_t)millisecs);

	return lectura;
}

uint32_t funcion_menu(uint32_t opcion)
{
	uint32_t i = 0;
	uint8_t input1;
	uint32_t lec_uart_vect [3];
	uint32_t lec_eeprom_vec [3];

	uint32_t exit;
	uint32_t dato = NULL;
	uint32_t cant_digitos = 0;
	uint8_t lec_uart = 0;
	uint8_t lec_eeprom = 0;


	uartWriteString( UART_USB, "          ***********************************************************************************\r\n" ); // Envia primera linea
	uartWriteString( UART_USB, "             ******     MENU PRINCIPAL DE PANEL DE CAJA FUERTE     *****\r\n" ); // Envia primera linea
	uartWriteString( UART_USB, "          ***********************************************************************************\r\n" ); // Envia primera linea
	uartWriteString( UART_USB, "                                   APERTURA DE CAJA FUERTE\r\n" ); // Envia opción 1
	uartWriteString( UART_USB, "            INGRESE CODIGO DE SEGURIDAD Y CONFIRME CON TECLA 1\r\n" ); // Envia opción 2
	uartWriteString( UART_USB, "          ***********************************************************************************\r\n" ); // Envia primera linea

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	    	/////////////////// RUTINA PARA LA SELECCION DE LAS OPCIONES DE ARMADO MEDIANTE UART //////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	i = NULL;
	while (i < 3){

		    uartReadByte( UART_USB, &input1 );	// se toma dato desde la PC
		    lec_uart = input1;
		    if (!gpioRead( TEC1 ))
		    {
		    	do{
		    		delay((tick_t)millisecs);
		    	   }while (!gpioRead( TEC1 ));

		    	uartWriteByte( UART_USB, input1 );

		    	write_data_EEPROM25LC1024 (input1);

		    	lec_uart_vect [i] = lec_uart;
		    	delay((tick_t)millisecs);
		    	i++;
		    }

	}


	uartWriteString( UART_USB, "            CODIGO DE SEGURIDAD INGRESADO. CONFIRME CERRANDO PUERTA\r\n" ); // Envia opción 2
	while (gpioRead( TEC4 ));
	gpioWrite( LEDG, ON );					// Indicador de puerta cerrada
	gpioWrite( LED3, ON );					// Indicador de puerta cerrada

	uartWriteString( UART_USB, "            PARA APERTURA INGRESE CODIGO\r\n" ); // Envia opción 2

	i = NULL;
	while (i < 3){

		    uartReadByte( UART_USB, &input1 );	// se toma dato desde la PC
		    lec_uart = input1;

		    if (!gpioRead( TEC1 ))
		    {
		    	do{
		    		delay((tick_t)millisecs);
		    	}while (!gpioRead( TEC1 ));

		    	lec_eeprom = read_data_EEPROM25LC1024 ();

		    	if (lec_uart == lec_eeprom)
		    	{

		    		i++;
		    	}
		    	else
		    		uartWriteString( UART_USB, "            CODIGO INCORRECTO\r\n" );
		    }

	}

	uartWriteString( UART_USB, "            CODIGO CORRECTO\r\n" );
	gpioWrite( LEDR, ON );						// Indicador de puerta cerrada
	gpioWrite( LED3, OFF );						// Indicador de puerta cerrada
	lec_eeprom = read_data_EEPROM25LC1024 ();

}

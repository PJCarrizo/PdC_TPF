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



/*
typedef enum{
    OPTION_1 = '1',
    OPTION_2 = '2',
    OPTION_3 = '3',
} menu_state;
*/

void ini_spi_uart (void)
{
	spi_Config_EEPROM25LC1024 (SPI0);

	uartConfig( UART_USB, 115200 );
}


uint32_t write_data_EEPROM25LC1024 (uint8_t dato)
{
	bool res;
	int32_t millisecs = 2;
	/*
	 * 	MODO WREN
	*/
	//control_CS(CS_OFF);
	chipSelect(NULL);
	delay((tick_t)millisecs);

	func_escritura (WREN);

	delay((tick_t)millisecs);
	//control_CS(CS_ON);
	chipSelect(TRUE);

	delay((tick_t)millisecs);

	/*
	 * 	MODO WRITE
	 */

	//control_CS(CS_OFF);
	chipSelect(NULL);
	delay((tick_t)millisecs);

	func_escritura (WRITE);

	delay((tick_t)millisecs);
	//control_CS(CS_ON);

	func_escritura (MSBADDRESS);	// address >> 16

	delay((tick_t)millisecs);

	func_escritura (MIDADDRESS);	// address >> 8

	delay((tick_t)millisecs);

	func_escritura (LSBADDRESS);	// address

	delay((tick_t)millisecs);

	//for (uint32_t i = 0; i < 8; i++)
	//{
	func_escritura (dato);	// address >> 16
	//}
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
	delay((tick_t)millisecs);

	/*
	 * 	MODO READ
	 */
	func_escritura (READ);

	delay((tick_t)millisecs);

	func_escritura (MSBADDRESS);	// address >> 16

	delay((tick_t)millisecs);

	func_escritura (MSBADDRESS);	// address >> 8

	delay((tick_t)millisecs);

	func_escritura (MSBADDRESS);	// address

	delay((tick_t)millisecs);

	lectura = func_lectura ();	// address >> 16

	//uartWriteByte(UART_USB, lectura);

	delay((tick_t)millisecs);

	chipSelect(TRUE);

	delay((tick_t)millisecs);

	return lectura;
}

uint32_t funcion_menu(uint32_t opcion)
{
	uint8_t input1;
	uint32_t exit;
	uint32_t dato = NULL;
	uint32_t cant_digitos = 0;
	uint8_t lec_uart = 0;
	uint8_t lec_eeprom = 0;
	uint32_t lec_uart_vect [3];
	uint32_t i = 0;
	//menu_state state;

	uartWriteString( UART_USB, "          ***********************************************************************************\r\n" ); // Envia primera linea
	uartWriteString( UART_USB, "             ******     MENU PRINCIPAL DE PANEL DE CAJA FUERTE     *****\r\n" ); // Envia primera linea
	uartWriteString( UART_USB, "          ***********************************************************************************\r\n" ); // Envia primera linea
	uartWriteString( UART_USB, "                                   APERTURA DE CAJA FUERTE\r\n" ); // Envia opción 1
	uartWriteString( UART_USB, "            INGRESE CODIGO DE SEGURIDAD Y CONFIRME CON TECLA 1\r\n" ); // Envia opción 2
	uartWriteString( UART_USB, "          ***********************************************************************************\r\n" ); // Envia primera linea

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	    	/////////////////// RUTINA PARA LA SELECCION DE LAS OPCIONES DE ARMADO MEDIANTE UART //////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//lec_eeprom = read_data_EEPROM25LC1024 ();
	i = NULL;
	while (i < 3){//dato == NULL &

		    uartReadByte( UART_USB, &input1 );	// se toma dato desde la PC
		    lec_uart = input1;
		    if (!gpioRead( TEC1 ))
		    {
		    	i++;
		    	uartWriteByte( UART_USB, lec_uart );
		    	write_data_EEPROM25LC1024 (lec_uart);
		    	delay( 200 );

		    }

	}

	uartWriteString( UART_USB, "            INGRESE CODIGO DE SEGURIDAD Y CONFIRME CON TECLA 1\r\n" ); // Envia opción 2
	lec_eeprom = read_data_EEPROM25LC1024 ();
	//uartWriteByte( UART_USB, lec_eeprom );
/*
	while (lec_uart > 0)
	{
		lec_uart_vect [i] = lec_uart%10;
		lec_uart = lec_uart/10;
		i++;
	}



		    	if (lec_uart == lec_eeprom)
		    	{
		    		dato = TRUE;
		    	}
		    	else if (lec_uart == MASTER_CODE)
		    		dato = TRUE;

	while (gpioRead( TEC1 )){//dato == NULL &

	    	uartReadByte( UART_USB, &input1 );	// se toma dato desde la PC
	    	lec_uart = input1;

	    	if (lec_uart == lec_eeprom)
	    	{
	    		dato = TRUE;
	    	}
	    	else if (lec_uart == MASTER_CODE)
	    		dato = TRUE;
	}


	gpioWrite( LEDG, ON );	// Indicador de puerta abierta
	gpioWrite( LED3, ON ); 	// Simula mecanismo de apertura de caja fuerte
	uartWriteString( UART_USB, "                                   CAJA FUERTE ABIERTA\r\n" );
	uartWriteString( UART_USB, "¿NUEVO CODIGO DE SEGURIDAD? INGRESE NUEVO CODIGO Y CONFIRME CON TECLA 1\r\n" ); // Envia opción 2

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	    	/////////////////// RUTINA PARA LA SELECCION DE NUEVO CODIGO DE ARMADO MEDIANTE UART //////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	while (dato != MASTER_CODE && !gpioRead( TEC1 )){

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		    	/////////////////// RUTINA PARA LA SELECCION DE LAS OPCIONES DE ARMADO MEDIANTE UART //////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		    	uartReadByte( UART_USB, &input1 );	// se toma dato desde la PC
		    	dato = input1;

		}
		gpioWrite( LEDG, ON );	// Indicador de puerta abierta
		gpioWrite( LED3, ON ); 	// Simula mecanismo de apertura de caja fuerte




*/
}
/*
void func_menu_carga digito (void)
{
	 //
	 // 	MENU PRINCIPAL
	 //


	uartWriteString( UART_USB, "          ***********************************************************************************\r\n" ); // Envia primera linea
	uartWriteString( UART_USB, "                                  ******     MENU PRINCIPAL     *****\r\n" ); // Envia primera linea
	uartWriteString( UART_USB, "          ***********************************************************************************\r\n" ); // Envia primera linea
	uartWriteString( UART_USB, "                                   CARGADO DE DATOS EN MEMORIA\r\n" ); // Envia opción 1

	while (lec_uart == NULL)//dato == NULL &
	{
		uartReadByte( UART_USB, &input1 );	// se toma dato desde la PC
		lec_uart = input1;
	}

	uartWriteString( UART_USB, "          Escribiendo Memoria...\r\n" ); //

	//uartWriteByte( UART_USB, lec_uart);

	//for (i = 0; i < 8; i++)
	//{
	write_data_EEPROM25LC1024 (lec_uart);
	//}
	delay( 200 );
	//uartWriteString( UART_USB, "          Leyendo Memoria...\r\n" ); //
	//delay( 200 );

	uartWriteString( UART_USB, "          Dato cargado en Memoria:\r\n" ); //
	delay( 200 );

	//for (j = 0; j < 24; j++)
	//{
	lec_eeprom = read_data_EEPROM25LC1024 ();
	uartWriteByte(UART_USB, lec_uart);
	//}
	//lec_eeprom = read_data_EEPROM25LC1024 ();
	//uartWriteByte(UART_USB, lec_eeprom);
}
*/

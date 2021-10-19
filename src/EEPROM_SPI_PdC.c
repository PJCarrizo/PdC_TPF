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

/*==================[definiciones y macros]==================================*/
//#define PCA9633_ADD              0x3E
//#define PCA9633_REG_CONFIG_A     0x00
/*==================[definiciones de datos internos]=========================*/
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

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/
bool_t spi_Config_EEPROM25LC1024( spiMap_t spi )

{

   bool_t retVal = TRUE;

   if( spi == SPI0 ) {

      // Configure SPI pins for each board

      //#if BOARD==ciaa_nxp||edu_ciaa_nxp
         /* Set up clock and power for SSP1 module */
         // Configure SSP SSP1 pins
         Chip_SCU_PinMuxSet( 0xF, 4, (SCU_MODE_PULLUP | SCU_MODE_FUNC0)); // SSP1_SCK
         Chip_SCU_PinMuxSet( 0x1, 3, (SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC5)); // SSP1_MISO
         Chip_SCU_PinMuxSet( 0x1, 4, (SCU_MODE_PULLUP | SCU_MODE_FUNC5)); // SSP1_MOSI
         Chip_SCU_PinMuxSet( 0x6, 1, (SCU_MODE_PULLUP | SCU_MODE_FUNC0)); // Pin for SPI SS configured as GPIO output with pull-up
       	 Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 3, 0);					//Pin SS as output (GPIO0)

         // Initialize SSP Peripheral
         Chip_SSP_Init( LPC_SSP1 );
         Chip_SSP_Enable( LPC_SSP1 );
      //#endif

         // Initialize SSP Peripheral
         //Chip_SSP_Init( LPC_SSP0 );
         //Chip_SSP_Enable( LPC_SSP0 );

   } else {
      retVal = FALSE;
   }

   return retVal;
}


float write_data_EEPROM25LC1024 (uint32_t dato)
{
//float max6675_GetTemp(void)  {
	char buffer_1;
	char buffer_res;
	uint16_t raw_data;
	float temp;


	Chip_SSP_DATA_SETUP_T xferConfig;
	uint8_t data = 0x6;
	uint8_t buffer[] = {data};
	uint16_t ret;
	bool res;
	int32_t millisecs = 2;


	/**
	* Inicio de una nueva lectura, ponemos CS en LOW (ver hoja de datos)
	*/
	//control_CS(CS_ON);
	Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,3,0);
	//delay_1ms_func(2);
	gpioWrite( LED1, ON );
	delay((tick_t)millisecs);
	gpioWrite( LED2, ON );
	xferConfig.tx_data = buffer[0];
	xferConfig.tx_cnt  = 0;
	xferConfig.rx_data = NULL;
	xferConfig.rx_cnt  = 0;
	xferConfig.length  = 1;

	Chip_SSP_RWFrames_Blocking(LPC_SSP1,  &xferConfig);
	gpioWrite( LED3, ON );
	delay((tick_t)millisecs);
	//control_CS(CS_OFF);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,3,0);
	delay((tick_t)millisecs);
	/**
	* Leemos el dato crudo desde el dispositivo y terminamos la transaccion
	*/

	//*******dato = spi_write_data();

/////////////************************////////////////
	data = 0x2;//buffer [1] = 0x2;
	buffer [0] = data;
	gpioWrite( LEDB, OFF );
	delay((tick_t)millisecs);
	for(uint32_t i = 0; i < 4; i++)
	{

		xferConfig.tx_data = buffer[0];
		xferConfig.tx_cnt  = 0;
		xferConfig.rx_data = NULL;
		xferConfig.rx_cnt  = 0;
		xferConfig.length  = 1;


		/**
		 * Se utiliza una funcion de lpc open que permite leer un byte
		 * Mediante el parametro lengh se indica que seran 2 bytes a leer
		 */
		res = Chip_SSP_RWFrames_Blocking(LPC_SSP1,  &xferConfig);
		gpioWrite( LED1, OFF );
		//itoa((int)res,buffer_res,10);
		//uartWriteString( UART_USB, res);
		uartWriteByte(UART_USB, res);
		uartWriteByte(UART_USB, buffer[0]);
		gpioWrite( LED2, OFF );
		//buffer = buffer * 0x2;
		if (dato != 0)
		{
			data = dato;//buffer [1] = 0x2;
			buffer [0] = data;

		}
		else
		{
			data = 0x2*4;//buffer [1] = 0x2;
			buffer [0] = data;

		}
		delay((tick_t)millisecs);
		//data = 0x2*4;//buffer [1] = 0x2;
		//buffer [1] = data;
		//itoa((int)buffer,buffer_1,10);
		//uartWriteString( UART_USB, buffer);
		uartWriteByte(UART_USB, buffer);
		delay((tick_t)millisecs);
		gpioWrite( LED3, OFF );
		delay((tick_t)millisecs);
	}
		/**
		 * Se debe armar el dato de 16bits entendiendo que el primer byte recibido es
		 * el mas significativo
		 */
		//ret = buffer[0] << 8;
		//ret |= buffer[1];
////////////******************/////////////////

	//delay_1ms_func(2);
	delay((tick_t)millisecs);
	//control_CS(CS_OFF);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,3,0);
	gpioWrite( LED1, OFF );
	/**
	* Se hace un bit shift hacia la derecha segun la hoja de datos
	*/
	//dato = dato >> 3;

	/**
	* Aplicamos la conversion correspondiente segun la hoja de datos y retornamos
	*/
	//temp = convert_raw2temp(raw_data);

	return temp;
}




float read_data_EEPROM25LC1024 (void)
{
//float max6675_GetTemp(void)  {
	char buffer_1;
	char buffer_res;
	uint16_t raw_data;
	float temp;


	Chip_SSP_DATA_SETUP_T xferConfig;
	uint8_t data = 0x4;
	uint8_t buffer[] = {data};
	uint16_t ret;
	bool res;
	int32_t millisecs = 2;


	/**
	* Inicio de una nueva lectura, ponemos CS en LOW (ver hoja de datos)
	*/
	//control_CS(CS_ON);
	Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,3,0);
	//delay_1ms_func(2);
	gpioWrite( LED1, ON );
	delay((tick_t)millisecs);

	/**
	* Leemos el dato crudo desde el dispositivo y terminamos la transaccion
	*/

	//*******dato = spi_write_data();

/////////////************************////////////////
	data = 0x3;//buffer [1] = 0x2;
	buffer [1] = data;
	gpioWrite( LEDB, OFF );
	for(uint32_t i = 0; i < 10; i++)
	{

		xferConfig.tx_data = NULL;
		xferConfig.tx_cnt  = 0;
		xferConfig.rx_data = buffer;
		xferConfig.rx_cnt  = 0;
		xferConfig.length  = 1;


		/**
		 * Se utiliza una funcion de lpc open que permite leer un byte
		 * Mediante el parametro lengh se indica que seran 2 bytes a leer
		 */
		res = Chip_SSP_RWFrames_Blocking(LPC_SSP1,  &xferConfig);
		gpioWrite( LED1, OFF );
		//itoa((int)res,buffer_res,10);
		//uartWriteString( UART_USB, res);
		uartWriteByte(UART_USB, res);

		gpioWrite( LED2, OFF );
		//buffer = buffer * 0x2;
		data = 0x2*4;//buffer [1] = 0x2;
		buffer [1] = data;
		//itoa((int)buffer,buffer_1,10);
		//uartWriteString( UART_USB, buffer);
		uartWriteByte(UART_USB, buffer);
		gpioWrite( LED3, OFF );
	}
	 uartWriteString( UART_USB, "termine de leer");
		/**
		 * Se debe armar el dato de 16bits entendiendo que el primer byte recibido es
		 * el mas significativo
		 */
		//ret = buffer[0] << 8;
		//ret |= buffer[1];
////////////******************/////////////////

	//delay_1ms_func(2);
	delay((tick_t)millisecs);
	//control_CS(CS_OFF);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,3,0);
	gpioWrite( LED1, OFF );
	/**
	* Se hace un bit shift hacia la derecha segun la hoja de datos
	*/
	//dato = dato >> 3;

	/**
	* Aplicamos la conversion correspondiente segun la hoja de datos y retornamos
	*/
	//temp = convert_raw2temp(raw_data);

	return;
}




/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------
   //uint8_t transmitDataBuffr[1];
   // Inicializar y configurar la plataforma
	uint32_t state = 0;
	uint32_t input1 = 0;
   boardConfig();
   //gpioConfig( GPIO0, GPIO_OUTPUT );
   uartConfig( UART_USB, 115200 );

   //gpioConfig( GPIO0, GPIO_OUTPUT );
   // SPI configuration
   //spiConfig( SPI0 );
   spi_Config_EEPROM25LC1024 (SPI0);

   //delay( 40 );   //    delay( LCD_STARTUP_WAIT_MS );   // Wait for stable power (some LCD need that)Wait for stable power (some LCD need that)

   //i2cInit( I2C0, 300000 ); //i2cInit( I2C0, 100000 );
   //spiConfig( SPI0 );
   //initHW();
   uartWriteString( UART_USB, "Inicio:");

   gpioWrite( LEDB, ON );

   //spi_Init_EEPROM25LC1024 ();

   write_data_EEPROM25LC1024 (state = 0);
	   //temp_actual = max6675_GetTemp();
	   //itoa((int)variable,buffer_2,10);
	   //max6675_control.delay_1ms_func(2);
   gpioWrite( LED3, ON );

   delay( 2 );   //    delay( LCD_STARTUP_WAIT_MS );   // Wait for stable power (some LCD need that) Wait for stable power (some LCD need that)
	   //max6675_control.chip_select_ctrl(CS_DISABLE);
	   //Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,3,0);
   read_data_EEPROM25LC1024 ();
   gpioWrite( LEDB, ON );
   while (state == 0)
   {
	   uartReadByte( UART_USB, &input1 );	// se toma dato desde la PC
	   state = input1;

   }
   write_data_EEPROM25LC1024 (state);
   gpioWrite( LEDB, ON );
   delay( 2 );
	   while (TRUE){

	   }


}

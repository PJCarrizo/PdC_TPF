/*
 * EEPROM_SPI_PdC.c
 *
 *  Created on: 11 oct. 2021
 *      Author: Pablo Jesús Carrizo
 */


#include "sapi.h"        // <= Biblioteca sAPI
#include "sapi_board.h"        // <= Biblioteca sAPI
#include "sapi_gpio.h"
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

void initHW(void)  {

	/**
	 * Configuracion e Inicializacion de puerto SPI
	 */
	 Chip_SCU_PinMuxSet( 0xF, 4, (SCU_MODE_PULLUP | SCU_MODE_FUNC0)); // SSP1_SCK
	 Chip_SCU_PinMuxSet( 0x1, 3, (SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC5)); // SSP1_MISO
	 Chip_SCU_PinMuxSet( 0x6, 1, (SCU_MODE_PULLUP | SCU_MODE_FUNC0)); // Pin for SPI SS configured as GPIO output with pull-up
	 //Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 3, 0);					//Pin SS as output (GPIO0)
	 gpioConfig( GPIO0, GPIO_OUTPUT );
	 gpioWrite( GPIO0, 1 );
	 // Initialize SSP Peripheral
	 Chip_SSP_Init( LPC_SSP1 );
	 Chip_SSP_Enable( LPC_SSP1 );

	 // Inicializar UART_USB a 115200 baudios. Esto es de SAPI!
	 uartConfig( UART_USB, 115200 );
}
/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
	uint8_t* buffer_1 = 0;
	uint32_t bufferSize_1 = 0;
	float	variable = 0;
	char buffer_2 = 0;
   // ---------- CONFIGURACIONES ------------------------------
   //uint8_t transmitDataBuffr[1];
   // Inicializar y configurar la plataforma

   boardConfig();
   //gpioConfig( GPIO0, GPIO_OUTPUT );

   //gpioConfig( GPIO1, GPIO_OUTPUT );
   //delay( 40 );   //    delay( LCD_STARTUP_WAIT_MS );   // Wait for stable power (some LCD need that)Wait for stable power (some LCD need that)

   //i2cInit( I2C0, 300000 ); //i2cInit( I2C0, 100000 );
   //spiConfig( SPI0 );
   initHW();
   uartWriteString( UART_USB, "Temperatura actual: ");
   uartWriteString( UART_USB, "Ingrese bucle ");
   gpioWrite( LEDB, ON );
   //gpioWrite( LED1, OFF );
   //gpioWrite( LED2, OFF );
   //gpioWrite( LED3, OFF );
   //delay( 40 );   //    delay( LCD_STARTUP_WAIT_MS );   // Wait for stable power (some LCD need that) Wait for stable power (some LCD need that)
   //spiRead( spiMap_t spi, uint8_t* buffer, uint32_t bufferSize );
	/**
	 * Inicio de una nueva lectura, ponemos CS en LOW (ver hoja de datos)
	 */
	//max6675_control.chip_select_ctrl(CS_ENABLE);
	//max6675_control.delay_1ms_func(2);
   //buffer_1 = 0x03;
   //*buffer_1 = 0x03;
   //bufferSize_1 = 1;

	   //Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,3,0);
	   uartWriteString( UART_USB, "Ingrese bucle ");
	   gpioWrite( GPIO0, 0 );
	   uartWriteString( UART_USB, "Pase GPIO0 = 0 ");
	   delay( 2 );   //    delay( LCD_STARTUP_WAIT_MS );   // Wait for stable power (some LCD need that) Wait for stable power (some LCD need that)
	   /**
		 * Leemos el dato crudo desde el dispositivo y terminamos la transaccion
		 */
		//raw_data = max6675_control.spi_read_fnc();
	   /**
	   	 * Se utiliza una funcion de lpc open que permite leer un byte
	   	 * Mediante el parametro lengh se indica que seran 2 bytes a leer
	   	 */
	   variable = spiRead( SPI0, 0x03, 1 );

	   //temp_actual = max6675_GetTemp();
	   itoa((int)variable,buffer_2,10);
	   uartWriteString( UART_USB, "Temperatura actual: ");
	   uartWriteString( UART_USB, buffer_2);
	   uartWriteString( UART_USB, "ÂºC           \r");
	   //max6675_control.delay_1ms_func(2);
	   delay( 2 );   //    delay( LCD_STARTUP_WAIT_MS );   // Wait for stable power (some LCD need that) Wait for stable power (some LCD need that)
	   //max6675_control.chip_select_ctrl(CS_DISABLE);
	   //Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,3,0);
	   gpioWrite( GPIO0, 1 );

	   //transmitDataBuffr[1] = 0x07;
	   //i2cWrite( I2C0, PCA9633_ADD  , 0x07, 1, TRUE ); //i2cWrite( I2C0, pcf8574TI2cAddress, &directions, 1, TRUE );
	   //delay( 40 );   //    delay( LCD_STARTUP_WAIT_MS );   // Wait for stable power (some LCD need that) Wait for stable power (some LCD need that)
	   gpioWrite( LED3, ON );
	   delay( 1000 );
	   gpioWrite( LED3, OFF );

	   while (TRUE){

	   }


}

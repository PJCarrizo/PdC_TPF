/*
 * EEPROM_Port.c
 *
 *  Created on: 20 oct. 2021
 *      Author: Usuario
 */

#include "EEPROM_Port.h"
#include "ssp_18xx_43xx.h"
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

void chipSelect(uint8_t cs)
{
	if (cs == NULL)
	{
		gpioWrite( GPIO0, OFF );
		//gpioWrite( LED3, ON );
		//gpioWrite( LED2, OFF );
	}

	else
	{
		gpioWrite( GPIO0, ON );
		//gpioWrite( LED3, OFF );
		//gpioWrite( LED2, ON );
	}


}

void func_escritura (uint8_t wren)
{
	Chip_SSP_DATA_SETUP_T xferConfig;//buffer [0] = wren;
	uint16_t buffer[1];
	buffer [0] = wren;
	xferConfig.tx_data = buffer[0];
	xferConfig.tx_cnt  = 0;
	xferConfig.rx_data = NULL;
	xferConfig.rx_cnt  = 0;
	xferConfig.length  = 1;
	/**
	 * Se utiliza una funcion de lpc open que permite leer un byte
	 * Mediante el parametro lengh se indica que seran 2 bytes a leer
	*/
	Chip_SSP_SendFrame (LPC_SSP1, xferConfig.tx_data);
	//Chip_SSP_RWFrames_Blocking(LPC_SSP1,  &xferConfig);
	//SSP_Write1BFifo (LPC_SSP1,  &xferConfig);
	return;
}


uint16_t func_lectura (void)
{
	Chip_SSP_DATA_SETUP_T xferConfig;//buffer [0] = wren;
	uint8_t buffer[1];
	uint16_t ret;
	bool res;

	xferConfig.tx_data = NULL;
	xferConfig.tx_cnt  = 0;
	xferConfig.rx_data = buffer [0];
	xferConfig.rx_cnt  = 0;
	xferConfig.length  = 1;

	/**
	 * Se utiliza una funcion de lpc open que permite leer un byte
	 * Mediante el parametro lengh se indica que seran 2 bytes a leer
	*/
	res = Chip_SSP_RWFrames_Blocking(LPC_SSP1,  &xferConfig);

	//ret = read[0] << 8;
	//ret |= read[1];
	//uartWriteByte(UART_USB, read[1]);
	//uartWriteByte(UART_USB, *read);
	//uartWriteByte(UART_USB, buffer[0]);
	if(res == TRUE)
		gpioWrite( LED1, ON );
	return ret;
}
/*
uint32_t write_data_EEPROM25LC1024 (uint32_t dato)
{
//float max6675_GetTemp(void)  {
	char buffer_1;
	char buffer_res;
	uint16_t raw_data;
	float temp;


	Chip_SSP_DATA_SETUP_T xferConfig;
	uint32_t data = 0x6;
	uint32_t buffer[1];
	uint16_t ret;
	bool res;
	int32_t millisecs = 2;
	//uint32_t dato_vector [1024];
	//uint32_t i = 0;
/*
	while (dato > 0)
		{
			dato_vector [i] = dato%10;
			dato = dato/10;
			i++;
		}



	// Inicio de una nueva escritura, ponemos CS en LOW (ver hoja de datos)

	//control_CS(CS_ON);
	//Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,3,0);
	gpioWrite( GPIO0, OFF );
	if (GPIO0 == TRUE)
		//gpioWrite( LED2, ON );
		uartWriteString( UART_USB, " No habilito CS\r\n" );
		//delay_1ms_func(2);
	//gpioWrite( LED1, ON );
	delay((tick_t)millisecs);
	//gpioWrite( LED2, ON );
	buffer [0] = data;
	xferConfig.tx_data = buffer[0];
	xferConfig.tx_cnt  = 0;
	xferConfig.rx_data = NULL;
	xferConfig.rx_cnt  = 0;
	xferConfig.length  = 1;

	Chip_SSP_RWFrames_Blocking(LPC_SSP1,  &xferConfig);
	//gpioWrite( LED3, ON );
	delay((tick_t)millisecs);
	//control_CS(CS_OFF);
	gpioWrite( GPIO0, ON );
	//Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,3,0);
	delay((tick_t)millisecs);

	//dato = spi_write_data();


	data = 0x2;//buffer [1] = 0x2;
	buffer [0] = data;

	delay((tick_t)millisecs);

	//Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,3,0);
	gpioWrite( GPIO0, OFF );//delay_1ms_func(2);
	//gpioWrite( LED1, ON );
	delay((tick_t)millisecs);
	//gpioWrite( LED2, ON );

	xferConfig.tx_data = buffer[0];
	xferConfig.tx_cnt  = 0;
	xferConfig.rx_data = NULL;
	xferConfig.rx_cnt  = 0;
	xferConfig.length  = 1;

	Chip_SSP_RWFrames_Blocking(LPC_SSP1,  &xferConfig);
	//gpioWrite( LED3, ON );
	delay((tick_t)millisecs);
	//control_CS(CS_OFF);
	//Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,3,0);
	//delay((tick_t)millisecs);

	//for(uint32_t j = 0; j < i; j++)
	//{
	buffer [0] = dato;
	xferConfig.tx_data = buffer [0];
	xferConfig.tx_cnt  = 0;
	xferConfig.rx_data = NULL;
	xferConfig.rx_cnt  = 0;
	xferConfig.length  = 1;



		res = Chip_SSP_RWFrames_Blocking(LPC_SSP1,  &xferConfig);



	return res;
}

*/
/*

uint32_t read_data_EEPROM25LC1024 (void)
{
//float max6675_GetTemp(void)  {
	char buffer_1;
	char buffer_res;
	uint32_t raw_data;
	float temp;


	Chip_SSP_DATA_SETUP_T xferConfig;
	uint32_t data = 0x4;
	uint32_t buffer[1]; //= {data};
	uint32_t ret;
	bool res;
	int32_t millisecs = 2;



	//control_CS(CS_ON);
	gpioWrite( GPIO0, OFF);
	//Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,3,0);
	//delay_1ms_func(2);
	//gpioWrite( LED1, ON );
	delay((tick_t)millisecs);

	data = 0x3;//buffer [1] = 0x2;
	buffer [0] = data;

	xferConfig.tx_data = NULL;
	xferConfig.tx_cnt  = 0;
	xferConfig.rx_data = buffer;
	xferConfig.rx_cnt  = 0;
	xferConfig.length  = 1;



	res = Chip_SSP_RWFrames_Blocking(LPC_SSP1,  &xferConfig);


	//uartWriteByte(UART_USB, res);

	//buffer = buffer * 0x2;
	//data = 0x2*4;//buffer [1] = 0x2;
	//buffer [1] = data;

	//uartWriteByte(UART_USB, buffer);
	//gpioWrite( LED3, OFF );


		//ret = buffer[0] << 8;
		//ret |= buffer[1];


	//delay_1ms_func(2);
	delay((tick_t)millisecs);
	//control_CS(CS_OFF);
	gpioWrite( GPIO0, ON );
	//Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,3,0);
	//gpioWrite( LED1, OFF );

	//dato = dato >> 3;


	//temp = convert_raw2temp(raw_data);
	ret = buffer[0] << 8;
	ret |= buffer[1];

	return ret;
	//return buffer;
}
*/

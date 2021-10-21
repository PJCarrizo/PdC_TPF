/*
 * EEPROM_Port.c
 *
 *  Created on: 20 oct. 2021
 *      Author: Carrizo Pablo Jesús
 */

#include "EEPROM_Port.h"
#include "ssp_18xx_43xx.h"
bool_t spi_Config_EEPROM25LC1024( spiMap_t spi )

{

   bool_t retVal = TRUE;

   if( spi == SPI0 ) {

	   	   // Configure SPI pins for each board

         /* Set up clock and power for SSP1 module */
         // Configure SSP SSP1 pins
         Chip_SCU_PinMuxSet( 0xF, 4, (SCU_MODE_PULLUP | SCU_MODE_FUNC0)); 		// SSP1_SCK
         Chip_SCU_PinMuxSet( 0x1, 3, (SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC5)); // SSP1_MISO
         Chip_SCU_PinMuxSet( 0x1, 4, (SCU_MODE_PULLUP | SCU_MODE_FUNC5)); 		// SSP1_MOSI
         Chip_SCU_PinMuxSet( 0x6, 1, (SCU_MODE_PULLUP | SCU_MODE_FUNC0)); 		// Pin for SPI SS configured as GPIO output with pull-up
       	 Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 3, 0);						//Pin SS as output (GPIO0)

         // Initialize SSP Peripheral
         Chip_SSP_Init( LPC_SSP1 );
         Chip_SSP_Enable( LPC_SSP1 );


   }
   else {
      retVal = FALSE;
   }

   return retVal;
}

void chipSelect(uint8_t cs)
{
	if (cs == NULL)
	{
		gpioWrite( GPIO0, OFF );

	}

	else
	{
		gpioWrite( GPIO0, ON );

	}


}

void func_escritura (uint8_t wren)
{
	Chip_SSP_DATA_SETUP_T xferConfig;
	uint16_t buffer[1];
	buffer [0] = wren;
	xferConfig.tx_data = buffer[0];
	xferConfig.tx_cnt  = 0;
	xferConfig.rx_data = NULL;
	xferConfig.rx_cnt  = 0;
	xferConfig.length  = 1;
	// Funcion de LPCOpen
	Chip_SSP_RWFrames_Blocking(LPC_SSP1,  &xferConfig);

	return;
}


uint16_t func_lectura (void)
{
	Chip_SSP_DATA_SETUP_T xferConfig;
	uint8_t buffer[1];
	uint16_t ret;
	bool res;

	xferConfig.tx_data = NULL;
	xferConfig.tx_cnt  = 0;
	xferConfig.rx_data = buffer [0];
	xferConfig.rx_cnt  = 0;
	xferConfig.length  = 1;

	res = Chip_SSP_RWFrames_Blocking(LPC_SSP1,  &xferConfig);

	return buffer;
}

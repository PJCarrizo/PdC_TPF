/*
 * EEPROM_Port.h
 *
 *  Created on: 20 oct. 2021
 *      Author: Usuario
 */
#include "EEPROM_25LC1024.h"
#include "chip.h"
#include "sapi.h"

#ifndef PRACTICAS_PROGRAMACION_PRACTICAS_PROTOCOL_COM_PDC_TPF_INC_EEPROM_PORT_H_
#define PRACTICAS_PROGRAMACION_PRACTICAS_PROTOCOL_COM_PDC_TPF_INC_EEPROM_PORT_H_

bool_t spi_Config_EEPROM25LC1024( spiMap_t spi );
void func_escritura (uint8_t wren);
uint16_t func_lectura (void);


#endif /* PRACTICAS_PROGRAMACION_PRACTICAS_PROTOCOL_COM_PDC_TPF_INC_EEPROM_PORT_H_ */

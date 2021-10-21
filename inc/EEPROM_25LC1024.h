/*
 * EEPROM_25LC1024.h
 *
 *  Created on: 20 oct. 2021
 *      Author: Usuario
 */

#include "chip.h"
#include "sapi.h"

#ifndef PRACTICAS_PROGRAMACION_PRACTICAS_PROTOCOL_COM_PDC_TPF_INC_EEPROM_25LC1024_H_
#define PRACTICAS_PROGRAMACION_PRACTICAS_PROTOCOL_COM_PDC_TPF_INC_EEPROM_25LC1024_H_

void ini_spi_uart (void);
uint32_t funcion_menu(uint32_t opcion);
uint32_t write_data_EEPROM25LC1024 (uint8_t dato);
uint8_t read_data_EEPROM25LC1024 (void);
//uint32_t read_data_EEPROM25LC102 (uint32_t dato)
#endif /* PRACTICAS_PROGRAMACION_PRACTICAS_PROTOCOL_COM_PDC_TPF_INC_EEPROM_25LC1024_H_ */

#ifndef INITSPI_H_
#define INITSPI_H_

/* ============================================ INCLUDES ===================================================== */

#include "main.h"

/* ============================================ DEFINES ===================================================== */
#define SPI1_CS_PORT		GPIOE
#define SPI1_SCK_PORT		GPIOA
#define SPI1_MISO_PORT	GPIOA
#define SPI1_MOSI_PORT	GPIOA

#define SPI1_CS_PIN			PIN3
#define SPI1_SCK_PIN		PIN5
#define SPI1_MISO_PIN		PIN6
#define SPI1_MOSI_PIN		PIN7

/* ============================================ FUCTIONS ==================================================== */

void InitSPI1(void);
void SPI_WriteRegister(uint8_t registerAddress, uint8_t registerData);
uint8_t SPI_ReadRegister(uint8_t registerAddress);

#endif /* INITSPI_H_ */

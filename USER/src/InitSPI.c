#include "main.h"
#include "InitSPI.h"

void InitSPI1(void){

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;					// Enable Clock GPIOA
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;					// Enable Clock GPIOE
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;						// Enable Clock SPI1

	// GPIOE3 - SPI1 CS
	/* Configure GPIOE as output, meduim speed, no pull-up, pull-down */
	GPIOE->MODER 	&= 	~GPIO_MODER_MODER3_1;
	GPIOE->MODER 	|= 	 GPIO_MODER_MODER3_0;
	GPIOE->OTYPER	&= 	~GPIO_OTYPER_OT_3;
	GPIOE->PUPDR 	&= 	~GPIO_PUPDR_PUPDR3;
	GPIOE->OSPEEDR 	|= 	 GPIO_OSPEEDER_OSPEEDR3_0;
	GPIOE->OSPEEDR 	&= 	~GPIO_OSPEEDER_OSPEEDR3_1;

	// GPIOA5 - SPI1 SCK
	GPIOA->MODER |= (0x02<<5*2);								// Alternate func
	GPIOA->OSPEEDR |= (0x03<<5*2);							// Very high speed
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR5;					// No PP
	GPIOA->AFR[0] |=  (0x05<<5*4);							// Alternate func AF5 SPI1

	// GPIOA6 - SPI1 MISO
	GPIOA->MODER |= (0x02<<6*2);								// Alternate func
	GPIOA->OSPEEDR |= (0x03<<6*2);							// Very high speed
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR5;					// No PP
	GPIOA->AFR[0] |=  (0x05<<6*4);							// Alternate func AF5 SPI1

	// GPIOA7 - SPI1 MOSI
	GPIOA->MODER |= (0x02<<7*2);								// Alternate func
	GPIOA->OSPEEDR |= (0x03<<7*2);							// Very high speed
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR5;					// No PP
	GPIOA->AFR[0] |=  (0x05<<7*4);							// Alternate func AF5 SPI1

	SPI1->CR1 = 0x0;
	
	SPI1->CR1 |= SPI_CR1_MSTR;
	
	SPI1->CR1 |= SPI_CR1_SSM;										// Soft slave select
	SPI1->CR1 |= SPI_CR1_SSI;
	
	SPI1->CR1 |= SPI_CR1_CPOL;
	SPI1->CR1 |= SPI_CR1_CPHA;

	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;
	SPI1->CR1 &= ~SPI_CR1_RXONLY;							// Full duplex
	SPI1->CR1 &= ~SPI_CR1_DFF;								// 8bit frame format

	SPI1->CR1 |= SPI_CR1_BR_0;
	SPI1->CR1 |= SPI_CR1_BR_1;
	SPI1->CR1 |= SPI_CR1_BR_2;
	
	SPI1->CR1 |= SPI_CR1_SPE;

}


void SPI1_ON(GPIO_TypeDef* _SPIgpio, uint16_t _SPIpin){				
	GPIOPinReset(_SPIgpio, _SPIpin);
}

void SPI1_OFF(GPIO_TypeDef* _SPIgpio, uint16_t _SPIpin){				
	GPIOPinSet(_SPIgpio, _SPIpin);
}


uint8_t SPI1SendData(uint8_t data){
	
		while (!(SPI1->SR & SPI_SR_TXE)){};
			SPI1->DR = data;	
		while (!(SPI1->SR & SPI_SR_RXNE)){};
			data = SPI1->DR;
		return data;
	
}

void SPI_WriteRegister(uint8_t registerAddress, uint8_t registerData){

	SPI1_ON(SPI1_CS_PORT, SPI1_CS_PIN);	
	SPI1SendData( registerAddress );
	SPI1SendData( registerData );
	SPI1_OFF(SPI1_CS_PORT, SPI1_CS_PIN);

}

uint8_t SPI_ReadRegister(uint8_t registerAddress){

	SPI1_ON(SPI1_CS_PORT, SPI1_CS_PIN);	
	uint8_t registerData; 
	registerAddress |= (0x01<<7);
	SPI1SendData( registerAddress );
	registerData = SPI1SendData( 0x0F );
	SPI1_OFF(SPI1_CS_PORT, SPI1_CS_PIN);
	return registerData;
	
}


#include "InitUSART.h"

void InitUSART2(void){

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;							//Enable Clock GPIOA
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;             //Enable Clock for USART2

	// GPIOA2 - TX
	GPIOA->MODER 	|= (0x02<<2*2);											// Alternate mode
	GPIOA->OSPEEDR |= (0x03<<2*2);										// Very high speed
	GPIOA->AFR[0] 	|= (0x07<<4*2);										// Alternate func AF7 - USART2

	// GPIOA3 - RX
	GPIOA->MODER 	|= (0x02<<3*2);											// Alternate mode
	GPIOA->PUPDR 	&= ~GPIO_PUPDR_PUPDR3;							// Floating input
	GPIOA->AFR[0] 	|=  (0x07<<4*3);									// Alternate

	USART2 -> BRR = 0x1117;														// 9600
	USART2 -> CR1 |= USART_CR1_RE | USART_CR1_TE;			// Enable RX, TX
	USART2 -> CR1 |= USART_CR1_UE;										// Enable USART2
	USART2 -> CR1 |= USART_CR1_RXNEIE;								// Enable IT RX
	NVIC_EnableIRQ(USART2_IRQn);											// Enable IT USART2
}


void USART2_IRQHandler (void){

	if (USART2->SR & USART_SR_RXNE){

		USART2->SR &= ~USART_SR_RXNE;

		if (USART2->DR == '0'){

			USART2SendString ("OFF\r\n");
			GPIOPinReset(LED_PORT, LED_ORANGE_PIN);

		}

		if (USART2->DR == '1'){

			USART2SendString ("ON\r\n");
			GPIOPinSet(LED_PORT, LED_ORANGE_PIN);

		}
	}
}


void USART2SendChar (char chr){

	while (!(USART2->SR & USART_SR_TC));
	USART2->DR = chr;

}

void USART2SendString (char* str){

	uint8_t i = 0;

	while (str[i])
		USART2SendChar(str[i++]);

}

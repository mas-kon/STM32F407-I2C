#include "InitI2C.h"

void InitI2C1(void){

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;					// Enable Clock GPIOB
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;						// Enable Clock I2C1

	// GPIOB6 - I2C1 SCL
	/* Configure GPIOB as AF, high speed, pull-up */
	GPIOB->AFR[0]  &= ~GPIO_AFRL_AFRL6_0;					// 0100: AF4	
	GPIOB->AFR[0]  &= ~GPIO_AFRL_AFRL6_1;					// 0100: AF4	
	GPIOB->AFR[0]  |= GPIO_AFRL_AFRL6_2;					// 0100: AF4	
	GPIOB->AFR[0]  &= ~GPIO_AFRL_AFRL6_3;					// 0100: AF4	
	GPIOB->MODER   &= ~GPIO_MODER_MODE6_0;				// 10: Alternate function mode
	GPIOB->MODER   |= GPIO_MODER_MODE6_1;					// 10: Alternate function mode
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_0;		// 11: Very high speed
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_1;		// 11: Very high speed
	GPIOB->OTYPER	 |= GPIO_OTYPER_OT6;						//  1: Open-drain
	GPIOB->PUPDR	 &= ~GPIO_PUPDR_PUPD6_0;				// 01: No Pull-up
	GPIOB->PUPDR	 &= ~GPIO_PUPDR_PUPD6_1;				// 01: No Pull-up
	
	// GPIOB7 - I2C1 SDA
	/* Configure GPIOB as AF, high speed, pull-up */
	GPIOB->AFR[0]  &= ~GPIO_AFRL_AFRL7_0;					// 0100: AF4	
	GPIOB->AFR[0]  &= ~GPIO_AFRL_AFRL7_1;					// 0100: AF4	
	GPIOB->AFR[0]  |= GPIO_AFRL_AFRL7_2;					// 0100: AF4	
	GPIOB->AFR[0]  &= ~GPIO_AFRL_AFRL7_3;					// 0100: AF4	
	GPIOB->MODER   &= ~GPIO_MODER_MODE7_0;				// 10: Alternate function mode
	GPIOB->MODER   |= GPIO_MODER_MODE7_1;					// 10: Alternate function mode
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7_0;		// 11: Very high speed
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7_1;		// 11: Very high speed
	GPIOB->OTYPER	 |= GPIO_OTYPER_OT7;						// 	1: Open-drain
	GPIOB->PUPDR	 &= ~GPIO_PUPDR_PUPD7_0;				// 00: No Pull-up
	GPIOB->PUPDR	 &= ~GPIO_PUPDR_PUPD7_1;				// 00: No Pull-up

	
/***************************************************************************************
		� FREQ[5:0] ������� APB (�� ������� ����������� I2C, � ����� ������ APB1) � ��� .
    � ����� ������������ ������� APB1 - 42��� .
*****************************************************************************************/
		// ������� � FREQ �������� FPCLK1(APB1)
	I2C1->CR2 &= ~I2C_CR2_FREQ;
	I2C1->CR2 |= I2C_CR2_FREQ_5 | I2C_CR2_FREQ_3 | I2C_CR2_FREQ_1;		// 42 MHz = 0B101010
	
/***************************************************************************************
	������� �������� SCL (http://mcu.goodboard.ru/viewtopic.php?id=14):
	
	FSCL - ������� SCL ��� SM - 100���, ��� FM - 400���
	TSCL - ������ SCL TSCL = 1/FSCL = Tf + TLOW + Tr + THIGH
  TSCL ��� SM 10000 nS   
	TSCL ��� FM  2500 nS 
	
	� STM �������� Tf Tr �� �����������:
	TSCL = TLOW + THIGH

	TPCLK1 ����� 1/FPCLK1 � � ����� ������ 1/42 000 000  = 24nS

	��� SM (��� SMBUS):
		TSCL - 10000 nS
		TPCLK1 -  24 nS   
		TLOW + THIGH = 10000 nS
		CCR * TPCLK1 + CCR * TPCLK1 = 10 000nS
		CCR = (10 000nS/2) / TPCLK1
		CCR = 208
   
	��� FM 
		TSCL - 2500nS
		TPCLK1 - 24nS   
		TLOW + THIGH = 2500nS

	���� DUTY=0 (Fm mode tlow/thigh = 2)
      
	2*CCR * TPCLK1 + CCR * TPCLK1 = 2500nS/2
	CCR = (2500nS/3) / TPCLK1 
	CCR = 34    
 
  ���� DUTY=1	(Fm mode tlow/thigh = 16/9)
	
	16*CCR * TPCLK1 + 9*CCR * TPCLK1 = 2500nS
	CCR = (2500nS/25) / TPCLK1 
	CCR = 4 
*****************************************************************************************/
	
	I2C1->CCR &= ~I2C_CCR_CCR;
	I2C1->CCR |= 208;							// 
	I2C1->CCR &= ~I2C_CCR_FS;			// StandartMode, 100 kHz

/***************************************************************************************
	TRISE - ������������ ����� ���������� ��������, � ���� ��������� ��������� ��� Tr max
	�� ������������ i2c:
	 Tr max Sm - 1000 nS
	 Tr max Fm - 300nS
	 TPCLK1  - 24nS
  � TRISE ��������� ����������� (Tr max/TPCLK1)+1
   TRISE (Fm) = (300/24)+1 = 14
	 TRISE (Sm)= (1000/24)+1 = 43
*****************************************************************************************/
	I2C1->TRISE |= 43;
	
	SPI1->CR1 |= SPI_CR1_MSTR; 			//���������� ������ ���� ��������
	
	// �������� I2C
	I2C1->CR1 |= I2C_CR1_PE;
}


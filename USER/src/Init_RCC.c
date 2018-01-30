#include "stm32f4xx.h"
#include "init_RCC.h"
#define PLL_M 		4
#define PLL_N 	168
#define PLL_P  		2
#define PLL_Q			7

/* ================================== Configure RCC ================================== */
void InitRCC(void){ 
	
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP;
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLQ;
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC;

	RCC->CR |= RCC_CR_HSEON;																		// Enable HSE
	while (!(RCC->CR & RCC_CR_HSERDY)) {};											// Wait for ready HSE
		
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;														// AHB = SYSCLK/1 = 168MHz
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;														// APB1 = HCLK/4 (PCLK1 = 42 MHz, APB1 Timers = 84 MHz)
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;														// APB2 = HCLK/2 (PCLK2 = 84 MHz, APB2 Timers = 168 MHz)
	
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_3;													// PLLM = 8
	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLN_4 | RCC_PLLCFGR_PLLN_6 
																		  | RCC_PLLCFGR_PLLN_8); 	// PLLN = 336
		
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP;													// PLLP = 2
		
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC;													// HSE oscillator clock selected as PLL and PLLI2S clock entry
		
	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLQ_0 | RCC_PLLCFGR_PLLQ_1
																		  | RCC_PLLCFGR_PLLQ_2);	// PLLQ = 7
	
	RCC->CR |= RCC_CR_PLLON;                      							// Enable PLL
	while(!(RCC->CR & RCC_CR_PLLRDY)) {}      									// Wait till PLL is ready
		
	FLASH->ACR |= FLASH_ACR_ICEN | FLASH_ACR_DCEN 
						 | FLASH_ACR_LATENCY_5WS | FLASH_ACR_PRFTEN;			// Cloclk Flash memory

	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;																// PLL selected as system clock	
	while (!(RCC->CFGR & RCC_CFGR_SWS_PLL)) {}									// Wait for PLL/PLLP used as system clock
		
}

void MCO_Init(void)
{
  
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER &=~ GPIO_MODER_MODE9;
	GPIOC->MODER |= GPIO_MODER_MODE9_1;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9;
	RCC->CFGR |= RCC_CFGR_MCO2PRE;

}

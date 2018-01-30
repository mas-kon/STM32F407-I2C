#include "main.h"

uint8_t counter = 0;	

void Test_MCP01(void);
void MCP_Blink(void);

int main(void)
{

	InitRCC();
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);
	
	InitTIM7();
	InitTIM6();
	InitLED();
	InitBUTTON();
 
	InitI2C1();
	MCP23017_Init();
	
	
	GPIOPinSet(LED_PORT, LED_USB_PIN);
	
	while (1)
	{
		

	}
	
}


void SysTick_Handler(){

}

void TIM7_IRQHandler(){ 				// 500 мс
	
	TIM7->SR &=~TIM_SR_UIF;
	counter++;
	GPIOPinToggle(LED_PORT, LED_USB_PIN); // для проверки, что не висим..
}


void TIM6_DAC_IRQHandler(){			// 10 мс
	TIM6->SR &=~TIM_SR_UIF;	

	MCP_Blink();
	Test_MCP01();
	
}


void Test_MCP01 (void){

	if (MCP23017_ReadPin(MCP23017_ADDR, MCP23017_REG_ADDR_GPIOA, MCP23017_PIN1))
		 { GPIOPinSet(LED_PORT, LED_GREEN_PIN); }
	else 
		 { GPIOPinReset(LED_PORT, LED_GREEN_PIN); }	

}


void MCP_Blink(void){
	if (counter % 2)
	{
		MCP23017_WritePin(MCP23017_ADDR, MCP23017_REG_ADDR_GPIOA, MCP23017_PIN1, MCP23017_PIN_SET);
		MCP23017_WritePin(MCP23017_ADDR, MCP23017_REG_ADDR_GPIOA, MCP23017_PIN3, MCP23017_PIN_RESET);
	}
	else
	{
		MCP23017_WritePin(MCP23017_ADDR, MCP23017_REG_ADDR_GPIOA, MCP23017_PIN1, MCP23017_PIN_RESET);
		MCP23017_WritePin(MCP23017_ADDR, MCP23017_REG_ADDR_GPIOA, MCP23017_PIN3, MCP23017_PIN_SET);
	}
}



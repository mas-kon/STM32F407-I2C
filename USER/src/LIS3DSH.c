#include "LIS3DSH.h"

void InitLIS3DSH(void){
	
uint8_t SpiData = 0;

	SPI_WriteRegister(0x20, 0x97);
	SPI_WriteRegister(0x24, 0xD0);
	SpiData = SPI_ReadRegister(0x0F);
	
	if (SpiData == LIS3DSH_ID) {
		GPIOPinToggle(LED_PORT, LED_USB_PIN);
	}
	
}

void TestLIS3DSH(void){
	
		int16_t XXX = 0;
		int16_t YYY = 0;
		int16_t ZZZ = 0;

		XXX = (SPI_ReadRegister(0x29) << 8) | SPI_ReadRegister(0x28);
		YYY = (SPI_ReadRegister(0x2B) << 8) | SPI_ReadRegister(0x2A);
		ZZZ = (SPI_ReadRegister(0x2D) << 8) | SPI_ReadRegister(0x2C);
		
		if (XXX > HYSTERESIS)
			{ GPIOPinSet(LED_PORT, LED_RED_PIN); }
		else if (XXX < -HYSTERESIS)
			{ GPIOPinSet(LED_PORT, LED_GREEN_PIN); }
		else
		{
			GPIOPinReset(LED_PORT, LED_RED_PIN);
			GPIOPinReset(LED_PORT, LED_GREEN_PIN);
		}
		
		if (YYY > HYSTERESIS)
			{ GPIOPinSet(LED_PORT, LED_ORANGE_PIN); }
		else if (YYY < -HYSTERESIS)
			{ GPIOPinSet(LED_PORT, LED_BLUE_PIN); }
		else
		{
			GPIOPinReset(LED_PORT, LED_ORANGE_PIN);
			GPIOPinReset(LED_PORT, LED_BLUE_PIN);
		}
		
		if (ZZZ > HYSTERESIS)
			{ GPIOPinSet(LED_PORT, LED_USB_PIN); }
		else if (ZZZ < -HYSTERESIS)
			{ GPIOPinSet(LED_PORT, LED_USB_PIN); }
		else
		{
			GPIOPinReset(LED_PORT, LED_USB_PIN);
			GPIOPinReset(LED_PORT, LED_USB_PIN);
		}
	
}


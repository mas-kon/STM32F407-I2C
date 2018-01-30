#include "button.h"

	uint8_t button_pressed_flag = 0;
	uint8_t button_unpressed_flag = 1;
	uint8_t button_current_state = 0;
	uint16_t button_temp_counter = 0;

void Button_state(GPIO_TypeDef* _gpio, uint16_t _pin)
{
	uint8_t button_state = 0;

	button_current_state = GPIOPinRead( _gpio, _pin);
	
		if (button_current_state == 1)
		{
  		if (button_temp_counter < 5)
			{
				button_temp_counter ++;
			}
			else {
				if (button_state == 0)
				{
				button_state = 1;
				button_pressed_flag = 1;
				}
			}
		} else {
			if (button_temp_counter > 0)
			{
				button_temp_counter --;
			}
			else {
				if (button_state == 1)
				{
				button_state = 0;
				button_unpressed_flag = 1;	
				}
			}
	}
}

uint8_t getButtonPressedFlag(void)
{
	return button_pressed_flag;
}

uint8_t getButtonUnpressedFlag(void)
{
	return button_unpressed_flag;
}

void clearButtonPressedFlag(void)
{
	button_pressed_flag = 0;
}

void clearButtonUnpressedFlag(void)
{
	button_unpressed_flag = 0;
}


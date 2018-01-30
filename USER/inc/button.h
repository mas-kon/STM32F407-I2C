#ifndef BUTTON_H
#define BUTTON_H

/* ============================================ INCLUDES ===================================================== */

#include "main.h"

/* ============================================ DEFINES ===================================================== */

#define BUTTON_PORT						GPIOA
#define BUTTON_PIN						PIN0
#define	BUTTON_DEBOUNCE				5

/* ============================================ FUCTIONS ==================================================== */

void Button_state(GPIO_TypeDef* _gpio, uint16_t _pin);
uint8_t getButtonPressedFlag(void);
uint8_t getButtonUnpressedFlag(void);
void clearButtonPressedFlag(void);
void clearButtonUnpressedFlag(void);

#endif /* BUTTON_H */

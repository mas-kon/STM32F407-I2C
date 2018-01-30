#ifndef INIT_LED_H_
#define INIT_LED_H_

/* ============================================ INCLUDES ===================================================== */

#include "main.h"

/* ============================================ DEFINES ===================================================== */

#define LED_PORT						GPIOD
#define LED_GREEN_PIN				PIN12
#define LED_ORANGE_PIN			PIN13
#define LED_RED_PIN					PIN14
#define LED_BLUE_PIN				PIN15
#define LED_USB_PIN					PIN5

/* ============================================ FUCTIONS ==================================================== */
void InitLED(void);
void InitBUTTON(void);

#endif /* INIT_LED_H_ */

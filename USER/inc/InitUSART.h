#ifndef INITUSART_H_
#define INITUSART_H_

/* ============================================ INCLUDES ===================================================== */

#include "main.h"

/* ============================================ DEFINES ===================================================== */


/* ============================================ FUCTIONS ==================================================== */

void InitUSART2(void);
void USART2SendChar (char chr);
void USART2SendString (char* str);


void USART_Init (void);
void USART_Send_Byte (char chr);
void USART_Send_String (char* str);

#endif /* INITUSART_H_ */

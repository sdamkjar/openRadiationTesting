/***************************************************************************//**
 * @file print.h
 * @brief 
 * @author Stefan Damkjar
 * @version 
 ******************************************************************************/

#ifndef __PRINT_H
#define __PRINT_H

/* Include libraries */
#include "em_usart.h"
#include "em_leuart.h"

/* Function prototypes*/
void PRINT_Stringln(USART_TypeDef* uart, char* data);
void PRINT_StringlnLE(LEUART_TypeDef* leuart, char* data);
void PRINT_Char(USART_TypeDef* uart, char data);
void PRINT_time(USART_TypeDef* uart, uint32_t currentTime);
void PRINT_timeLE(LEUART_TypeDef* leuart, uint32_t currentTime);
void PRINT_current(USART_TypeDef* uart, int curr);

#endif

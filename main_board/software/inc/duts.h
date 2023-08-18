/******************************************************************************
 * @file duts.h
 * @brief 
 * @author 
 * @version 
 ******************************************************************************/


#ifndef __DUTS_H
#define __DUTS_H

#include "em_usart.h"
#include "em_leuart.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/


/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

typedef enum
{
  DUT_A		=	0,
  DUT_B		=	1,
  DUT_C		=	2,
  DUT_D		=	3,
  DUT_CONTROL = 4
} DUTNUM_TypeDef;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/


void DUTS_initIRQs_USART(USART_TypeDef* usart, IRQn_Type rxIRQn);
void DUTS_initIRQs_LEUART(LEUART_TypeDef* leuart, IRQn_Type rxIRQn);
uint8_t DUTS_getChar(DUTNUM_TypeDef dutNum);
void DUTS_PutChar(uint8_t, DUTNUM_TypeDef dutNum);
void DUTS_purge(DUTNUM_TypeDef dutNum);


#endif /* DUTS_H_ */

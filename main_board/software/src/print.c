/***************************************************************************//**
 * @file print.c
 * @brief 
 * @author Stefan Damkjar
 * @version 
 ******************************************************************************/

#include "print.h"
#include "em_usart.h"
#include "em_usart.h"

static char  StringBuf[15];

/***************************************************************************//**
 * @brief Must be null terminated.
 ******************************************************************************/
void PRINT_Stringln(USART_TypeDef* uart, char* data)
{
  int i = 0;
  for(i = 0;data[i]!='\0';i++){
    USART_Tx(uart,data[i]);
  }
  USART_Tx(uart,'\n');
  //if(open) f_printf(&fsrc,"%s", data);
}

/***************************************************************************//**
 * @brief Must be null terminated.
 ******************************************************************************/
void PRINT_StringlnLE(LEUART_TypeDef* leuart, char* data)
{
  int i = 0;
  for(i = 0;data[i]!='\0';i++){
	  LEUART_Tx(leuart,data[i]);
  }
  LEUART_Tx(leuart,'\n');
  //if(open) f_printf(&fsrc,"%s", data);
}

/***************************************************************************//**
 * @brief
 ******************************************************************************/
void PRINT_Char(USART_TypeDef* uart, char data)
{
  USART_Tx(uart,data);
  //if(open) f_printf(&fsrc,"%c", data);
}

/***************************************************************************//**
 * @brief
 ******************************************************************************/
void PRINT_time(USART_TypeDef* uart, uint32_t currentTime)
{
  uint32_t msec = currentTime % 1000;

  currentTime /= 1000;

  uint8_t sec = currentTime % 60;

  currentTime /= 60;

  uint8_t min = currentTime % 60;

  currentTime /= 60;

  uint8_t i = 0;


  StringBuf[0] = '\r';
  StringBuf[1] = 0x30 + (currentTime / 10);
  StringBuf[2] = 0x30 + (currentTime % 10);
  StringBuf[3] = ':';
  StringBuf[4] = 0x30 + (min / 10);
  StringBuf[5] = 0x30 + (min % 10);
  StringBuf[6] = ':';
  StringBuf[7] = 0x30 + (sec / 10);
  StringBuf[8] = 0x30 + (sec % 10);
  StringBuf[9] = '.';
  StringBuf[10] = 0x30 + (msec / 100);
  StringBuf[11] = 0x30 + ((msec / 10) % 10);
  StringBuf[12] = 0x30 + (msec % 10);
  StringBuf[13] = '\t';
  StringBuf[14] = '\0';

  //if(open) f_printf(&fsrc,"%s", displayStringBuf);
  for(i = 0;i<15;i++){
    USART_Tx(uart,StringBuf[i]);
  }
}

/***************************************************************************//**
 * @brief
 ******************************************************************************/
void PRINT_timeLE(LEUART_TypeDef* leuart, uint32_t currentTime)
{
  uint32_t msec = currentTime % 1000;

  currentTime /= 1000;

  uint8_t sec = currentTime % 60;

  currentTime /= 60;

  uint8_t min = currentTime % 60;

  currentTime /= 60;

  uint8_t i = 0;


  StringBuf[0] = '\r';
  StringBuf[1] = 0x30 + (currentTime / 10);
  StringBuf[2] = 0x30 + (currentTime % 10);
  StringBuf[3] = ':';
  StringBuf[4] = 0x30 + (min / 10);
  StringBuf[5] = 0x30 + (min % 10);
  StringBuf[6] = ':';
  StringBuf[7] = 0x30 + (sec / 10);
  StringBuf[8] = 0x30 + (sec % 10);
  StringBuf[9] = '.';
  StringBuf[10] = 0x30 + (msec / 100);
  StringBuf[11] = 0x30 + ((msec / 10) % 10);
  StringBuf[12] = 0x30 + (msec % 10);
  StringBuf[13] = '\t';
  StringBuf[14] = '\0';

  //if(open) f_printf(&fsrc,"%s", displayStringBuf);
  for(i = 0;i<15;i++){
    LEUART_Tx(leuart,StringBuf[i]);
  }
}

void PRINT_current(USART_TypeDef* uart, int curr)
{
	uint8_t i = 0;

	StringBuf[0] = '\t';
	if(curr < 0) {
		StringBuf[1] = '-';
		curr = -curr;
	}
	else StringBuf[1] = '+';
	StringBuf[2] = 0x30 + (curr / 100000);
	if(StringBuf[2] == '0') StringBuf[2] = ' ';
	StringBuf[3] = 0x30 + ((curr / 10000) % 10);
	if(StringBuf[3] == '0') StringBuf[3] = ' ';
	StringBuf[4] = 0x30 + ((curr /  1000) % 10);
	StringBuf[5] = '.';
	StringBuf[6] = 0x30 + ((curr /   100) % 10);
	StringBuf[7] = 0x30 + ((curr /    10) % 10);
	StringBuf[8] = 'm';
	StringBuf[9] = 'A';
	StringBuf[10] = '\0';
    for(i = 0;i<11;i++){
	  USART_Tx(uart,StringBuf[i]);
    }
}

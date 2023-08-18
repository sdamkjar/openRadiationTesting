/*******************************************************************************
 * (c) Copyright 2012-2015 Microsemi SoC Products Group.  All rights reserved.
 *
 *  Simple SmartFusion2 microcontroller subsystem UART example program
 *  transmitting a greeting message using UART1. Any characters received on
 *  UART1 are echoed back. The UART configuration is specified as part of the
 *  call to MSS_UART_init().
 *
 * SVN $Revision: 7985 $
 * SVN $Date: 2015-10-12 12:26:08 +0530 (Mon, 12 Oct 2015) $
 */
#include "drivers/mss_uart/mss_uart.h"

#include <stdio.h>
#include <stdint.h>

#define DUT_ID "\n\t,7D,"

#define MAX_RETRIES 10

#define BUFFER_SIZE 20
#define TEST_SIZE 14000

#define NVM_ADDRESS_START 0
#define NVM_ADDRESS_END   250000

typedef unsigned int word;

volatile word testMemArray[TEST_SIZE] = {0};
unsigned int ram_errors = 0;
word previous_write = 0;
word next_write = 0;
word crc = 0;
unsigned int irRetries = 0;
unsigned int iteration = 0;

char buffer[BUFFER_SIZE] = {0};

void PRINT_Stringln(char* data);
word CRC_calc(word start, word end);
void RAM_test(void);

/*------------------------------------------------------------------------------
  UART selection.
  Replace the line below with this one if you want to use UART1 instead of
  UART0:
  mss_uart_instance_t * const gp_my_uart = &g_mss_uart1;
 */
mss_uart_instance_t * const gp_my_uart = &g_mss_uart0;

/*==============================================================================
 * main function.
 */
int main()
{
    
    /* Turn off the watchdog */
    SYSREG->WDOG_CR = 0;
    
    unsigned int i = 0;

    /*--------------------------------------------------------------------------
     * Initialize and configure UART.
     */
    MSS_UART_init(gp_my_uart,
    			250000,
                  MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);

    /*--------------------------------------------------------------------------
     * Send greeting message over the UART.
     */
    PRINT_Stringln("boot\0");
    /*--------------------------------------------------------------------------
     */
    for (;;)
    {
        PRINT_Stringln("ram\0");

        RAM_test();

        PRINT_Stringln("nvm\0");

        crc = CRC_calc(NVM_ADDRESS_START,NVM_ADDRESS_END);

        sprintf(buffer,"CRC:%x\0",crc);
        PRINT_Stringln(buffer);

        sprintf(buffer,"end%u\0",iteration++);
        PRINT_Stringln(buffer);

        for ( i = 0 ; i < 2000000 ; i++){
        	 /*do nothing*/
        }
    }
}

void PRINT_Stringln(char* data) {

  MSS_UART_polled_tx_string(gp_my_uart, (const uint8_t *)DUT_ID);
  MSS_UART_polled_tx_string(gp_my_uart, (const uint8_t *)data);
}

word CRC_calc(word start, word end)
{
  word crc = 0x0;
  uint8_t  *data;


  for (data = start; data < end; data++)
  {
    crc  = (crc >> 8) | (crc << 8);
    crc ^= *data;
    crc ^= (crc & 0xff) >> 4;
    crc ^= crc << 12;
    crc ^= (crc & 0xff) << 5;
  }
  return crc;
}

void RAM_test(void) {
  word read = 0;
  unsigned int j = 0;
  previous_write = next_write;
  next_write = next_write ^ (word)(~0);
  for(j = 0; j<TEST_SIZE; j++) {
    read = testMemArray[j];
    if (read != previous_write) {
      // delayed read
      sprintf(buffer,"DR:%0x,%0x,%0x\0",j,read,previous_write);
      PRINT_Stringln(buffer);
      ram_errors++;
    }
    testMemArray[j]= next_write;
    read = testMemArray[j];
    if (read != next_write) {
      // instantaneous read
      sprintf(buffer,"IR:%0x,%0x,%0x\0",j,read,previous_write);
      PRINT_Stringln(buffer);
      irRetries++;
    }
    else irRetries = 0;

    if(irRetries > MAX_RETRIES){
      PRINT_Stringln("SEFI!\0");
      while (1){
        /* DO NOTHING */
      }
    }
  }
  sprintf(buffer,"RE:%u\0",ram_errors);
  PRINT_Stringln(buffer);
}



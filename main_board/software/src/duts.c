
/******************************************************************************
 * @file duts.c
 * @brief 
 * @author 
 * @version 
 ******************************************************************************/

#define BUF_DEFAULT {{0},0,0,0,0}
#define BUFFERSIZE 10000

#include "em_usart.h"
#include "em_leuart.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "duts.h"
#include "InitDevice.h"

typedef struct {
  char data[BUFFERSIZE];
  uint16_t wrI;
  uint16_t rdI;
  uint16_t pendingBytes;
  uint8_t  overflow;
} data_buffer;

data_buffer rxBuf_LEUART0  = BUF_DEFAULT;
data_buffer txBuf_LEUART0  = BUF_DEFAULT;
data_buffer rxBuf_LEUART1  = BUF_DEFAULT;
data_buffer txBuf_LEUART1  = BUF_DEFAULT;
data_buffer rxBuf_UART0  = BUF_DEFAULT;
data_buffer txBuf_UART0  = BUF_DEFAULT;
data_buffer rxBuf_UART1  = BUF_DEFAULT;
data_buffer txBuf_UART1  = BUF_DEFAULT;
data_buffer rxBuf_USART0 = BUF_DEFAULT;
data_buffer txBuf_USART0 = BUF_DEFAULT;
data_buffer rxBuf_USART1 = BUF_DEFAULT;
data_buffer txBuf_USART1 = BUF_DEFAULT;
data_buffer rxBuf_USART2 = BUF_DEFAULT;
data_buffer txBuf_USART2 = BUF_DEFAULT;
data_buffer rxBuf_USART3 = BUF_DEFAULT;
data_buffer txBuf_USART3 = BUF_DEFAULT;
data_buffer rxBuf_USART4 = BUF_DEFAULT;
data_buffer txBuf_USART4 = BUF_DEFAULT;

/**************************************************************************//**
 * @brief UART0 RX IRQ Handler
 *****************************************************************************/
void UART0_RX_IRQHandler(void)
{
  /* Check for RX data valid interrupt */
  if (UART0->STATUS & UART_STATUS_RXDATAV)
  {
    /* Copy data into RX Buffer */
    uint8_t rxData = USART_Rx(UART0);
    if(!rxBuf_UART0.overflow)
	{
	  rxBuf_UART0.data[rxBuf_UART0.wrI] = rxData;
	  rxBuf_UART0.wrI = (rxBuf_UART0.wrI + 1) % BUFFERSIZE;
	  rxBuf_UART0.pendingBytes++;
	}

    /* Flag Rx overflow */
    if (rxBuf_UART0.pendingBytes > BUFFERSIZE)
    {
    	rxBuf_UART0.overflow = true;
    }

    /* Clear RXDATAV interrupt */
    USART_IntClear(UART0, UART_IF_RXDATAV);
  }
}

/**************************************************************************//**
 * @brief UART0 RX IRQ Handler
 *****************************************************************************/
void UART1_RX_IRQHandler(void)
{
  /* Check for RX data valid interrupt */
  if (UART0->STATUS & UART_STATUS_RXDATAV)
  {
    /* Copy data into RX Buffer */
    uint8_t rxData = USART_Rx(UART0);
    if(!rxBuf_UART0.overflow)
  {
    rxBuf_UART0.data[rxBuf_UART0.wrI] = rxData;
    rxBuf_UART0.wrI = (rxBuf_UART0.wrI + 1) % BUFFERSIZE;
    rxBuf_UART0.pendingBytes++;
  }

    /* Flag Rx overflow */
    if (rxBuf_UART0.pendingBytes > BUFFERSIZE)
    {
      rxBuf_UART0.overflow = true;
    }

    /* Clear RXDATAV interrupt */
    USART_IntClear(UART0, UART_IF_RXDATAV);
  }
}

/**************************************************************************//**
 * @brief UART0 RX IRQ Handler
 *****************************************************************************/
void USART0_RX_IRQHandler(void)
{
  /* Check for RX data valid interrupt */
  if (USART0->STATUS & UART_STATUS_RXDATAV)
  {
    /* Copy data into RX Buffer */
    uint8_t rxData = USART_Rx(USART0);
    if(!rxBuf_USART0.overflow)
  {
    rxBuf_USART0.data[rxBuf_USART0.wrI] = rxData;
    rxBuf_USART0.wrI = (rxBuf_USART0.wrI + 1) % BUFFERSIZE;
    rxBuf_USART0.pendingBytes++;
  }

    /* Flag Rx overflow */
    if (rxBuf_USART0.pendingBytes > BUFFERSIZE)
    {
      rxBuf_USART0.overflow = true;
    }

    /* Clear RXDATAV interrupt */
    USART_IntClear(USART0, USART_IF_RXDATAV);
  }
}

/**************************************************************************//**
 * @brief UART0 RX IRQ Handler
 *****************************************************************************/
void USART1_RX_IRQHandler(void)
{
  /* Check for RX data valid interrupt */
  if (USART1->STATUS & UART_STATUS_RXDATAV)
  {
    /* Copy data into RX Buffer */
    uint8_t rxData = USART_Rx(USART1);
    if(!rxBuf_USART1.overflow)
    {
      rxBuf_USART1.data[rxBuf_USART1.wrI] = rxData;
      rxBuf_USART1.wrI = (rxBuf_USART1.wrI + 1) % BUFFERSIZE;
      rxBuf_USART1.pendingBytes++;
    }

    /* Flag Rx overflow */
    if (rxBuf_USART1.pendingBytes > BUFFERSIZE)
    {
      rxBuf_USART1.overflow = true;
    }

    /* Clear RXDATAV interrupt */
    USART_IntClear(USART1, USART_IF_RXDATAV);
  }
}

/**************************************************************************//**
 * @brief UART0 RX IRQ Handler
 *****************************************************************************/
void USART2_RX_IRQHandler(void)
{
  /* Check for RX data valid interrupt */
  if (USART2->STATUS & UART_STATUS_RXDATAV)
  {
    /* Copy data into RX Buffer */
    uint8_t rxData = USART_Rx(USART2);
    if(!rxBuf_USART2.overflow)
    {
      rxBuf_USART2.data[rxBuf_USART2.wrI] = rxData;
      rxBuf_USART2.wrI = (rxBuf_USART2.wrI + 1) % BUFFERSIZE;
      rxBuf_USART2.pendingBytes++;
    }

    /* Flag Rx overflow */
    if (rxBuf_USART2.pendingBytes > BUFFERSIZE)
    {
      rxBuf_USART2.overflow = true;
    }

    /* Clear RXDATAV interrupt */
    USART_IntClear(USART2, USART_IF_RXDATAV);
  }
}

/**************************************************************************//**
 * @brief UART0 RX IRQ Handler
 *****************************************************************************/
void USART3_RX_IRQHandler(void)
{
  /* Check for RX data valid interrupt */
  if (USART3->STATUS & UART_STATUS_RXDATAV)
  {
    /* Copy data into RX Buffer */
    uint8_t rxData = USART_Rx(USART3);
    if(!rxBuf_USART3.overflow)
    {
      rxBuf_USART3.data[rxBuf_USART3.wrI] = rxData;
      rxBuf_USART3.wrI = (rxBuf_USART3.wrI + 1) % BUFFERSIZE;
      rxBuf_USART3.pendingBytes++;
    }

    /* Flag Rx overflow */
    if (rxBuf_USART3.pendingBytes > BUFFERSIZE)
    {
      rxBuf_USART3.overflow = true;
    }

    /* Clear RXDATAV interrupt */
    USART_IntClear(USART3, USART_IF_RXDATAV);
  }
}

/**************************************************************************//**
 * @brief UART0 RX IRQ Handler
 *****************************************************************************/
void USART4_RX_IRQHandler(void)
{
  /* Check for RX data valid interrupt */
  if (USART4->STATUS & UART_STATUS_RXDATAV)
  {
    /* Copy data into RX Buffer */
    uint8_t rxData = USART_Rx(USART4);
    if(!rxBuf_USART4.overflow)
    {
      rxBuf_USART4.data[rxBuf_USART4.wrI] = rxData;
      rxBuf_USART4.wrI = (rxBuf_USART4.wrI + 1) % BUFFERSIZE;
      rxBuf_USART4.pendingBytes++;
    }

    /* Flag Rx overflow */
    if (rxBuf_USART4.pendingBytes > BUFFERSIZE)
    {
      rxBuf_USART4.overflow = true;
    }

    /* Clear RXDATAV interrupt */
    USART_IntClear(USART4, USART_IF_RXDATAV);
  }
}


/**************************************************************************//**
 * @brief LEUART0 IRQ Handler
 *****************************************************************************/
void LEUART0_IRQHandler(void)
{
  /* Check for RX data valid interrupt */
  if (LEUART0->STATUS & LEUART_STATUS_RXDATAV)
  {
    /* Copy data into RX Buffer */
    uint8_t rxData = LEUART_Rx(LEUART0);
    if(!rxBuf_LEUART0.overflow)
  {
    rxBuf_LEUART0.data[rxBuf_LEUART0.wrI] = rxData;
    rxBuf_LEUART0.wrI = (rxBuf_LEUART0.wrI + 1) % BUFFERSIZE;
    rxBuf_LEUART0.pendingBytes++;
  }

    /* Flag Rx overflow */
    if (rxBuf_LEUART0.pendingBytes > BUFFERSIZE)
    {
      rxBuf_LEUART0.overflow = true;
    }

    /* Clear RXDATAV interrupt */
    LEUART_IntClear(LEUART0, LEUART_IF_RXDATAV);
  }
}

/**************************************************************************//**
 * @brief LEUART0 IRQ Handler
 *****************************************************************************/
void LEUART1_IRQHandler(void)
{
  /* Check for RX data valid interrupt */
  if (LEUART1->STATUS & LEUART_STATUS_RXDATAV)
  {
    /* Copy data into RX Buffer */
    uint8_t rxData = LEUART_Rx(LEUART1);
    if(!rxBuf_LEUART1.overflow)
  {
    rxBuf_LEUART1.data[rxBuf_LEUART1.wrI] = rxData;
    rxBuf_LEUART1.wrI = (rxBuf_LEUART1.wrI + 1) % BUFFERSIZE;
    rxBuf_LEUART1.pendingBytes++;
  }

    /* Flag Rx overflow */
    if (rxBuf_LEUART1.pendingBytes > BUFFERSIZE)
    {
      rxBuf_LEUART1.overflow = true;
    }

    /* Clear RXDATAV interrupt */
    LEUART_IntClear(LEUART1, LEUART_IF_RXDATAV);
  }
}

void DUTS_initIRQs_USART(USART_TypeDef* usart, IRQn_Type rxIRQn)
{
  /* Prepare UART Rx and Tx interrupts */
  USART_IntClear(usart, _UART_IF_MASK);
  USART_IntEnable(usart, UART_IF_RXDATAV);
  NVIC_ClearPendingIRQ(rxIRQn);
  NVIC_EnableIRQ(rxIRQn);
}

void DUTS_initIRQs_LEUART(LEUART_TypeDef* leuart, IRQn_Type rxIRQn)
{
  /* Prepare UART Rx and Tx interrupts */
  LEUART_IntClear(leuart, _LEUART_IF_MASK);
  LEUART_IntEnable(leuart, LEUART_IF_RXDATAV);
  NVIC_ClearPendingIRQ(rxIRQn);
  NVIC_EnableIRQ(rxIRQn);
}

void DUTS_purge(DUTNUM_TypeDef dutNum)
{
  if (dutNum == DUT_A){
    rxBuf_USART1  = (data_buffer)BUF_DEFAULT;
      USART1_enter_DefaultMode_from_RESET();
  }
  else if (dutNum == DUT_B){
    rxBuf_USART3  = (data_buffer)BUF_DEFAULT;
      USART3_enter_DefaultMode_from_RESET();
  }
  else if (dutNum == DUT_C){
    rxBuf_USART2  = (data_buffer)BUF_DEFAULT;
      USART2_enter_DefaultMode_from_RESET();
  }
  else if (dutNum == DUT_D){
    rxBuf_USART1  = (data_buffer)BUF_DEFAULT;
    USART1_enter_DefaultMode_from_RESET();
  }
}

uint8_t DUTS_getChar(DUTNUM_TypeDef dutNum)
{
  uint8_t ch;

  data_buffer *rxBuf;

  if (dutNum == DUT_A)
      rxBuf = &rxBuf_USART0;
  else if (dutNum == DUT_B)
      rxBuf = &rxBuf_USART1;
  else if (dutNum == DUT_C)
      rxBuf = &rxBuf_USART3;
  else if (dutNum == DUT_D)
      rxBuf = &rxBuf_USART2;
  else if (dutNum == DUT_CONTROL)
      rxBuf = &rxBuf_USART4;

  /* Check if there is a byte that is ready to be fetched. If no byte is ready, wait for incoming data */
  if (rxBuf->pendingBytes < 1)
  {
    return 0;
  }

  /* Copy data from buffer */
  ch        = rxBuf->data[rxBuf->rdI];
  rxBuf->rdI = (rxBuf->rdI + 1) % BUFFERSIZE;

  /* Decrement pending byte counter */
  rxBuf->pendingBytes--;

  rxBuf->overflow = false;

  return ch;
}

/******************************************************************************
 * @brief  uart1PutChar function
 *****************************************************************************/
void DUTS_PutChar(uint8_t ch, DUTNUM_TypeDef dutNum)
{

  data_buffer *txBuf;

  if (dutNum == DUT_A)
      txBuf = &txBuf_USART1;
  else if (dutNum == DUT_B)
      txBuf = &txBuf_USART3;
  else if (dutNum == DUT_C)
      txBuf = &txBuf_USART2;
  else if (dutNum == DUT_D)
      txBuf = &txBuf_USART0;

  /* Check if Tx queue has room for new data */
  while ((txBuf->pendingBytes + 1) > BUFFERSIZE)
  {
    /* Wait until there is room in queue */
	  EMU_EnterEM1();
  }

  /* Copy ch into txBuffer */
  txBuf->data[txBuf->wrI] = ch;
  txBuf->wrI             = (txBuf->wrI + 1) % BUFFERSIZE;

  /* Increment pending byte counter */
  txBuf->pendingBytes++;

  /* Enable interrupt on USART TX Buffer*/
  //USART_IntEnable(uart, USART_IF_TXBL);
}

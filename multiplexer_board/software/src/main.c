#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_prs.h"
#include "em_system.h"
#include "em_timer.h"
#include "em_chip.h"


#define LED_PORT    gpioPortE
#define LED_PIN     13

/* Define PWM frequency value */
#define PWM_FREQ 1000

#define OUTPUT_PORT gpioPortA
#define OUTPUT_PIN 0
#define LOCATION TIMER_ROUTE_LOCATION_LOC0

/******************************************************************************
 * @brief Delay function
 *****************************************************************************/
void Delay(uint16_t milliseconds)
{
  /* Enable clock for TIMER0 */
  CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER0;

  /* Set prescaler to maximum */
  TIMER0->CTRL = (TIMER0->CTRL & ~_TIMER_CTRL_PRESC_MASK) |  TIMER_CTRL_PRESC_DIV1024;

  /* Clear TIMER0 counter value */
  TIMER0->CNT = 0;

  /* Start TIMER0 */
  TIMER0->CMD = TIMER_CMD_START;

  /* Wait until counter value is over the target ms threshold */
  /* One TIMER0 count is 1024 (prescaler)/HFRCO frequency */
  /* The 1ms interval is about (HFRCO value - 1) TIMER0 count */
#if defined(_EFM32_PEARL_FAMILY)
  /* For EFM32PG, the default HFRCO frequency is 19 MHz */
  while(TIMER0->CNT < 18*milliseconds){
#else
  /* For other families, the default HFRCO frequency is 14 MHz */
  while(TIMER0->CNT < 13*milliseconds){
#endif
   /* Do nothing, just wait */
  }

  /* Stop TIMER0 */
  TIMER0->CMD = TIMER_CMD_STOP;
}

/**************************************************************************//**
 * @brief TIMER0_IRQHandler
 * Interrupt Service Routine TIMER0 Interrupt Line
 *****************************************************************************/
void TIMER0_IRQHandler(void)
{
  uint32_t compareValue;

  /* Clear flag for TIMER0 overflow interrupt */
  TIMER_IntClear(TIMER0, TIMER_IF_OF);

  compareValue = TIMER_CaptureGet(TIMER0, 0);
  /* increment duty-cycle or reset if reached TOP value */
  if( compareValue == TIMER_TopGet(TIMER0))
    TIMER_CompareBufSet(TIMER0, 0, 0);
  else
    TIMER_CompareBufSet(TIMER0, 0, ++compareValue);
}
/**************************************************************************//**
 * @brief  Main function
 * Main is called from __iar_program_start, see assembly startup file
 *****************************************************************************/
int main(void)
{
  /* Initialize chip */
  CHIP_Init();

  /* Enable clock for GPIO module */
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Configure LED_PORT pin LED_PIN (User LED) as push/pull outputs */
  GPIO_PinModeSet(LED_PORT,         /* Port */
				  LED_PIN,          /* Pin */
				  gpioModePushPull, /* Mode */
				  0 );              /* Output value */

  /* Infinite loop */
  while (1) {
	  /* Set LSB of count value on LED */
	  GPIO_PinOutToggle(LED_PORT, LED_PIN);
	  Delay(100);
  }

  /* Enable clock for TIMER0 module */
//  CMU_ClockEnable(cmuClock_TIMER0, true);
//
//  /* Set CC0 pin as output */
//  GPIO_PinModeSet(OUTPUT_PORT, OUTPUT_PIN, gpioModePushPull, 0);
//
//  /* Select CC channel parameters */
//  TIMER_InitCC_TypeDef timerCCInit =
//  {
//    .eventCtrl  = timerEventEveryEdge,
//    .edge       = timerEdgeBoth,
//    .prsSel     = timerPRSSELCh0,
//    .cufoa      = timerOutputActionNone,
//    .cofoa      = timerOutputActionNone,
//    .cmoa       = timerOutputActionToggle,
//    .mode       = timerCCModePWM,
//    .filter     = false,
//    .prsInput   = false,
//    .coist      = false,
//    .outInvert  = false,
//  };
//
//  /* Configure CC channel 0 */
//  TIMER_InitCC(TIMER0, 0, &timerCCInit);
//
//
//    /* Route CC0 to location and enable pin */
//    TIMER0->ROUTE |= (TIMER_ROUTE_CC0PEN | LOCATION);
//
//
//  /* Set Top Value */
//  TIMER_TopSet(TIMER0, CMU_ClockFreqGet(cmuClock_HFPER)/PWM_FREQ);
//
//  /* Set compare value starting at 0 - it will be incremented in the interrupt handler */
//  TIMER_CompareBufSet(TIMER0, 0, 0);
//
//  /* Select timer parameters */
//  TIMER_Init_TypeDef timerInit =
//  {
//    .enable     = true,
//    .debugRun   = true,
//    .prescale   = timerPrescale64,
//    .clkSel     = timerClkSelHFPerClk,
//    .fallAction = timerInputActionNone,
//    .riseAction = timerInputActionNone,
//    .mode       = timerModeUp,
//    .dmaClrAct  = false,
//    .quadModeX4 = false,
//    .oneShot    = false,
//    .sync       = false,
//  };
//
//  /* Enable overflow interrupt */
//  TIMER_IntEnable(TIMER0, TIMER_IF_OF);
//
//  /* Enable TIMER0 interrupt vector in NVIC */
//  NVIC_EnableIRQ(TIMER0_IRQn);
//
//  /* Configure timer */
//  TIMER_Init(TIMER0, &timerInit);
//
//  while(1)
//  {
//    /* Go to EM1 */
//    __WFI();
//  }

}

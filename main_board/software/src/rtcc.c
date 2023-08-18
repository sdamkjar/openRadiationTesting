#include <stdio.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_rtcc.h"

#define START_TIME      0x00235945      /* 23:59:45 */
#define START_DATE      0x06160228      /* 2016 Feb 28 */

uint32_t rtccFlag;

/**************************************************************************//**
* @brief RTCC Interrupt handler
*****************************************************************************/
void RTCC_IRQHandler(void)
{
  /* Read and clear interrupt source */
  rtccFlag = RTCC->IFC;

  /* Toggle GPIO pin for LCD display. */
  //GPIO_PinOutToggle((GPIO_Port_TypeDef)LCD_PORT_EXTCOMIN, LCD_PIN_EXTCOMIN );
}

/**************************************************************************//**
* @brief Setup RTCC for calendar.
*****************************************************************************/
void RTCC_Setup(void)
{
  RTCC_Init_TypeDef rtccInit = RTCC_INIT_DEFAULT;

  /* In calendar mode, the pre-counter should be configured to give ticks with a period of   */
  /* one second, i.e. RTCC_CTRL_CNTTICK should be set to PRESC, and the CNTPRESC bitfield    */
  /* of the RTCC_CTRL register should be set to DIV32768 if a 32768 Hz clock source is used. */
  rtccInit.enable   = false;
  rtccInit.presc = rtccCntPresc_32768;
  rtccInit.cntMode = rtccCntModeCalendar;
  RTCC_Init(&rtccInit);

  /* Initialize date and time */
  RTCC_DateSet(START_DATE);
  RTCC_TimeSet(START_TIME);
    
  /* Enable required interrupt */
  RTCC_IntEnable(RTCC_IEN_CNTTICK + RTCC_IEN_DAYTICK);

  /* Enable RTCC interrupt */
  NVIC_ClearPendingIRQ(RTCC_IRQn);
  NVIC_EnableIRQ(RTCC_IRQn);

  /* Start Counter */
  RTCC_Enable(true);
}
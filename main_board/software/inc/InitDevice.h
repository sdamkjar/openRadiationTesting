/*
 * InitDevice.h
 *
 *  Created on: May 20, 2018
 *      Author: sdamk
 */

#ifndef INC_INITDEVICE_H_
#define INC_INITDEVICE_H_

// USER CONSTANTS
// USER PROTOTYPES

// Mode Transition Prototypes
extern void enter_DefaultMode_from_RESET(void);
// Mode Transition Prototypes

// Config(Per-Module Mode)Transition Prototypes
extern void HFXO_enter_DefaultMode_from_RESET(void);
extern void LFXO_enter_DefaultMode_from_RESET(void);
extern void CMU_enter_DefaultMode_from_RESET(void);
extern void ADC0_enter_DefaultMode_from_RESET(void);
extern void ACMP0_enter_DefaultMode_from_RESET(void);
extern void ACMP1_enter_DefaultMode_from_RESET(void);
extern void DAC0_enter_DefaultMode_from_RESET(void);
extern void BURTC_enter_DefaultMode_from_RESET(void);
extern void RTC_enter_DefaultMode_from_RESET(void);
extern void OPAMP0_enter_DefaultMode_from_RESET(void);
extern void OPAMP1_enter_DefaultMode_from_RESET(void);
extern void OPAMP2_enter_DefaultMode_from_RESET(void);
extern void USART0_enter_DefaultMode_from_RESET(void);
extern void USART1_enter_DefaultMode_from_RESET(void);
extern void USART2_enter_DefaultMode_from_RESET(void);
extern void USART3_enter_DefaultMode_from_RESET(void);
extern void USART4_enter_DefaultMode_from_RESET(void);
extern void UART0_enter_DefaultMode_from_RESET(void);
extern void UART1_enter_DefaultMode_from_RESET(void);
extern void LEUART0_enter_DefaultMode_from_RESET(void);
extern void LEUART1_enter_DefaultMode_from_RESET(void);
extern void VCMP_enter_DefaultMode_from_RESET(void);
extern void WDOG_enter_DefaultMode_from_RESET(void);
extern void I2C0_enter_DefaultMode_from_RESET(void);
extern void I2C1_enter_DefaultMode_from_RESET(void);
extern void I2C2_enter_DefaultMode_from_RESET(void);
extern void TIMER0_enter_DefaultMode_from_RESET(void);
extern void TIMER1_enter_DefaultMode_from_RESET(void);
extern void TIMER2_enter_DefaultMode_from_RESET(void);
extern void TIMER3_enter_DefaultMode_from_RESET(void);
extern void LETIMER0_enter_DefaultMode_from_RESET(void);
extern void PCNT0_enter_DefaultMode_from_RESET(void);
extern void PCNT1_enter_DefaultMode_from_RESET(void);
extern void PCNT2_enter_DefaultMode_from_RESET(void);
extern void PRS_enter_DefaultMode_from_RESET(void);
extern void ETM_enter_DefaultMode_from_RESET(void);
extern void EBI_enter_DefaultMode_from_RESET(void);
extern void PORTIO_enter_DefaultMode_from_RESET(void);
// [Config(Per-Module Mode)Transition Prototypes]$


#endif /* INC_INITDEVICE_H_ */

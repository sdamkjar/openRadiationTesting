#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_chip.h"
#include "em_usart.h"


#define LED_PORT    gpioPortA
#define LED_PIN     15

#define USART0_RX_PIN       (6U)
#define USART0_RX_PORT      (gpioPortE)
#define USART0_RX_LOC       (1U)

#define USART0_TX_PIN       (7U)
#define USART0_TX_PORT      (gpioPortE)
#define USART0_TX_LOC       (1U)

#define DUT_ID_0 '7'
#define DUT_ID_1 'B'

#define MAX_RETRIES 10

#define BUFFER_SIZE 20
#define TEST_SIZE 120000

#define NVM_ADDRESS_START  0

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

void PRINT_Stringln(char* data) {
	unsigned int i = 0;
	USART_Tx(USART0,'\n');
	USART_Tx(USART0,'\t');
	USART_Tx(USART0,',');
	USART_Tx(USART0,DUT_ID_0);
	USART_Tx(USART0,DUT_ID_1);
	USART_Tx(USART0,',');
	do {
		USART_Tx(USART0,data[i]);
	} while(data[i++]!='\0');
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

void initUART(void) {

  // $[UART_InitAsync]
  USART_InitAsync_TypeDef initasync = USART_INITASYNC_DEFAULT;

  initasync.baudrate = 250000;
  initasync.databits = usartDatabits8;
  initasync.parity = usartNoParity;
  initasync.stopbits = usartStopbits1;
  initasync.oversampling = usartOVS16;
#if defined( USART_INPUT_RXPRS ) && defined( USART_CTRL_MVDIS )
  initasync.mvdis = 0;
  initasync.prsRxEnable = 0;
  initasync.prsRxCh = 0;
#endif

  USART_InitAsync(USART0, &initasync);
  // [UART_InitAsync]$

  // $[USART_InitPrsTrigger]
  USART_PrsTriggerInit_TypeDef initprs = USART_INITPRSTRIGGER_DEFAULT;

  initprs.rxTriggerEnable = 0;
  initprs.txTriggerEnable = 0;
  initprs.prsTriggerChannel = usartPrsTriggerCh0;

  USART_InitPrsTrigger(USART0, &initprs);
  // [USART_InitPrsTrigger]$

  GPIO_PinModeSet(USART0_TX_PORT, USART0_TX_PIN, gpioModePushPull, 1);
  GPIO_PinModeSet(USART0_RX_PORT, USART0_RX_PIN, gpioModeInput, 0);

  USART0->ROUTEPEN = USART_ROUTEPEN_RXPEN  | USART_ROUTEPEN_TXPEN;

  USART0->ROUTELOC0 = ( USART0->ROUTELOC0 & ~( _USART_ROUTELOC0_TXLOC_MASK | _USART_ROUTELOC0_RXLOC_MASK ) ) |
  ( USART0_TX_LOC << _USART_ROUTELOC0_TXLOC_SHIFT ) | ( USART0_RX_LOC << _USART_ROUTELOC0_RXLOC_SHIFT );


}


int main(void)
{
  /* Chip errata */
  CHIP_Init();

  /* Using HFXO at 48MHz as high frequency clock, HFXO */
  CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);

  /* Enable clock for GPIO */
  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(cmuClock_USART0, true);

  initUART();

  GPIO_PinModeSet(LED_PORT,LED_PIN,gpioModePushPull,0 );

  /* Infinite loop */
  while (1) {
	GPIO_PinOutToggle(LED_PORT,LED_PIN);
	PRINT_Stringln("ram\0");

	RAM_test();

	PRINT_Stringln("nvm\0");

	crc = CRC_calc(NVM_ADDRESS_START,(((DEVINFO->MSIZE & _DEVINFO_MSIZE_FLASH_MASK) >> _DEVINFO_MSIZE_FLASH_SHIFT) << 10));

	sprintf(buffer,"CRC:%x\0",crc);
	PRINT_Stringln(buffer);

	sprintf(buffer,"end%u\0",iteration++);
	PRINT_Stringln(buffer);

  }

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

/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>

#include <gpio.h>
#include <usart.h>
#include <stdio.h>
#include <stdint.h>
#include <common_nvm.h>

#define USART                 (&AVR32_USART3)
#define USART_RX_PIN          AVR32_USART3_RXD_2_PIN
#define USART_RX_FUNCTION     AVR32_USART3_RXD_2_FUNCTION
#define USART_TX_PIN          AVR32_USART3_TXD_2_PIN
#define USART_TX_FUNCTION     AVR32_USART3_TXD_2_FUNCTION

#define TARGET_PBACLK_FREQ_HZ   BOARD_OSC0_HZ// PBA clock target frequency, in Hz

#define DUT_ID_0 '3'
#define DUT_ID_1 'A'

#define MAX_RETRIES 10

#define BUFFER_SIZE 20
#define TEST_SIZE 15000

#define NVM_ADDRESS_START AVR32_FLASH_ADDRESS
#define NVM_ADDRESS_END   AVR32_FLASH_ADDRESS+AVR32_FLASH_SIZE

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
	usart_putchar(USART,'\n');
	usart_putchar(USART,'\t');
	usart_putchar(USART,',');
	usart_putchar(USART,DUT_ID_0);
	usart_putchar(USART,DUT_ID_1);
	usart_putchar(USART,',');
	do {
		usart_putchar(USART,data[i]);
	} while(data[i++]!='\0');
}

word CRC_calc(word start, word end)
{
	word crc = 0x0;
	word  address;
	
	uint8_t tmp = 0;

	for (address = end; address > start; address--)
	{
		crc  = (crc >> 8) | (crc << 8);
		nvm_read_char(INT_FLASH, start++, &tmp);
		crc ^= tmp;
		crc ^= (crc & 0xff) >> 4;
		crc ^= crc << 12;
		crc ^= (crc & 0xff) << 5;
	}
	return crc;
}

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();

	board_init();
	
	static const gpio_map_t USART_GPIO_MAP =
	{
		{USART_RX_PIN, USART_RX_FUNCTION},
		{USART_TX_PIN, USART_TX_FUNCTION}
	};
	
	// USART options.
	static const usart_options_t USART_OPTIONS =
	{
		.baudrate     = 250000,
		.charlength   = 8,
		.paritytype   = USART_NO_PARITY,
		.stopbits     = USART_1_STOPBIT,
		.channelmode  = USART_NORMAL_CHMODE
	};
	
	// Assign GPIO to USART.
	gpio_enable_module(USART_GPIO_MAP,
	sizeof(USART_GPIO_MAP) / sizeof(USART_GPIO_MAP[0]));
	
	// Initialize USART in RS232 mode.
	usart_init_rs232(USART, &USART_OPTIONS, TARGET_PBACLK_FREQ_HZ);
	
	gpio_set_pin_high(AVR32_PIN_PA08);
	
	PRINT_Stringln("boot\0");

	/* Insert application code here, after the board has been initialized. */
	
	AVR32_GPIO.port[0].oders = 1 << (8 & 0x1F); // The GPIO output driver is enabled for that pin.
	AVR32_GPIO.port[0].gpers = 1 << (8 & 0x1F); // The GPIO module controls that pin.

	gpio_set_pin_high(AVR32_PIN_PA08);

	while (1) {
		gpio_toggle_pin(AVR32_PIN_PA08);
		
		PRINT_Stringln("ram\0");
		
		RAM_test();
		
		PRINT_Stringln("nvm\0");
		
		crc = CRC_calc(NVM_ADDRESS_START,NVM_ADDRESS_END);
		
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



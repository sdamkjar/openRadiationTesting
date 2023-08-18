#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_i2c.h"
#include "em_chip.h"
#include "em_rtcc.h"
#include "InitDevice.h"
#include "em_usart.h"
#include "em_leuart.h"

#include "i2c.h"
#include "servo.h"
#include "tca6408a.h"
#include "ina226.h"

#include "duts.h"

#include "print.h"

#include "hal-config.h"

// Default servo angle in degrees
#define DEFAULT_SERVO_ANGLE 90
// Period in msec of blinking LED
#define BLINK_PERIOD_MS 500
// Period in msec between advancing servo (changes servo speed)
#define SERVO_PERIOD_MS 50
// Period in msec between current measurements
#define CURR_PERIOD_MS	20
// Duration in msec of power cycle
#define RESET_DELAY_MS	2000
// Number of steps for fine stepper adjustment
#define FINE_STEP		10
// No-response timeout in msec
#define WD_TIMEOUT_MS   2000
// Number of over current samples before reset
#define CURR_COUNT_LIMIT 50
// Default maximum current in uA
#define DEFAULT_MAX_CURR 200000
// Maximum current for each device in uA
#define MAX_CURR_1A (30000)
#define MAX_CURR_1B (30000)
#define MAX_CURR_1C (30000)
#define MAX_CURR_1D (30000)
#define MAX_CURR_2A (50000)
#define MAX_CURR_2B (50000)
#define MAX_CURR_2C (50000)
#define MAX_CURR_2D (50000)
#define MAX_CURR_3A (100000)
#define MAX_CURR_3B (100000)
#define MAX_CURR_3C (100000)
#define MAX_CURR_3D (100000)
#define MAX_CURR_4A (130000)
#define MAX_CURR_4B (130000)
#define MAX_CURR_4C (130000)
#define MAX_CURR_4D (130000)
#define MAX_CURR_5A (30000)
#define MAX_CURR_5B (50000)
#define MAX_CURR_5C (100000)
#define MAX_CURR_5D (130000)
#define MAX_CURR_6A (1000000)
#define MAX_CURR_6B (1000000)
#define MAX_CURR_6C (1000000)
#define MAX_CURR_6D (1000000)

/* Counts 1ms timeTicks */
volatile uint32_t msTicks = 0;

void Delay(uint32_t dlyTicks)
{
  uint32_t curTicks;
 
  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks){
    __WFI();
  }
}

void SysTick_Handler(void)
{
  /* Increment counter necessary in Delay()*/
  msTicks++;
}


int main(void)
{
  /* Chip errata */
  CHIP_Init();

  enter_DefaultMode_from_RESET();

  SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000);

  I2C_enableINT(I2C2);

  uint8_t needResetA = 0;
  uint8_t needResetC = 0;
  uint8_t needResetB = 0;
  uint8_t needResetD = 0;

  uint8_t useWatchdog = 1;

  uint8_t useOverCurr = 1;

  uint8_t val = 0;

  uint8_t servoDir = 0;

  uint16_t servoAngle = DEFAULT_SERVO_ANGLE;

  uint16_t x = 0;

  char buffer[20] = {0};

  int currThresholdA = DEFAULT_MAX_CURR;
  int currThresholdB = DEFAULT_MAX_CURR;
  int currThresholdC = DEFAULT_MAX_CURR;
  int currThresholdD = DEFAULT_MAX_CURR;
  uint8_t currOverCountA = 0;
  uint8_t currOverCountB = 0;
  uint8_t currOverCountC = 0;
  uint8_t currOverCountD = 0;

  uint16_t servoAngleTarget = DEFAULT_SERVO_ANGLE;

  uint32_t blinkTime = 0;
  uint32_t servoTime = 0;
  uint32_t currTime = 0;
  uint32_t resetTimeA = 0;
  uint32_t resetTimeB = 0;
  uint32_t resetTimeC = 0;
  uint32_t resetTimeD = 0;
  uint32_t watchDogTimeA = 0;
  uint32_t watchDogTimeB = 0;
  uint32_t watchDogTimeC = 0;
  uint32_t watchDogTimeD = 0;

  int currValueA = 0;
  int currValueB = 0;
  int currValueC = 0;
  int currValueD = 0;





  DUTS_initIRQs_USART(USART0,USART0_RX_IRQn);
  DUTS_initIRQs_USART(USART1,USART1_RX_IRQn);
  DUTS_initIRQs_USART(USART2,USART2_RX_IRQn);
  DUTS_initIRQs_USART(USART3,USART3_RX_IRQn);
  DUTS_initIRQs_USART(USART4,USART4_RX_IRQn);

  TCA6508A_PortModeSet(I2C2,TCA6408A_ADDR1,0x00); // Set all pins as outputs

  //PRINT_time(USART4, msTicks);
  //PRINT_Stringln(USART4, "System initialized!");

  PRINT_Stringln(UART0, "Hello1");
  PRINT_Stringln(UART1, "Hello2");
  PRINT_StringlnLE(LEUART0, "Hello3");
  PRINT_StringlnLE(LEUART1, "Hello4");

  SERVO_SetAngle(I2C2,SERVO_ADDRESS,servoAngle);

  while(1){

	val = DUTS_getChar(DUT_C);
	if (val == '\t') {
		PRINT_timeLE(LEUART1,msTicks);
		watchDogTimeA = msTicks;
	}
	else if( val != 0 ) LEUART_Tx(LEUART1,val);

	val = DUTS_getChar(DUT_D);
	if (val == '\t') {
		PRINT_time(UART0,msTicks);
		watchDogTimeB = msTicks;
	}
	else if( val != 0 ) USART_Tx(UART0,val);

	val = DUTS_getChar(DUT_A);
	if (val == '\t') {
		PRINT_timeLE(LEUART0,msTicks);
		watchDogTimeC = msTicks;
	}
	else if( val != 0 ) LEUART_Tx(LEUART0,val);

	val = DUTS_getChar(DUT_B);
	if (val == '\t') {
		PRINT_time(UART1,msTicks);
		watchDogTimeD = msTicks;
	}
	else if( val != 0 ) USART_Tx(UART1,val);

	val = DUTS_getChar(DUT_CONTROL);
	if (val == '1'){
		PRINT_time(USART4, msTicks);
		PRINT_Stringln(USART4, "Selected stage 1.");
		TCA6508A_PortModeSet(I2C2,TCA6408A_ADDR1,0x00); // Set all pins as outputs
		TCA6408A_PortOutSetVal(I2C2,TCA6408A_ADDR1,0x01);
		currThresholdA = MAX_CURR_1A;
		currThresholdB = MAX_CURR_1B;
		currThresholdC = MAX_CURR_1C;
		currThresholdD = MAX_CURR_1D;
	}
	else if (val == '2'){
		PRINT_time(USART4, msTicks);
		PRINT_Stringln(USART4, "Selected stage 2.");
		TCA6508A_PortModeSet(I2C2,TCA6408A_ADDR1,0x00); // Set all pins as outputs
		TCA6408A_PortOutSetVal(I2C2,TCA6408A_ADDR1,0x02);
		currThresholdA = MAX_CURR_2A;
		currThresholdB = MAX_CURR_2B;
		currThresholdC = MAX_CURR_2C;
		currThresholdD = MAX_CURR_2D;
	}
	else if (val == '3'){
		PRINT_time(USART4, msTicks);
		PRINT_Stringln(USART4, "Selected stage 3.");
		TCA6508A_PortModeSet(I2C2,TCA6408A_ADDR1,0x00); // Set all pins as outputs
		TCA6408A_PortOutSetVal(I2C2,TCA6408A_ADDR1,0x03);
		currThresholdA = MAX_CURR_3A;
		currThresholdB = MAX_CURR_3B;
		currThresholdC = MAX_CURR_3C;
		currThresholdD = MAX_CURR_3D;
	}
	else if (val == '4'){
		PRINT_time(USART4, msTicks);
		PRINT_Stringln(USART4, "Selected stage 4.");
		TCA6508A_PortModeSet(I2C2,TCA6408A_ADDR1,0x00); // Set all pins as outputs
		TCA6408A_PortOutSetVal(I2C2,TCA6408A_ADDR1,0x04);
		currThresholdA = MAX_CURR_4A;
		currThresholdB = MAX_CURR_4B;
		currThresholdC = MAX_CURR_4C;
		currThresholdD = MAX_CURR_4D;
	}
	else if (val == '5'){
		PRINT_time(USART4, msTicks);
		PRINT_Stringln(USART4, "Selected stage 5.");
		TCA6508A_PortModeSet(I2C2,TCA6408A_ADDR1,0x00); // Set all pins as outputs
		TCA6408A_PortOutSetVal(I2C2,TCA6408A_ADDR1,0x05);
		currThresholdA = MAX_CURR_5A;
		currThresholdB = MAX_CURR_5B;
		currThresholdC = MAX_CURR_5C;
		currThresholdD = MAX_CURR_5D;
	}
	else if (val == '6'){
		PRINT_time(USART4, msTicks);
		PRINT_Stringln(USART4, "Selected stage 6.");
		TCA6508A_PortModeSet(I2C2,TCA6408A_ADDR1,0x00); // Set all pins as outputs
		TCA6408A_PortOutSetVal(I2C2,TCA6408A_ADDR1,0x06);
		currThresholdA = MAX_CURR_6A;
		currThresholdB = MAX_CURR_6B;
		currThresholdC = MAX_CURR_6C;
		currThresholdD = MAX_CURR_6D;
    }
    else if (val == ']'){
    	PRINT_time(USART4, msTicks);
    	PRINT_Stringln(USART4, "Rotating clockwise.");
    	GPIO_PinOutClear(PORTIO_STP_EN_PORT,PORTIO_STP_EN_PIN);
    	GPIO_PinOutClear(PORTIO_STP_DIR_PORT,PORTIO_STP_DIR_PIN);
    	GPIO_PinOutSet(PORTIO_STP_MS1_PORT,PORTIO_STP_MS1_PIN);
		GPIO_PinOutSet(PORTIO_STP_MS2_PORT,PORTIO_STP_MS2_PIN);
		for(x=1;x<2000;x++){
			GPIO_PinOutSet(PORTIO_STP_STEP_PORT,PORTIO_STP_STEP_PIN);
			Delay(1);
			GPIO_PinOutClear(PORTIO_STP_STEP_PORT,PORTIO_STP_STEP_PIN);
			Delay(1);
		}
    }
    else if (val == '}'){
    	PRINT_time(USART4, msTicks);
    	PRINT_Stringln(USART4, "Small step clockwise.");
    	GPIO_PinOutClear(PORTIO_STP_EN_PORT,PORTIO_STP_EN_PIN);
    	GPIO_PinOutClear(PORTIO_STP_DIR_PORT,PORTIO_STP_DIR_PIN);
    	GPIO_PinOutSet(PORTIO_STP_MS1_PORT,PORTIO_STP_MS1_PIN);
		GPIO_PinOutSet(PORTIO_STP_MS2_PORT,PORTIO_STP_MS2_PIN);
		for(x=1;x<FINE_STEP;x++){
			GPIO_PinOutSet(PORTIO_STP_STEP_PORT,PORTIO_STP_STEP_PIN);
			Delay(1);
			GPIO_PinOutClear(PORTIO_STP_STEP_PORT,PORTIO_STP_STEP_PIN);
			Delay(1);
		}
    }
    else if (val == '['){
    	PRINT_time(USART4, msTicks);
    	PRINT_Stringln(USART4, "Rotating counter-clockwise.");
		GPIO_PinOutClear(PORTIO_STP_EN_PORT,PORTIO_STP_EN_PIN);
		GPIO_PinOutSet(PORTIO_STP_DIR_PORT,PORTIO_STP_DIR_PIN);
		GPIO_PinOutSet(PORTIO_STP_MS1_PORT,PORTIO_STP_MS1_PIN);
		GPIO_PinOutSet(PORTIO_STP_MS2_PORT,PORTIO_STP_MS2_PIN);
		for(x=1;x<2000;x++){
			GPIO_PinOutSet(PORTIO_STP_STEP_PORT,PORTIO_STP_STEP_PIN);
			Delay(1);
			GPIO_PinOutClear(PORTIO_STP_STEP_PORT,PORTIO_STP_STEP_PIN);
			Delay(1);
		}
    }
    else if (val == '{'){
    	PRINT_time(USART4, msTicks);
    	PRINT_Stringln(USART4, "Small step counter-clockwise.");
		GPIO_PinOutClear(PORTIO_STP_EN_PORT,PORTIO_STP_EN_PIN);
		GPIO_PinOutSet(PORTIO_STP_DIR_PORT,PORTIO_STP_DIR_PIN);
		GPIO_PinOutSet(PORTIO_STP_MS1_PORT,PORTIO_STP_MS1_PIN);
		GPIO_PinOutSet(PORTIO_STP_MS2_PORT,PORTIO_STP_MS2_PIN);
		for(x=1;x<FINE_STEP;x++){
			GPIO_PinOutSet(PORTIO_STP_STEP_PORT,PORTIO_STP_STEP_PIN);
			Delay(1);
			GPIO_PinOutClear(PORTIO_STP_STEP_PORT,PORTIO_STP_STEP_PIN);
			Delay(1);
		}
    }
    else if (val == '9'){
    	PRINT_time(USART4, msTicks);
    	PRINT_Stringln(USART4, "Motor disengaged.");
		GPIO_PinOutClear(PORTIO_STP_STEP_PORT,PORTIO_STP_STEP_PIN);
		GPIO_PinOutClear(PORTIO_STP_DIR_PORT,PORTIO_STP_DIR_PIN);
		GPIO_PinOutClear(PORTIO_STP_MS1_PORT,PORTIO_STP_MS1_PIN);
		GPIO_PinOutClear(PORTIO_STP_MS2_PORT,PORTIO_STP_MS2_PIN);
		GPIO_PinOutSet(PORTIO_STP_EN_PORT,PORTIO_STP_EN_PIN);
    }
    else if (val == '0'){
    	PRINT_time(USART4, msTicks);
    	PRINT_Stringln(USART4, "All stages off.");
    	TCA6408A_PortOutSetVal(I2C2,TCA6408A_ADDR1,0x78);
    }
    else if (val == 'a'){
    	PRINT_time(USART4, msTicks);
    	PRINT_Stringln(USART4, "Manually cycle A.");
    	TCA6408A_PinOutSet(I2C2,TCA6408A_ADDR1,3);
    	needResetA = 1;
    	resetTimeA = msTicks;
    }
    else if (val == 'b'){
    	PRINT_time(USART4, msTicks);
    	PRINT_Stringln(USART4, "Manually cycle B.");
    	TCA6408A_PinOutSet(I2C2,TCA6408A_ADDR1,4);
    	needResetB = 1;
    	resetTimeB = msTicks;
    }
    else if (val == 'c'){
    	PRINT_time(USART4, msTicks);
    	PRINT_Stringln(USART4, "Manually cycle C.");
    	TCA6408A_PinOutSet(I2C2,TCA6408A_ADDR1,5);
    	needResetC = 1;
    	resetTimeC = msTicks;
    }
    else if (val == 'd'){
    	PRINT_time(USART4, msTicks);
    	PRINT_Stringln(USART4, "Manually cycle D.");
    	TCA6408A_PinOutSet(I2C2,TCA6408A_ADDR1,6);
    	needResetD = 1;
    	resetTimeD = msTicks;
    }
    else if (val == '/'){
		PRINT_time(USART4, msTicks);
		PRINT_Stringln(USART4, "Manually cycle all.");
		TCA6408A_PinOutSet(I2C2,TCA6408A_ADDR1,3);
		TCA6408A_PinOutSet(I2C2,TCA6408A_ADDR1,4);
		TCA6408A_PinOutSet(I2C2,TCA6408A_ADDR1,5);
		TCA6408A_PinOutSet(I2C2,TCA6408A_ADDR1,6);
		needResetA = 1;
		needResetB = 1;
		needResetC = 1;
		needResetD = 1;
		resetTimeA = msTicks;
		resetTimeB = msTicks;
		resetTimeC = msTicks;
		resetTimeD = msTicks;
	}
    else if (val == 'A'){
    	PRINT_time(USART4, msTicks);
    	PRINT_Stringln(USART4, "Manually toggle A.");
    	TCA6408A_PinOutToggle(I2C2,TCA6408A_ADDR1,3);
    }
    else if (val == 'B'){
    	PRINT_time(USART4, msTicks);
    	PRINT_Stringln(USART4, "Manually toggle B.");
    	TCA6408A_PinOutToggle(I2C2,TCA6408A_ADDR1,4);
    }
    else if (val == 'C'){
    	PRINT_time(USART4, msTicks);
    	PRINT_Stringln(USART4, "Manually toggle C.");
    	TCA6408A_PinOutToggle(I2C2,TCA6408A_ADDR1,5);
    }
    else if (val == 'D'){
    	PRINT_time(USART4, msTicks);
    	PRINT_Stringln(USART4, "Manually toggle D.");
    	TCA6408A_PinOutToggle(I2C2,TCA6408A_ADDR1,6);
    }
    else if (val == '?'){
    	PRINT_time(USART4, msTicks);
    	PRINT_Stringln(USART4, "Manually toggle all.");
    	TCA6408A_PinOutToggle(I2C2,TCA6408A_ADDR1,3);
    	TCA6408A_PinOutToggle(I2C2,TCA6408A_ADDR1,4);
    	TCA6408A_PinOutToggle(I2C2,TCA6408A_ADDR1,5);
    	TCA6408A_PinOutToggle(I2C2,TCA6408A_ADDR1,6);
    }
    else if (val == 'w'){
		PRINT_time(USART4, msTicks);
		if(useWatchdog == 0){
			PRINT_Stringln(USART4, "Watchdog Enabled.");
			useWatchdog = 1;
		}
		else if(useWatchdog == 1){
			PRINT_Stringln(USART4, "Watchdog Disabled.");
			useWatchdog = 0;
		}
	}
    else if (val == 'q'){
		PRINT_time(USART4, msTicks);
		if(useOverCurr == 0){
			PRINT_Stringln(USART4, "Overcurrent Enabled.");
			useOverCurr = 1;
		}
		else if(useOverCurr == 1){
			PRINT_Stringln(USART4, "Overcurrent Disabled.");
			useOverCurr = 0;
		}
	}
    else if (val == '-'){
		servoAngleTarget-=15;
		PRINT_time(USART4, msTicks);
		sprintf(buffer,"Servo to %d\0",servoAngleTarget);
		PRINT_Stringln(USART4, buffer);
	}
    else if (val == '='){
		servoAngleTarget+=15;
		PRINT_time(USART4, msTicks);
		sprintf(buffer,"Servo to %d\0",servoAngleTarget);
		PRINT_Stringln(USART4, buffer);
	}
    val = 0;

    if(msTicks - resetTimeA > RESET_DELAY_MS && needResetA){
    	PRINT_time(USART4, msTicks);
    	PRINT_Stringln(USART4, "Turn on A.");
    	watchDogTimeA = msTicks;
    	TCA6408A_PinOutClear(I2C2,TCA6408A_ADDR1,3);
    	needResetA = 0;
    }

    if(msTicks - resetTimeB > RESET_DELAY_MS && needResetB){
    	PRINT_time(USART4, msTicks);
    	PRINT_Stringln(USART4, "Turn on B.");
    	watchDogTimeB = msTicks;
    	TCA6408A_PinOutClear(I2C2,TCA6408A_ADDR1,4);
        needResetB = 0;
    }

    if(msTicks - resetTimeC > RESET_DELAY_MS && needResetC){
    	PRINT_time(USART4, msTicks);
    	PRINT_Stringln(USART4, "Turn on C.");
    	watchDogTimeC = msTicks;
    	TCA6408A_PinOutClear(I2C2,TCA6408A_ADDR1,5);
        needResetC = 0;
    }

    if(msTicks - resetTimeD > RESET_DELAY_MS && needResetD){
    	PRINT_time(USART4, msTicks);
    	PRINT_Stringln(USART4, "Turn on D.");
    	watchDogTimeD = msTicks;
    	TCA6408A_PinOutClear(I2C2,TCA6408A_ADDR1,6);
        needResetD = 0;
    }

    if(msTicks - blinkTime > BLINK_PERIOD_MS){
    	blinkTime = msTicks;
    	GPIO_PinOutToggle(PORTIO_LED_PORT,PORTIO_LED_PIN);
    	//PRINT_StringlnLE(LEUART1, "HelloA");
    	//PRINT_Stringln(UART0, "HelloB");
    	//PRINT_StringlnLE(LEUART0, "HelloC");
    	//PRINT_Stringln(UART1, "HelloD");

    }

    // Wiper code for testing
    if(msTicks - servoTime > SERVO_PERIOD_MS){
    	servoTime = msTicks;
    	if ( servoAngle < servoAngleTarget ){
    		servoAngle++;
    		SERVO_SetAngle(I2C2,SERVO_ADDRESS,servoAngle);
    	}
    	else if ( servoAngle > servoAngleTarget ){
    		servoAngle--;
    		SERVO_SetAngle(I2C2,SERVO_ADDRESS,servoAngle);
    	}
    }

    if(msTicks - currTime > CURR_PERIOD_MS){
    	currTime = msTicks;
        PRINT_time(USART4, msTicks);
        INA226_ReadShuntVoltage(I2C2,INA226_ADDR94,&currValueA);
        INA226_ReadShuntVoltage(I2C2,INA226_ADDR96,&currValueB);
        INA226_ReadShuntVoltage(I2C2,INA226_ADDR9C,&currValueC);
        INA226_ReadShuntVoltage(I2C2,INA226_ADDR9E,&currValueD);
        if(0x8000 & currValueA) {
        	currValueA|=0x7FFF;
        	currValueA*= -1;
        }
        if(0x8000 & currValueB) {
            currValueB|=0x7FFF;
            currValueB*= -1;
        }
        if(0x8000 & currValueC) {
            currValueC|=0x7FFF;
            currValueC*= -1;
        }
        if(0x8000 & currValueD) {
            currValueD|=0x7FFF;
            currValueD*= -1;
        }
        currValueA*=1000; 	//  currValue * 2.5uV/LSB * 1000mA/A / 30000 uOhmu = X/12 mA
        currValueB*=1000; 	//  currValue * 2.5uV/LSB * 1000mA/A / 30000 uOhmu = X/12 mA
        currValueC*=1000; 	//  currValue * 2.5uV/LSB * 1000mA/A / 30000 uOhmu = X/12 mA
        currValueD*=1000; 	//  currValue * 2.5uV/LSB * 1000mA/A / 30000 uOhmu = X/12 mA
        currValueA/=12; 	//  currValue * 2.5uV/LSB * 1000mA/A / 30000 uOhmu = X/12 mA
        currValueB/=12; 	//  currValue * 2.5uV/LSB * 1000mA/A / 30000 uOhmu = X/12 mA
        currValueC/=12; 	//  currValue * 2.5uV/LSB * 1000mA/A / 30000 uOhmu = X/12 mA
        currValueD/=12; 	//  currValue * 2.5uV/LSB * 1000mA/A / 30000 uOhmu = X/12 mA
        PRINT_current(USART4,currValueA);
        PRINT_current(USART4,currValueB);
        PRINT_current(USART4,currValueC);
        PRINT_current(USART4,currValueD);
        PRINT_Char(USART4,'\n');
        if(currValueA > currThresholdA) currOverCountA++;
        else currOverCountA = 0;
        if(currOverCountA > CURR_COUNT_LIMIT && useOverCurr){
        	currOverCountA = 0;
        	PRINT_time(USART4, msTicks);
        	PRINT_Stringln(USART4, "High current A.");
        	TCA6408A_PinOutSet(I2C2,TCA6408A_ADDR1,3);
        	needResetA = 1;
        	resetTimeA = msTicks;
        }
        if(currValueB > currThresholdB) currOverCountB++;
        else currOverCountB = 0;
        if(currOverCountB > CURR_COUNT_LIMIT && useOverCurr){
        	currOverCountB = 0;
        	PRINT_time(USART4, msTicks);
        	PRINT_Stringln(USART4, "High current B.");
        	TCA6408A_PinOutSet(I2C2,TCA6408A_ADDR1,4);
        	needResetB = 1;
        	resetTimeB = msTicks;
        }
        if(currValueC > currThresholdC) currOverCountC++;
        else currOverCountC = 0;
        if(currOverCountC > CURR_COUNT_LIMIT && useOverCurr){
        	currOverCountC = 0;
        	PRINT_time(USART4, msTicks);
        	PRINT_Stringln(USART4, "High current C.");
        	TCA6408A_PinOutSet(I2C2,TCA6408A_ADDR1,5);
        	needResetC = 1;
        	resetTimeC = msTicks;
        }
        if(currValueD > currThresholdD) currOverCountD++;
        else currOverCountD = 0;
        if(currOverCountD > CURR_COUNT_LIMIT && useOverCurr){
        	currOverCountD = 0;
        	PRINT_time(USART4, msTicks);
        	PRINT_Stringln(USART4, "High current D.");
        	TCA6408A_PinOutSet(I2C2,TCA6408A_ADDR1,6);
        	needResetD = 1;
        	resetTimeD = msTicks;
        }

    }


    if(useWatchdog){
		if(msTicks - watchDogTimeA > WD_TIMEOUT_MS && !needResetA){
			PRINT_time(USART4, msTicks);
			PRINT_Stringln(USART4, "Watchdog A.");
			TCA6408A_PinOutSet(I2C2,TCA6408A_ADDR1,3);
			needResetA = 1;
			resetTimeA = msTicks;
		}

		if(msTicks - watchDogTimeB > WD_TIMEOUT_MS && !needResetB){
			PRINT_time(USART4, msTicks);
			PRINT_Stringln(USART4, "Watchdog B.");
			TCA6408A_PinOutSet(I2C2,TCA6408A_ADDR1,4);
			needResetB = 1;
			resetTimeB = msTicks;
		}

		if(msTicks - watchDogTimeC > WD_TIMEOUT_MS && !needResetC){
			PRINT_time(USART4, msTicks);
			PRINT_Stringln(USART4, "Watchdog C.");
			TCA6408A_PinOutSet(I2C2,TCA6408A_ADDR1,5);
			needResetC = 1;
			resetTimeC = msTicks;
		}

		if(msTicks - watchDogTimeD > WD_TIMEOUT_MS && !needResetD){
			PRINT_time(USART4, msTicks);
			PRINT_Stringln(USART4, "Watchdog D.");
			TCA6408A_PinOutSet(I2C2,TCA6408A_ADDR1,6);
			needResetD = 1;
			resetTimeD = msTicks;
		}
    }



//	__WFI();
	
  }

}

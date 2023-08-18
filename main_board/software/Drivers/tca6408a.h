/*
 * tca6508a.h
 *
 *  Created on: May 28, 2018
 *      Author: sdamk
 */

#ifndef DRIVERS_TCA6408A_H_
#define DRIVERS_TCA6408A_H_		

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#define TCA6408A_ADDR0     (0x40)
#define TCA6408A_ADDR1     (0x42)

#define TCA6408A_INPUT_INPUT			(0xFFUL << 0)
#define _TCA6408A_INPUT_INPUT_SHIFT		0
#define _TCA6408A_INPUT_INPUT_MASK		0xFFUL
#define TCA6408A_OUTPUT_OUTPUT			(0xFFUL << 0)
#define _TCA6408A_OUTPUT_OUTPUT_SHIFT	0
#define _TCA6408A_OUTPUT_OUTPUT_MASK	0xFFUL
#define _TCA6408A_OUTPUT_OUTPUT_DEFUALT	0xFFUL
#define TCA6408A_OUTPUT_OUTPUT_DEFAULT	(_TCA6408A_OUTPUT_OUTPUT_DEFUALT << 0)
#define TCA6408A_POL_POL				(0xFFUL << 0)
#define _TCA6408A_POL_POL_SHIFT			0
#define _TCA6408A_POL_POL_MASK			0xFFUL
#define _TCA6408A_POL_POL_DEFUALT		0X00UL
#define TCA6408A_POL_POL_DEFAULT		(_TCA6408A_POL_POL_DEFUALT << 0)
#define TCA6408A_CONFIG_CONFIG			(0xFFUL << 0)
#define _TCA6408A_CONFIG_CONFIG_SHIFT	0
#define _TCA6408A_CONFIG_CONFIG_MASK	0xFFUL
#define _TCA6408A_CONFIG_CONFIG_DEFUALT	0xFFUL
#define TCA6408A_CONFIG_CONFIG_DEFAULT	(_TCA6408A_CONFIG_CONFIG_DEFUALT << 0)

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

 typedef enum
 {
 	TCA6408A_RegInput	=	0x00,	/**< Input port register (read-only) */
 	TCA6408A_RegOutput	=	0x01,	/**< Output port register */
 	TCA6408A_RegPol		=	0x02,	/**< Polarity inversion register */
 	TCA6408A_RegConfig	=	0x03	/**< Configuration register */
 } TCA6408A_Register_TypeDef;

typedef enum
{
	TCA6408A_ConfigOutput  = 0,
	TCA6408A_ConfigInput = 1	 /**< (default) */
} TCA6408A_Config_TypeDef;

typedef enum
{
	TCA6408A_PolNorm	=	0,	 	/**< (default) */
	TCA6408A_PolInv	=	1
} TCA6408A_Pol_TypeDef;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

int TCA6408A_RegisterSet(I2C_TypeDef *i2c,
                         uint8_t addr,
                         TCA6408A_Register_TypeDef reg,
                         uint8_t val);

int TCA6408A_RegisterGet(I2C_TypeDef *i2c,
                         uint8_t addr,
                         TCA6408A_Register_TypeDef reg,
                         uint8_t *val);

int TCA6408A_PinModeGet(I2C_TypeDef *i2c,
                       	uint8_t addr,
                       	uint8_t pin,
                       	uint8_t *val);

int TCA6408A_PinModeSet(I2C_TypeDef *i2c,
                       	uint8_t addr,
                       	uint8_t pin,
                       	uint8_t val);

int TCA6408A_PinInGet(I2C_TypeDef *i2c,
                       uint8_t addr,
                       uint8_t pin,
                       uint8_t *val);

int TCA6408A_PinOutGet(I2C_TypeDef *i2c,
                       uint8_t addr,
                       uint8_t pin,
                       uint8_t *val);

int TCA6408A_PinOutSet(I2C_TypeDef *i2c,
                       uint8_t addr,
                       uint8_t pin);

int TCA6408A_PinOutClear(I2C_TypeDef *i2c,
                       uint8_t addr,
                       uint8_t pin);

int TCA6408A_PinOutSetVal(I2C_TypeDef *i2c,
                       uint8_t addr,
                       uint8_t pin,
                       uint8_t val);

int TCA6408A_PinOutToggle(I2C_TypeDef *i2c,
                       uint8_t addr,
                       uint8_t pin);

int TCA6508A_PortModeGet(I2C_TypeDef *i2c,
                       uint8_t addr,
                       uint8_t *val);

int TCA6508A_PortModeSet(I2C_TypeDef *i2c,
                       uint8_t addr,
                       uint8_t val);

int TCA6508A_PortInGet(I2C_TypeDef *i2c,
                       uint8_t addr,
                       uint8_t *val);

int TCA6508A_PortOutGet(I2C_TypeDef *i2c,
                       uint8_t addr,
                       uint8_t *val);

int TCA6408A_PortOutSet(I2C_TypeDef *i2c,
                       uint8_t addr);

int TCA6408A_PortOutClear(I2C_TypeDef *i2c,
                       uint8_t addr);

int TCA6408A_PortOutSetVal(I2C_TypeDef *i2c,
                       uint8_t addr,
                       uint8_t val);

int TCA6408A_PortOutToggle(I2C_TypeDef *i2c,
                       uint8_t addr);

#endif /* DRIVERS_TCA6508A_H_ */

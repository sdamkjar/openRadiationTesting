/*
 * servo.c
 *
 *  Created on: June 26, 2018
 *      Author: sdamk
 */



#include "i2c.h"
#include "em_i2c.h"
#include "em_emu.h"
#include "servo.h"

#define MAX_RETRIES 1000

int SERVO_SetAngle(I2C_TypeDef *i2c,
                         uint8_t addr,
                         uint16_t val)
{
  I2C_TransferSeq_TypeDef seq;
  uint8_t data[2];

  val = (val*311)>>5;
  val = val + 1750;

  seq.addr = addr;
  seq.flags = I2C_FLAG_WRITE;

  data[0] = (uint8_t)(val >> 8);
  data[1] = (uint8_t)val;
  
  seq.buf[0].data = data;
  seq.buf[0].len = 2;

  I2C_setStatus(I2C2,I2C_TransferInit(i2c, &seq));

  unsigned int retries = 0;

  while (I2C_getStatus(i2c) == i2cTransferInProgress)
  {
    /* Enter EM1 while waiting for I2C interrupt */


    if (MAX_RETRIES < retries++) break;

    EMU_EnterEM1();
    /* Could do a timeout function here. */
  }
  
  return((int)I2C_getStatus(i2c));
}

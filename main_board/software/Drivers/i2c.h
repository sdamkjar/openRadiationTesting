/*
 * i2c.h
 *
 *  Created on: June 15, 2018
 *      Author: sdamk
 */

#ifndef DRIVERS_I2C_H_
#define DRIVERS_I2C_H_		

#include "em_i2c.h"

#define MAX_RETRIES 1000

__STATIC_INLINE void I2C_enableINT(I2C_TypeDef *i2c)
{  
  /* Support up to 2 I2C buses. */
  if (i2c == I2C0) {
    NVIC_ClearPendingIRQ(I2C0_IRQn);
    NVIC_EnableIRQ(I2C0_IRQn);
  }
#if (I2C_COUNT > 1)
  else if (i2c == I2C1) {
    NVIC_ClearPendingIRQ(I2C1_IRQn);
    NVIC_EnableIRQ(I2C1_IRQn);
  }
#endif
#if (I2C_COUNT > 2)
  else if (i2c == I2C2) {
    NVIC_ClearPendingIRQ(I2C2_IRQn);
    NVIC_EnableIRQ(I2C2_IRQn);
  }
#endif
}

I2C_TransferReturn_TypeDef I2C_getStatus(I2C_TypeDef *i2c);

void I2C_setStatus(I2C_TypeDef *i2c, I2C_TransferReturn_TypeDef transfer);

#endif /* DRIVERS_I2C_H_ */

/*
 * i2c.c
 *
 *  Created on: May 20, 2018
 *      Author: sdamk
 */

#include "i2c.h"
#include "em_i2c.h"
#include "em_assert.h"

/** Validation of the I2C register block pointer reference for assert statements. */
#if (I2C_COUNT == 1)
#define I2C_REF_VALID(ref)    ((ref) == I2C0)
#elif (I2C_COUNT == 2)
#define I2C_REF_VALID(ref)    (((ref) == I2C0) || ((ref) == I2C1))
#elif (I2C_COUNT == 3)
#define I2C_REF_VALID(ref)    (((ref) == I2C0) || ((ref) == I2C1) || ((ref) == I2C2))
#endif



/** A transfer state information for an ongoing master mode transfer. */
I2C_TransferReturn_TypeDef I2C_Status[I2C_COUNT];

void I2C0_IRQHandler(void)
{
  /* Just run the I2C_Transfer function that checks interrupts flags and returns */
  /* the appropriate status */
	I2C_Status[0] = I2C_Transfer(I2C0);
}
#if (I2C_COUNT > 1)
void I2C1_IRQHandler(void)
{
  /* Just run the I2C_Transfer function that checks interrupts flags and returns */
  /* the appropriate status */
	I2C_Status[1] = I2C_Transfer(I2C1);
}
#endif
#if (I2C_COUNT > 2)
void I2C2_IRQHandler(void)
{
  /* Just run the I2C_Transfer function that checks interrupts flags and returns */
  /* the appropriate status */
	I2C_Status[2] = I2C_Transfer(I2C2);
}
#endif

I2C_TransferReturn_TypeDef I2C_getStatus(I2C_TypeDef *i2c)
{

  I2C_TransferReturn_TypeDef transfer;

  EFM_ASSERT(I2C_REF_VALID(i2c));

  if (i2c == I2C0) {
    transfer = I2C_Status[0];
  }
#if (I2C_COUNT > 1)
  else if (i2c == I2C1) {
    transfer = I2C_Status[1];
  }
#endif
#if (I2C_COUNT > 2)
  else if (i2c == I2C2) {
    transfer = I2C_Status[2];
  }
#endif

  return transfer;
}

void I2C_setStatus(I2C_TypeDef *i2c, I2C_TransferReturn_TypeDef transfer)
{

  if (i2c == I2C0) {
	I2C_Status[0] = transfer;
  }
#if (I2C_COUNT > 1)
  else if (i2c == I2C1) {
	I2C_Status[1] = transfer;
  }
#endif
#if (I2C_COUNT > 2)
  else if (i2c == I2C2) {
	I2C_Status[2] = transfer;
  }
#endif
}

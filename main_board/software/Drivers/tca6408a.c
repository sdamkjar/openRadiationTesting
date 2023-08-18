/*
 * tca6408a.c
 *
 *  Created on: May 20, 2018
 *      Author: sdamk
 */

#include "i2c.h"
#include "em_i2c.h"
#include "em_emu.h"
#include "tca6408a.h"

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Set content of a register.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address, in 8 bit format, where LSB is reserved for R/W bit.
 *
 * @param[in] reg
 *   Register to write (input register cannot be written).
 *
 * @param[in] val
 *   Value used when writing to register.
 *
 * @return
 *   Returns 0 if register written, <0 if unable to write to register.
 ******************************************************************************/
int TCA6408A_RegisterSet(I2C_TypeDef *i2c,
                         uint8_t addr,
                         TCA6408A_Register_TypeDef reg,
                         uint8_t val)
{
  I2C_TransferSeq_TypeDef seq;
  uint8_t data[2];

  seq.addr = addr;
  seq.flags = I2C_FLAG_WRITE;

  data[0] = ((uint8_t)reg);
  data[1] = ((uint8_t)val);

  seq.buf[0].data = data;
  seq.buf[0].len = 2;

  I2C_setStatus(I2C2,I2C_TransferInit(i2c, &seq));

  unsigned int retries = 0;

  while (I2C_getStatus(i2c) == i2cTransferInProgress)
  {
    /* Enter EM1 while waiting for I2C interrupt */
    if(MAX_RETRIES < retries++)break;
    /* Enter EM1 while waiting for I2C interrupt */
    EMU_EnterEM1();
    /* Could do a timeout function here. */
  }

  return((int)I2C_getStatus(i2c));
}

/***************************************************************************//**
 * @brief
 *   Get current content of a register.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address, in 8 bit format, where LSB is reserved for R/W bit.
 *
 * @param[in] reg
 *   Register to read.
 *
 * @param[out] val
 *   Reference to place register read.
 *
 * @return
 *   Returns 0 if register read, <0 if unable to read register.
 ******************************************************************************/
int TCA6408A_RegisterGet(I2C_TypeDef *i2c,
                         uint8_t addr,
                         TCA6408A_Register_TypeDef reg,
                         uint8_t *val)
{
  I2C_TransferSeq_TypeDef seq;
  uint8_t regid[1];
  uint8_t data[1];

  seq.addr = addr;
  seq.flags = I2C_FLAG_WRITE_READ;

  /* Select register to be read */
  regid[0] = ((uint8_t)reg) & 0x3;
  seq.buf[0].data = regid;
  seq.buf[0].len = 1;

  seq.buf[1].data = data;
  seq.buf[1].len = 1;

  /* Do a polled transfer */
  I2C_setStatus(i2c,I2C_TransferInit(i2c, &seq));

  unsigned int retries = 0;

  while (I2C_getStatus(i2c) == i2cTransferInProgress)
  {
    /* Enter EM1 while waiting for I2C interrupt */
    if(MAX_RETRIES < retries++)break;
    /* Enter EM1 while waiting for I2C interrupt */
    EMU_EnterEM1();
    /* Could do a timeout function here. */
  }

  if (I2C_getStatus(i2c) != i2cTransferDone)
  {
    return((int)I2C_getStatus(i2c));
  }

  *val = (uint8_t)(data[0]);

  return((int)I2C_getStatus(i2c));
}

/***************************************************************************//**
 * @brief
 *   Get current mode (input or output) of a single pin in configuration
 *	 register.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address, in 8 bit format, where LSB is reserved for R/W bit.
 *
 * @param[in] pin
 *   Pin number (0 to 7).
 *
 * @param[out] val
 *   Reference to place pin mode value (0 -> Input, 1 -> Output).
 *
 * @return
 *   Returns 0 if register read, <0 if unable to read register.
 ******************************************************************************/
int TCA6408A_PinModeGet(I2C_TypeDef *i2c,
                       	uint8_t addr,
                       	uint8_t pin,
                       	uint8_t *val)
{
  int ret = -1;

  uint8_t tmp = 0;

  ret = TCA6408A_RegisterGet(i2c,addr,TCA6408A_RegConfig,&tmp);
  if (ret < 0)
  {
    return(ret);
  }

  *val = (tmp >> pin) & 0x1;

  return(ret);
}

/***************************************************************************//**
 * @brief
 *   Set mode (input or output) of a single pin in configuration register.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address, in 8 bit format, where LSB is reserved for R/W bit.
 *
 * @param[in] pin
 *   Pin number (0 to 7).
 *
 * @param[in] val
 *   Value of pin mode to set (0 -> Input, 1 -> Output).
 *
 * @return
 *   Returns 0 if register written, <0 if unable to write to register.
 ******************************************************************************/
int TCA6408A_PinModeSet(I2C_TypeDef *i2c,
                       	uint8_t addr,
                       	uint8_t pin,
                       	uint8_t val)
{
  int ret = -1;

  uint8_t tmp = 0;

  ret = TCA6408A_RegisterGet(i2c,addr,TCA6408A_RegConfig,&tmp);
  if (ret < 0)
  {
    return(ret);
  }

  tmp = (tmp & ~(0x1 << pin)) | (val << pin);

  ret = TCA6408A_RegisterSet(i2c,addr,TCA6408A_RegConfig,tmp);

  return(ret);
}

/***************************************************************************//**
 * @brief
 *   Read current value of a single pin in input port register.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address, in 8 bit format, where LSB is reserved for R/W bit.
 *
 * @param[in] pin
 *   Pin number (0 to 7).
 *
 * @param[out] val
 *   Reference to place pin value read.
 *
 * @return
 *   Returns 0 if register read, <0 if unable to read register.
 ******************************************************************************/
int TCA6408A_PinInGet(I2C_TypeDef *i2c,
                       uint8_t addr,
                       uint8_t pin,
                       uint8_t *val)
{
  int ret = -1;

  uint8_t tmp = 0;

  ret = TCA6408A_RegisterGet(i2c,addr,TCA6408A_RegInput,&tmp);
  if (ret < 0)
  {
    return(ret);
  }

  *val = (tmp >> pin) & 0x1;

  return(ret);
}

/***************************************************************************//**
 * @brief
 *   Get current value (high or low) of a single pin in output port register.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address, in 8 bit format, where LSB is reserved for R/W bit.
 *
 * @param[in] pin
 *   Pin number (0 to 7).
 *
 * @param[out] val
*   Reference to place pin value (high or low) read.
 *
 * @return
 *   Returns 0 if register read, <0 if unable to read register.
 ******************************************************************************/
int TCA6408A_PinOutGet(I2C_TypeDef *i2c,
                       uint8_t addr,
                       uint8_t pin,
                       uint8_t *val)
{
  int ret = -1;

  uint8_t tmp = 0;

  ret = TCA6408A_RegisterGet(i2c,addr,TCA6408A_RegOutput,&tmp);
  if (ret < 0)
  {
    return(ret);
  }

  *val = (tmp >> pin) & 0x1;

  return(ret);
}

/***************************************************************************//**
 * @brief
 *   Set value of a single pin in output port register to 1.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address, in 8 bit format, where LSB is reserved for R/W bit.
 *
 * @param[in] pin
 *   Pin number (0 to 7).
 *
 * @return
 *   Returns 0 if register written, <0 if unable to write to register.
 ******************************************************************************/
int TCA6408A_PinOutSet(I2C_TypeDef *i2c,
                       uint8_t addr,
                       uint8_t pin)
{
  int ret = -1;

  uint8_t tmp = 0;

  ret = TCA6408A_RegisterGet(i2c,addr,TCA6408A_RegOutput,&tmp);
  if (ret < 0)
  {
    return(ret);
  }

  tmp |= (0x1 << pin);

  ret = TCA6408A_RegisterSet(i2c,addr,TCA6408A_RegOutput,tmp);

  return(ret);
}

/***************************************************************************//**
 * @brief
 *   Set value of a single pin in output port register to 0.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address, in 8 bit format, where LSB is reserved for R/W bit.
 *
 * @param[in] pin
 *   Pin number (0 to 7).
 *
 * @return
 *   Returns 0 if register written, <0 if unable to write to register.
 ******************************************************************************/
int TCA6408A_PinOutClear(I2C_TypeDef *i2c,
                       uint8_t addr,
                       uint8_t pin)
{
  int ret = -1;

  uint8_t tmp = 0;

  ret = TCA6408A_RegisterGet(i2c,addr,TCA6408A_RegOutput,&tmp);
  if (ret < 0)
  {
    return(ret);
  }

  tmp &= ~(0x1 << pin);

  ret = TCA6408A_RegisterSet(i2c,addr,TCA6408A_RegOutput,tmp);

  return(ret);
}

/***************************************************************************//**
 * @brief
 *   Set value of a single pin in output port register.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address, in 8 bit format, where LSB is reserved for R/W bit.
 *
 * @param[in] pin
 *   Pin number (0 to 7).
 *
 * @param[in] val
 *   Value (high or low) to set.
 *
 * @return
 *   Returns 0 if register written, <0 if unable to write to register.
 ******************************************************************************/
int TCA6408A_PinOutSetVal(I2C_TypeDef *i2c,
                       uint8_t addr,
                       uint8_t pin,
                       uint8_t val)
{
  int ret = -1;

  uint8_t tmp = 0;

  ret = TCA6408A_RegisterGet(i2c,addr,TCA6408A_RegOutput,&tmp);
  if (ret < 0)
  {
    return(ret);
  }

  tmp = (tmp & ~(0x1 << pin)) | (val << pin);

  ret = TCA6408A_RegisterSet(i2c,addr,TCA6408A_RegOutput,tmp);

  return(ret);
}

/***************************************************************************//**
 * @brief
 *   Toggle a single pin in output port register.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address, in 8 bit format, where LSB is reserved for R/W bit.
 *
 * @param[in] pin
 *   Pin number (0 to 7).
 *
 * @return
 *   Returns 0 if register written, <0 if unable to write to register.
 ******************************************************************************/
int TCA6408A_PinOutToggle(I2C_TypeDef *i2c,
                       uint8_t addr,
                       uint8_t pin)
{
  int ret = -1;

  uint8_t tmp = 0;

  ret = TCA6408A_RegisterGet(i2c,addr,TCA6408A_RegOutput,&tmp);
  if (ret < 0)
  {
    return(ret);
  }

  tmp ^= 0x1 << pin;

  ret = TCA6408A_RegisterSet(i2c,addr,TCA6408A_RegOutput,tmp);

  return(ret);
}

/***************************************************************************//**
 * @brief
 *   Read current pin modes (input or output) in configuration register.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address, in 8 bit format, where LSB is reserved for R/W bit.
 *
 * @param[out] val
 *   Reference to place value read.
 *
 * @return
 *   Returns 0 if register read, <0 if unable to read register.
 ******************************************************************************/
int TCA6508A_PortModeGet(I2C_TypeDef *i2c,
                       uint8_t addr,
                       uint8_t *val)
{
  int ret = -1;

  uint8_t tmp = 0;

  ret = TCA6408A_RegisterGet(i2c,addr,TCA6408A_RegConfig,&tmp);
  if (ret < 0)
  {
    return(ret);
  }

  *val = tmp;

  return(ret);
}

/***************************************************************************//**
 * @brief
 *   Set pin modes (input or output) in configuration register.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address, in 8 bit format, where LSB is reserved for R/W bit.
 *
 * @param[it] val
 *   Value to set.
 *
 * @return
 *   Returns 0 if register written, <0 if unable to write to register.
 ******************************************************************************/
int TCA6508A_PortModeSet(I2C_TypeDef *i2c,
                       uint8_t addr,
                       uint8_t val)
{
  int ret = -1;

  ret = TCA6408A_RegisterSet(i2c,addr,TCA6408A_RegConfig,val);

  return(ret);
}

/***************************************************************************//**
 * @brief
 *   Read current values in input port register.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address, in 8 bit format, where LSB is reserved for R/W bit.
 *
 * @param[out] val
 *   Reference to place value read.
 *
 * @return
 *   Returns 0 if register read, <0 if unable to read register.
 ******************************************************************************/
int TCA6508A_PortInGet(I2C_TypeDef *i2c,
                       uint8_t addr,
                       uint8_t *val)
{
  int ret = -1;

  uint8_t tmp = 0;

  ret = TCA6408A_RegisterGet(i2c,addr,TCA6408A_RegInput,&tmp);
  if (ret < 0)
  {
    return(ret);
  }

  *val = tmp;

  return(ret);
}

/***************************************************************************//**
 * @brief
 *   Get current values (high or low) in output port register.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address, in 8 bit format, where LSB is reserved for R/W bit.
 *
 * @param[out] val
 *   Reference to place value read.
 *
 * @return
 *   Returns 0 if register read, <0 if unable to read register.
 ******************************************************************************/
int TCA6508A_PortOutGet(I2C_TypeDef *i2c,
                       uint8_t addr,
                       uint8_t *val)
{
  int ret = -1;

  uint8_t tmp = 0;

  ret = TCA6408A_RegisterGet(i2c,addr,TCA6408A_RegOutput,&tmp);
  if (ret < 0)
  {
    return(ret);
  }

  *val = tmp;

  return(ret);
}

/***************************************************************************//**
 * @brief
 *   Set bits in output port register to 1.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address, in 8 bit format, where LSB is reserved for R/W bit.
 *
 * @return
 *   Returns 0 if register written, <0 if unable to write to register.
 ******************************************************************************/
int TCA6408A_PortOutSet(I2C_TypeDef *i2c,
                       uint8_t addr)
{
  int ret = -1;

  ret = TCA6408A_RegisterSet(i2c,addr,TCA6408A_RegOutput,0xFF);

  return(ret);
}

/***************************************************************************//**
 * @brief
 *   Set bits in output port register to 0.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address, in 8 bit format, where LSB is reserved for R/W bit.
 *
 * @return
 *   Returns 0 if register written, <0 if unable to write to register.
 ******************************************************************************/
int TCA6408A_PortOutClear(I2C_TypeDef *i2c,
                       uint8_t addr)
{
  int ret = -1;

  ret = TCA6408A_RegisterSet(i2c,addr,TCA6408A_RegOutput,0x00);

  return(ret);
}

/***************************************************************************//**
 * @brief
 *   Set bits in output port register.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address, in 8 bit format, where LSB is reserved for R/W bit.
 *
 * @param[in] val
 *   Value used when writing to register.
 *
 * @return
 *   Returns 0 if register written, <0 if unable to write to register.
 ******************************************************************************/
int TCA6408A_PortOutSetVal(I2C_TypeDef *i2c,
                       uint8_t addr,
                       uint8_t val)
{
  int ret = -1;

  ret = TCA6408A_RegisterSet(i2c,addr,TCA6408A_RegOutput,val);

  return(ret);
}

/***************************************************************************//**
 * @brief
 *   Toggle bits in output port register.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address, in 8 bit format, where LSB is reserved for R/W bit.
 *
 * @return
 *   Returns 0 if register written, <0 if unable to write to register.
 ******************************************************************************/
int TCA6408A_PortOutToggle(I2C_TypeDef *i2c,
                       uint8_t addr)
{
  int ret = -1;

  uint8_t tmp = 0;

  ret = TCA6408A_RegisterGet(i2c,addr,TCA6408A_RegOutput,&tmp);
  if (ret < 0)
  {
    return(ret);
  }

  tmp = ~tmp;

  ret = TCA6408A_RegisterSet(i2c,addr,TCA6408A_RegOutput,tmp);

  return(ret);
}

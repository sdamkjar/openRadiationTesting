/*
 * rtcmk.c
 *
 *  Created on: May 28, 2018
 *      Author: sdamk
 */

#include "i2c.h"
#include "em_i2c.h"
#include "em_emu.h"
#include "rtcmk.h"

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
int RTCMK_RegisterSet(I2C_TypeDef *i2c,
                         uint8_t addr,
                         RTCMK_Register_TypeDef reg,
                         uint8_t val)
{
  I2C_TransferSeq_TypeDef seq;
  uint8_t data[3];

  seq.addr = addr;
  seq.flags = I2C_FLAG_WRITE;

  data[0] = ((uint8_t)reg);
  data[1] = (uint8_t)(val >> 8);
  data[2] = (uint8_t)val;
  
  seq.buf[0].data = data;
  seq.buf[0].len = 3;

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
int RTCMK_RegisterGet(I2C_TypeDef *i2c,
                         uint8_t addr,
                         RTCMK_Register_TypeDef reg,
                         uint8_t *val)
{
  I2C_TransferSeq_TypeDef seq;
  uint8_t regid[1];
  uint8_t data[2];

  seq.addr = addr;
  seq.flags = I2C_FLAG_WRITE_READ;
  /* Select register to be read */
  regid[0] = ((uint8_t)reg) & 0x7;
  seq.buf[0].data = regid;
  seq.buf[0].len = 1;
  
  seq.buf[1].data = data;
  seq.buf[1].len = 2;

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

  *val = (((uint16_t)(data[0])) << 8) | data[1];

  return((int)I2C_getStatus(i2c));
}

/***************************************************************************//**
 * @brief
 *   Write 0's to time and calender registors (0x00 to 0x06).
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address, in 8 bit format, where LSB is reserved for R/W bit.
 *
 * @return
 *   Returns 0 if registers written, <0 if unable to write to registers.
 ******************************************************************************/
int RTCMK_ResetTime(I2C_TypeDef *i2c,
                         uint8_t addr)
{
  I2C_TransferSeq_TypeDef seq;
  uint8_t data[8] = {0};

  seq.addr = addr;
  seq.flags = I2C_FLAG_WRITE;

  data[0] = ((uint8_t)RTCMK_RegSec);

  seq.buf[0].data = data;
  seq.buf[0].len = 8;

  I2C_TransferInit(i2c, &seq);

  while (I2C_getStatus(i2c) == i2cTransferInProgress)
  {
    /* Enter EM1 while waiting for I2C interrupt */
    EMU_EnterEM1();
    /* Could do a timeout function here. */
  }

  return((int)I2C_getStatus(i2c));
}

/***************************************************************************//**
 * @brief
 *   Returns current content of seconds register in decimal.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address, in 8 bit format, where LSB is reserved for R/W bit. 
 *
 * @param[out] val
 *   Reference to place result.
 *
 * @return
 *   Returns 0 if registers written, <0 if unable to write to registers.
 ******************************************************************************/
int RTCMK_ReadSeconds(I2C_TypeDef *i2c,
                       	uint8_t addr,
                       	uint8_t *val)
{
  int ret = -1;

  uint8_t tmp = 0;

  ret = RTCMK_RegisterGet(i2c,addr,RTCMK_RegSec,&tmp);
  if (ret < 0)
  {
    return(ret);
  }

  tmp &= _RTCMK_SEC_SEC_MASK;

  *val = ((tmp & 0xF0) >> 4) * 10 + (tmp & 0x0F);

  return(ret);
}

/***************************************************************************//**
 * @brief
 *   Returns current content of minutes register in decimal.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address, in 8 bit format, where LSB is reserved for R/W bit. 
 *
 * @param[out] val
 *   Reference to place result.
 *
 * @return
 *   Returns 0 if registers written, <0 if unable to write to registers.
 ******************************************************************************/
int RTCMK_ReadMinutes(I2C_TypeDef *i2c,
                       	uint8_t addr,
                       	uint8_t *val)
{
  int ret = -1;

  uint8_t tmp = 0;

  ret = RTCMK_RegisterGet(i2c,addr,RTCMK_RegMin,&tmp);
  if (ret < 0)
  {
    return(ret);
  }

  tmp &= _RTCMK_MIN_MIN_MASK;

  *val = ((tmp & 0xF0) >> 4) * 10 + (tmp & 0x0F);

  return(ret);
}

/***************************************************************************//**
 * @brief
 *   Returns current content of hours register in decimal.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address, in 8 bit format, where LSB is reserved for R/W bit. 
 *
 * @param[out] val
 *   Reference to place result.
 *
 * @return
 *   Returns 0 if registers written, <0 if unable to write to registers.
 ******************************************************************************/
int RTCMK_ReadHours(I2C_TypeDef *i2c,
                       	uint8_t addr,
                       	uint8_t *val)
{
  int ret = -1;

  uint8_t tmp = 0;

  ret = RTCMK_RegisterGet(i2c,addr,RTCMK_RegHour,&tmp);
  if (ret < 0)
  {
    return(ret);
  }

  tmp &= _RTCMK_HOUR_HOUR_MASK;

  *val = ((tmp & 0xF0) >> 4) * 10 + (tmp & 0x0F);

  return(ret);
}

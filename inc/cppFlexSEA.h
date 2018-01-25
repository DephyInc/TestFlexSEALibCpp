//****************************************************************************
//C++ wrapper for the FlexSEA stack
//****************************************************************************

#ifndef INC_CPP_FLEXSEA_H
#define INC_CPP_FLEXSEA_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdint.h>

//****************************************************************************
// Prototype(s):
//****************************************************************************

void requestReadActPack(uint8_t offset);
void printRigid(void);
void readActPack(uint8_t minOffs, uint8_t maxOffs, uint8_t printDiv);
void setControlMode( uint8_t ctrlMode);
void setMotorPosition(uint32_t motorPostion);
void setMotorCurrent(uint32_t motorCurrent);
void setMotorVoltage(uint32_t motorVoltage);
void setZGains(int z_k, int z_b, int i_kp, int i_ki);
uint8_t offs(uint8_t min, uint8_t max);

//****************************************************************************
// Definition(s):
//****************************************************************************

#endif


#include "types.h"

void byteWriteEEPROM_I2C(u8 slaveAddr, u16 wBuffAddr, u8 data);
u8 randReadEEPROM_I2C(u8 slaveAddr, u16 rBuffAddr);
void pageWriteEEPROM_I2C(u8 slaveAddr, u16 wBuffAddr, u8 *data, u8 bytes);
void seqReadEEPROM_I2C(u8 slaveAddr, u16 rBuffAddr, u8 *data, u8 bytes);

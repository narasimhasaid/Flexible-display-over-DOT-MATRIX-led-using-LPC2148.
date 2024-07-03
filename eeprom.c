#include <LPC21xx.h>
#include "i2c.h"
#include "types.h"
#include "delay.h"

void byteWriteEEPROM_I2C(u8 slaveAddr, u16 wBuffAddr, u8 data){
	startI2C(); // Issue i2c start
	writeI2C(slaveAddr<<1); // slaveAddr + w & take ACK
	writeI2C(wBuffAddr>>8); // wBuffAddr & take ACK // Writing upper byte of address
	writeI2C(wBuffAddr&0xFF); // wBuffAddr & take ACK // Writing lower byte of address
	writeI2C(data); // Data & take ACk
	stopI2C(); // Issue i2c Stop
	delay_ms(10); // Write cycle delay
}


u8 randReadEEPROM_I2C(u8 slaveAddr, u16 rBuffAddr){
	u8 data;

	startI2C(); // Issue i2c start
	writeI2C(slaveAddr<<1); // slaveAddr + w & take ACK
	writeI2C(rBuffAddr>>8); // rBuffAddr & take ACK // Writing upper byte of address
	writeI2C(rBuffAddr&0xFF); // rBuffAddr & take ACK // Writing lower byte of address
	restartI2C(); // Restart i2c
	writeI2C((slaveAddr<<1)|1); // slaveAddr + r & take ACK
	data = nackI2C();
	stopI2C(); // Issue i2c Stop

	return data;
}


void pageWriteEEPROM_I2C(u8 slaveAddr, u16 wBuffAddr, u8 *data, u8 bytes){
	u8 i;

	startI2C(); // Issue i2c start
	writeI2C(slaveAddr<<1); // slaveAddr + w & take ACK
	writeI2C(wBuffAddr>>8); // wBuffAddr & take ACK // Writing upper byte of address
	writeI2C(wBuffAddr&0xFF); // wBuffAddr & take ACK // Writing lower byte of address
	for(i=0; i<bytes; i++){
		// Write Data
		writeI2C(data[i]); // Data & take ACk
	}
	stopI2C(); // Issue i2c Stop
	delay_ms(10); // Write cycle delay
}


void seqReadEEPROM_I2C(u8 slaveAddr, u16 rBuffAddr, u8 *data, u8 bytes){
	u8 i;

	startI2C(); // Issue i2c start
	writeI2C(slaveAddr<<1); // slaveAddr + w & take ACK
	writeI2C(rBuffAddr>>8); // rBuffAddr & take ACK // Writing upper byte of address
	writeI2C(rBuffAddr&0xFF); // rBuffAddr & take ACK // Writing lower byte of address
	restartI2C(); // Restart i2c
	writeI2C((slaveAddr<<1)|1); // slaveAddr + r & take ACK
	for(i=0; i<bytes-1; i++){
		data[i] = mackI2C();
	}
	data[i] = nackI2C();
	stopI2C(); // Issue i2c Stop
}



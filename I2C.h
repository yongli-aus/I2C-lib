#ifndef I2C_H
#define I2C_H

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>

#define MAX_BUFFER_SIZE_1 64
#define I2C_port1 "/dev/i2c-2"

class I2C {

int i2cFile;

public:
I2C();
~I2C();


unsigned char I2C_WR_Buf[MAX_BUFFER_SIZE_1];

unsigned char I2C_RD_Buf[MAX_BUFFER_SIZE_1];


void i2cOpen();

void i2cClose();

void i2cSetAddress(unsigned char address);


void Send_I2C_Byte(unsigned char DEVICE_ADDR, unsigned char Reg_ADDR, unsigned char Data);


unsigned char Read_I2C_Byte(unsigned char DEVICE_ADDR,unsigned char Reg_ADDR);


unsigned char Read_Multi_Byte(unsigned char DEVICE_ADDR, unsigned char Reg_ADDR, size_t n);
};

#endif // I2C_H

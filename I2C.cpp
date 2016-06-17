#include "I2C.h"
#include <iostream>
using namespace std;


I2C::I2C(){
this->i2cOpen();
}

I2C::~I2C(){
this->i2cClose();
}


void I2C::i2cOpen()
{

i2cFile = open(I2C_port1, O_RDWR);
if (i2cFile < 0) {
perror("i2cOpen in I2C::i2cOpen");
//exit(1);
}

}


void I2C::i2cClose()
{
close(i2cFile);
}


void I2C::i2cSetAddress(unsigned char address)
{
//cout << "beagle-i2c setting address 0x"<< hex <<(int)address <<"... ";
if (ioctl(i2cFile, I2C_SLAVE, address) < 0) {
perror("i2cSetAddress error in myI2C::i2cSetAddress");
//exit(1);
}

}


void I2C::Send_I2C_Byte(unsigned char DEVICE_ADDR, unsigned char Reg_ADDR, unsigned char Data){
i2cSetAddress(DEVICE_ADDR);
//cout << "beagle-i2c writing 0x"<< hex << (int)Data <<" to 0x"<<hex <<(int)DEVICE_ADDR << ", reg 0x" <<hex<<(int)Reg_ADDR <<"... ";
I2C_WR_Buf[0] = Reg_ADDR;
I2C_WR_Buf[1] = Data;

if(write(i2cFile, I2C_WR_Buf, 2) != 2) {
perror("Write Error in myI2C::Send_I2C_Byte");
}

}


unsigned char I2C::Read_I2C_Byte(unsigned char DEVICE_ADDR,unsigned char Reg_ADDR){
I2C_WR_Buf[0] = Reg_ADDR;

i2cSetAddress(DEVICE_ADDR);
if(write(i2cFile, I2C_WR_Buf, 1) != 1) {
perror("Write Error in myI2C::Read_I2C_Byte");
}
i2cSetAddress(DEVICE_ADDR);
if(read(i2cFile, I2C_RD_Buf, 1) !=1){
perror("Read Error myI2C::Read_I2C_Byte");
}

return I2C_RD_Buf[0];


}

unsigned char I2C::Read_Multi_Byte(unsigned char DEVICE_ADDR, unsigned char Reg_ADDR, size_t n){
I2C_WR_Buf[0] = Reg_ADDR;

i2cSetAddress(DEVICE_ADDR);
size_t s = write(i2cFile, I2C_WR_Buf, 1);
if( s != 1) {

perror("Write Error in myI2C::Read_Multi_Byte");
}
i2cSetAddress(DEVICE_ADDR);
size_t t = read(i2cFile, I2C_RD_Buf, n);
if( t != n)
{

perror("Read Error in myI2C::Read_Multi_Byte");
}

return I2C_RD_Buf[0];
}


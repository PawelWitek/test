#ifndef _I2C_H_
#define _I2C_H_

sbit SDA= P1^0; 
sbit SCL= P1^1;
#include <intrins.h>


void nop(void)
{
unsigned char z;
 z=1;
 z=0;
 z=1;
 z=0;
 z=1;
 
}
void I2cStart(void)
{
SCL=1;
nop();
SDA=0;
nop();
SCL=0;
nop();
SDA=1;
nop();
}

void I2cStop(void)
{
SDA=0;
nop();
SCL=1;
nop();
SDA=1;
nop();
}

I2cWbyte(unsigned char x)
{
int i;
for(i=8;i>0;i--)
{
if((x&0x80)==0)
SDA=0;
else
SDA=1;
nop();
SCL=1;
nop();
SCL=0;
nop();
x=x<<1;
}
SDA=1;
nop();
SCL=1;
nop();
SCL=0;
}

unsigned char I2cRbyte(unsigned char ack)
{
unsigned char i;
unsigned char x;
unsigned char dana=0;
for(i=8;i>0;i--)
{
SCL=1;
nop();
dana=dana*2;
x=SDA;
nop();
SCL=0;
nop();
if(x==1)
dana=dana+1;
else
dana=dana+0;

nop();
}
if (ack==1)
{
SDA=0;
nop();
}
SCL=1;
nop();
SCL=0;
nop();
SDA=1;
nop();
return dana;
}

#endif



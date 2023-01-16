#include <REGX52.H>
#include <INTRINS.H>

sbit OneWire_DQ=P3^7;

unsigned char OneWire_Init()
{
	unsigned char i,AckBit;
	EA=0;
	OneWire_DQ=1;
	OneWire_DQ=0;
	_nop_();i = 227;while (--i);//Delay 500us
	OneWire_DQ=1;
	_nop_();i = 29;while (--i);//Delay 70us
	AckBit=OneWire_DQ;
	_nop_();i = 227;while (--i);//Delay 500us
	EA=1;
	return AckBit;
}

void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	EA=0;
	OneWire_DQ=0;
	i = 4;while (--i);//Delay 10us
	OneWire_DQ=Bit;
	i = 22;while (--i);//Delay 50us
	OneWire_DQ=1;
	EA=1;
}

unsigned char OneWire_ReceiveBit()
{
	unsigned char Bit,i;
	EA=0;
	OneWire_DQ=0;
	i = 2;while (--i);//Delay 5us
	OneWire_DQ=1;
	i = 2;while (--i);//Delay 5us
	Bit=OneWire_DQ;
	i = 22;while (--i);//Delay 50us
	EA=1;
	return Bit;
}

void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		OneWire_SendBit(Byte&0x01<<i);
	}
}

unsigned char OneWire_ReceiveByte()
{
	unsigned char i,Byte=0x00;
	for(i=0;i<8;i++)
	{
		if(OneWire_ReceiveBit()){Byte|=0x01<<i;}
	}
	return Byte;
}	
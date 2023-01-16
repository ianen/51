#include <REGX52.H>
#include "LCD1602.h"
#include "DS18B20.h"
#include "Delay.h"
#include "AT24C02.h"
#include "Key.h"
#include "Timer0.h"

float T,TShow;
char Tlow,Thigh;
unsigned char KeyNum;

void main()
{
	Thigh=AT24C02_ReadByte(0);
	Tlow=AT24C02_ReadByte(1);
	if(Thigh>125||Tlow<-55||Thigh<=Tlow)
	{
		Thigh=20;
		Tlow=15;
	}
	DS18B20_ConvertT();
	Delay(500);
	LCD_Init();
	LCD_ShowString(1,1,"T:");
	LCD_ShowString(2,1,"TH:");
	LCD_ShowString(2,9,"TL:");
	LCD_ShowSignedNum(2,4,Thigh,3);
	LCD_ShowSignedNum(2,12,Tlow,3);
	Timer0_Init();
	while(1)
	{
		KeyNum=Key();
		//温度读取及显示
		DS18B20_ConvertT();
		T=DS18B20_ReadT();
		if(T<0)
		{
			LCD_ShowChar(1,3,'-');
			TShow=-T;
		}
		else
		{
			LCD_ShowChar(1,3,'+');
			TShow=T;
		}
		LCD_ShowNum(1,4,TShow,3);
		LCD_ShowChar(1,7,'.');
		LCD_ShowNum(1,8,(unsigned long)(TShow*100)%100,2);
		
		//阈值判断及显示
		if(KeyNum)
		{
			if(KeyNum==1)
			{
				Thigh++;
				if(Thigh>125) Thigh=125;
			}
			if(KeyNum==2)
			{
				Thigh--;
				if(Thigh<=Tlow) Thigh++;
			}
			if(KeyNum==3)
			{
				Tlow++;
				if(Thigh<=Tlow) Tlow--;
			}
			if(KeyNum==4)
			{
				Tlow--;
				if(Tlow<-55) Tlow=-55;
			}
			LCD_ShowSignedNum(2,4,Thigh,3);
			LCD_ShowSignedNum(2,12,Tlow,3);
			AT24C02_WriteByte(0,Thigh);
			Delay(5);
			AT24C02_WriteByte(1,Tlow);
			Delay(5);
		}
		if(T>Thigh)
		{
			LCD_ShowString(1,13,"OV:H");
		}
		else if(T<Tlow)
		{
			LCD_ShowString(1,13,"OV:L");
		}
		else
		{
			LCD_ShowString(1,13,"    ");
		}
	}
}

void Timer0_Routine() interrupt 1//定时器0的中断函数
{
	static unsigned int T0Count;
	TH0=0xFC;//使计数单元回拨到1ms前，使其再次计数（反复1ms）
	TL0=0x18;
	T0Count++;
	if(T0Count>=20)
	{
		T0Count=0;
		Key_Loop();
	}
}
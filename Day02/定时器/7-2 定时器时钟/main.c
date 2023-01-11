#include <REGX52.H>
#include "LCD1602.h"
#include "Timer0.h"

unsigned char Sec=00,Min=59,Hour=23;
void main()
{
	Timer0Init();
	LCD_Init();
	LCD_ShowString(1,1,"Clock:");
	LCD_ShowString(2,1,"  :  :");
	while(1)
	{
		LCD_ShowNum(2,1,Hour,2);
		LCD_ShowNum(2,4,Min,2);
		LCD_ShowNum(2,7,Sec,2);
	}
}
void Timer0_Routine() interrupt 1//定时器0的中断函数
{
	static unsigned int T0Count;
	TH0=0xFC;//使计数单元回拨到1ms前，使其再次计数（反复1ms）
	TL0=0x18;
	T0Count++;
	if(T0Count>=1000)//达到1s时执行
	{
		T0Count=0;//重置T0Count（反复1s）
		Sec++;
		if(Sec>=60)
		{
			Sec=0;
			Min++;
			if(Min>=60)
			{
				Min=0;
				Hour++;
				if(Hour>=24)Hour=0;
			}
		}
	}
}
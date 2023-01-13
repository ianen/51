#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"
#include "Timer0.h"

unsigned char KeyNum,MODE,TimeSetSelete,TimeSetFlashFlag;

void TimeShow(void)
{
	DS1302_ReadTime();
	LCD_ShowNum(1,3,DS1302_Time[0],2);
	LCD_ShowNum(1,6,DS1302_Time[1],2);
	LCD_ShowNum(1,9,DS1302_Time[2],2);
	LCD_ShowNum(2,1,DS1302_Time[3],2);
	LCD_ShowNum(2,4,DS1302_Time[4],2);
	LCD_ShowNum(2,7,DS1302_Time[5],2);
}
void TimeSet(void)
{
	if(KeyNum==2)
	{
		TimeSetSelete++;
		TimeSetSelete%=6;
	}
	if(KeyNum==3) 
	{
		DS1302_Time[TimeSetSelete]++;
		if(DS1302_Time[0]>99) DS1302_Time[0]=0;
		if(DS1302_Time[1]>12) DS1302_Time[1]=1;
		//日的判断
		if(DS1302_Time[1]==1||DS1302_Time[1]==3||DS1302_Time[1]==5||DS1302_Time[1]==7||DS1302_Time[1]==8||DS1302_Time[1]==10||DS1302_Time[1]==12)
		{
			if(DS1302_Time[2]>31) DS1302_Time[2]=1;
			if(DS1302_Time[2]==0) DS1302_Time[2]=31;
		}
		if(DS1302_Time[1]==4||DS1302_Time[1]==6||DS1302_Time[1]==9||DS1302_Time[1]==11)
		{
			if(DS1302_Time[2]>30) DS1302_Time[2]=1;
			if(DS1302_Time[2]==0) DS1302_Time[2]=30;
		}
		if(DS1302_Time[1]==2)
		{
			if(DS1302_Time[0]%4==0)
			{
				if(DS1302_Time[2]>29) DS1302_Time[2]=1;
				if(DS1302_Time[2]==0) DS1302_Time[2]=29;
			}
			else
			{
				if(DS1302_Time[2]>28) DS1302_Time[2]=1;	
				if(DS1302_Time[2]==0) DS1302_Time[2]=28;
			}
		}
		
		if(DS1302_Time[3]>23) DS1302_Time[3]=0;
		if(DS1302_Time[4]>59) DS1302_Time[4]=0;
		if(DS1302_Time[5]>59) DS1302_Time[5]=0;
	}
	if(KeyNum==4)
	{
		DS1302_Time[TimeSetSelete]--;
		if(DS1302_Time[0]>100) DS1302_Time[0]=99;
		if(DS1302_Time[1]==0) DS1302_Time[1]=12;
		//日的判断
		if(DS1302_Time[1]==1||DS1302_Time[1]==3||DS1302_Time[1]==5||DS1302_Time[1]==7||DS1302_Time[1]==8||DS1302_Time[1]==10||DS1302_Time[1]==12)
		{
			if(DS1302_Time[2]>31) DS1302_Time[2]=1;
			if(DS1302_Time[2]==0) DS1302_Time[2]=31;
		}
		if(DS1302_Time[1]==4||DS1302_Time[1]==6||DS1302_Time[1]==9||DS1302_Time[1]==11)
		{
			if(DS1302_Time[2]>30) DS1302_Time[2]=1;
			if(DS1302_Time[2]==0) DS1302_Time[2]=30;
		}
		if(DS1302_Time[1]==2)
		{
			if(DS1302_Time[0]%4==0)
			{
				if(DS1302_Time[2]>29) DS1302_Time[2]=1;
				if(DS1302_Time[2]==0) DS1302_Time[2]=29;
			}
			else
			{
				if(DS1302_Time[2]>28) DS1302_Time[2]=1;	
				if(DS1302_Time[2]==0) DS1302_Time[2]=28;
			}
		}
		
		if(DS1302_Time[3]>100) DS1302_Time[3]=23;
		if(DS1302_Time[4]>100) DS1302_Time[4]=59;
		if(DS1302_Time[5]>100) DS1302_Time[5]=59;
	}
	if(TimeSetSelete==0&&TimeSetFlashFlag==1)
		LCD_ShowString(1,1,"    ");
	else
	{
		LCD_ShowNum(1,3,DS1302_Time[0],2);
		LCD_ShowNum(1,1,20,2);
	}
	if(TimeSetSelete==1&&TimeSetFlashFlag==1)
		LCD_ShowString(1,6,"  ");
	else
	{
		LCD_ShowNum(1,6,DS1302_Time[1],2);
	}	
	if(TimeSetSelete==2&&TimeSetFlashFlag==1)
		LCD_ShowString(1,9,"  ");
	else
	{
		LCD_ShowNum(1,9,DS1302_Time[2],2);
	}
	if(TimeSetSelete==3&&TimeSetFlashFlag==1)
		LCD_ShowString(2,1,"  ");
	else
	{
		LCD_ShowNum(2,1,DS1302_Time[3],2);
	}
	if(TimeSetSelete==4&&TimeSetFlashFlag==1)
		LCD_ShowString(2,4,"  ");
	else
	{
		LCD_ShowNum(2,4,DS1302_Time[4],2);
	}
	if(TimeSetSelete==5&&TimeSetFlashFlag==1)
		LCD_ShowString(2,7,"  ");
	else
	{
		LCD_ShowNum(2,7,DS1302_Time[5],2);
	}
}
void main()
{
	LCD_Init();
	DS1302_Init(); 
	Timer0Init();
	DS1302_SetTime();
	LCD_ShowString(1,1,"20  -  -");
	LCD_ShowString(2,1,"  :  :");
	while(1)
	{
		KeyNum=Key();
		if(KeyNum==1)
		{
			if(MODE==0) MODE=1;
			else if(MODE==1) 
			{
				MODE=0;
				TimeSetSelete=0;
				LCD_ShowNum(1,1,20,2);
				DS1302_SetTime();
			}
		}
		switch(MODE)
		{
			case 0:TimeShow();break;
			case 1:TimeSet();break;
		}
	}
}
void Timer0_Routine() interrupt 1//定时器0的中断函数
{
	static unsigned int T0Count;
	TH0=0xFC;//使计数单元回拨到1ms前，使其再次计数（反复1ms）
	TL0=0x18;
	T0Count++;
	if(T0Count>=300)//达到1s时执行
	{
		T0Count=0;//重置T0Count（反复1s）
		TimeSetFlashFlag=!TimeSetFlashFlag;
	}
}
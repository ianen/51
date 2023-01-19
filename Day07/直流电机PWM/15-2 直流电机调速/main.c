#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "Timer0.h"
#include "Nixie.h"

sbit Motor=P1^0;

unsigned char KeyNum,Speed,Counter,Compare;

void main()
{
	Timer0_Init();
	while(1)
	{
		KeyNum=Key();
		if(KeyNum==1)
		{
			Speed++;
			Speed%=4;
			if(Speed==0){Compare=0;}
			if(Speed==1){Compare=60;}
			if(Speed==2){Compare=75;}
			if(Speed==3){Compare=100;}
		}
		Nixie(1,Speed);	
	}
}

void Timer0_Routine() interrupt 1//定时器0的中断函数
{
	TH0=0xFF;
	TL0=0xF7;
	Counter++;
	Counter%100;
	if(Counter<Compare)
	{
		Motor=1;
	}
	else
	{
		Motor=0;
	}
}
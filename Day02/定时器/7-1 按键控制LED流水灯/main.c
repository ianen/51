#include <REGX52.H>
#include <INTRINS.H>
#include "Timer0.h"
#include "Key.h"

unsigned char KeyNum,LEDMode;
void main()
{
    P2=0xFE;
	Timer0Init();//开启计时，溢出（即1ms）时跳转到中断函数
	while(1)
	{
		KeyNum=Key();
        if(KeyNum)
        {
            if(KeyNum==1)
            {
                LEDMode++;
                if(LEDMode>=2)LEDMode=0;
            }
        }  
	}
}
void Timer0_Routine() interrupt 1//定时器0的中断函数
{
	static unsigned int T0Count;
	TH0=0xFC;//使计数单元回拨到1ms前，使其再次计数（反复1ms）
	TL0=0x18;
	T0Count++;
	if(T0Count>=500)//达到1s时执行
	{
		T0Count=0;//重置T0Count（反复1s）
		if(LEDMode==0)
            P2=_crol_(P2,1);
        if(LEDMode==1)
            P2=_cror_(P2,1);
	}
}
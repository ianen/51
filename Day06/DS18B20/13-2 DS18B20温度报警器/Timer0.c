#include <REGX52.H>

/**
  *@brief  定时器0初始化，1毫秒
  *@param  无
  *@retval 无
  */
void Timer0_Init()//定时器0初始化
{
	//时钟
	TMOD=TMOD&0xF0;//低四位清零，高四位保持不变，不影响定时器1的运作 
	TMOD=TMOD|0x01;//最低位为1，高四位不变，配置TMOD寄存器的定时器0开启,
	TF0=0;//配置TCON寄存器中的溢出标志为0
	TR0=1;//配置TCON寄存器中定时器0开启
	//计数单元
	TH0=0xFC;//配置计数单元，为取1ms即1000us，初始化为65535-1000。/256以取高位
	TL0=0x18;//配置中计数单元，%256以取低位
	//中断系统
	ET0=1;//配置中断系统的IE
	EA=1;//配置中断系统的IE
	PT0=0;//配置中断系统拨到低优先级
}
/*定时器1s中断函数模板
void Timer0_Routine() interrupt 1//定时器0的中断函数
{
	static unsigned int T0Count;
	TH0=0xFC;//使计数单元回拨到1ms前，使其再次计数（反复1ms）
	TL0=0x18;
	T0Count++;
	if(T0Count>=1000)//达到1s时执行
	{
		T0Count=0;//重置T0Count（反复1s）
		中断时的操作;
	}
}
*/
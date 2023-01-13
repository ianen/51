#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"
#include "LCD1602.h"

sbit Buzzer=P2^5;		//蜂鸣器端口定义


#define SPEED	340   //速度

//音符与索引对应表，P：休止符，L：低音，M：中音，H：高音，下划线
#define P	0
#define L1	1
#define L1_	2
#define L2	3
#define L2_	4
#define L3	5
#define L4	6
#define L4_	7
#define L5	8
#define L5_	9
#define L6	10
#define L6_	11
#define L7	12
#define M1	13
#define M1_	14
#define M2	15
#define M2_	16
#define M3	17
#define M4	18
#define M4_	19
#define M5	20
#define M5_	21
#define M6	22
#define M6_	23
#define M7	24
#define H1	25
#define H1_	26
#define H2	27
#define H2_	28
#define H3	29
#define H4	30
#define H4_	31
#define H5	32
#define H5_	33
#define H6	34
#define H6_	35
#define H7	36

//索引与频率对照表
unsigned int FreqTable[]={
	0,
	63465,63577,63691,63792,63892,63981,64070,64152,64229,64303,64372,64438,
	64499,64557,64612,64664,64713,64759,64803,64844,64883,64919,64954,64987,
	65017,65047,65074,65100,65124,65148,65169,65190,65209,65228,65245,65261,};

//乐谱
code unsigned char  Music[]={

	//1
	H5,2,
	H4,2,
	P,2,
	H2,2,
	H1,2,
	P,2,
	M6,2,
	M6_,2,
	
	//2
	P,2,
	H4,2,
	M4,2,
	M6_,1,
	H1,1,
	H2,2,
	H1,2,
	M6_,4,
	
	//3
	H5,2,
	H4,2,
	P,2,
	H2,2,
	H1,2,
	P,2,
	M6,2,
	M6_,2,
	
	//4
		P,2,
	H4,2,
	M4,2,
	M6_,1,
	H1,1,
	H2,2,
	H1,2,
	M6_,4,
	
	//5
	H5,2,
	H4,2,
	P,2,
	H2,2,
	H1,2,
	P,2,
	M6,2,
	M6_,2,
	
	//6
	P,2,
	H4,2,
	M4,2,
	M6_,1,
	H1,1,
	H6_,2,
	H6,2,
	H4,4,
	
	//7
	H5,2,
	H4,2,
	P,2,
	H2,2,
	H1,2,
	P,2,
	M6,2,
	M6_,2,
	
	
	//8
	P,2,
	H4,2,
	M4,2,
	M6_,1,
	H1,1,
	H2,2,
	H1,2,
	M6_,4,
	
	//9
	H2,2,
	M4,2,
	M4,2,
	H1,2,
	M4,2,
	M6,2,
	M6_,2,
	H4,2,
	
	//10
	H4,4+4,
	H4,2,
	M2,2,
	M1,2,
	L6_,2,
	
	//11
	L6_,2,
	M1,2,
	M2,2,
	M4,2,
	P,2,
	L6_,4,
	M1,2,
	
	//12
	M1,4+2,
	M2,2,
	P,2,
	M2,2,
	M1,2,
	L6_,2,
	
	//13
	L6_,2,
	M1,4,
	M6,2+2,
	L6_,2,
	L6_,2,
	M1,2,
	
	//14
	M1,2,
	L6_,4,
	L6,2,
	L6_,4,
	P,4,
	
	//15 16
	M6_,4+2,
	M6_,2,
	M5,2,
	M4,2,
	M4,2,
	M4,2+2,
	M6_,2,
	M6_,2,
	H1,2,
	H2,2,
	P,2,
	M4,2,
	M4,2,
	
	//17  18
	M4,2,
	M6_,2,
	H1,2,
	H2,2+2,
	H1,2+2,
	M4,2+2,
	M6_,2,
	M6_,2,
	H1,2,
	H1,2,
	P,2,
	M6_,4,
	
	//19
	P,4,
	P,2,
	M6_,2,
	M6_,2,
	M6,2,
	M4,2,
	M4,2,
	
	//20
	M4,4,
	M4,2,
	M4,2+2,
	M2_,2,
	M2,2,
	L6_,2,
	
	//21
	L6_,2,
	M1,2,
	M2,2,
	L6_,2,
	L6_,2,
	M1,2,
	M2,2,
	L6_,2,
	
	//22
	L6_,2,
	M1,2,
	L6_,2,
	L6_,2,
	L6_,2,
	M6_,2+2,
	M6,2,
	
	//23 24
	M6_,4,
	P,2,
	M6_,2,
	M6_,4,
	H2,2,
	H1,2+2,
	M6_,2,
	P,2,
	M6_,2,
	H1,2,
	M6_,2+2,
	M6_,2,
	
	//25 26
	M6,4+2,
	P,2,
	M6,4,
	M6_,2,
	H1,2,
	
	//26
	H1,4+4+4+4,
	
	//27
	P,4,
	P,4,
	P,4,
	M4_,2,
	M4_,2,
	
	//28
	M7,4,
	H1_,4,
	H2_,4,
	H1_,4,
	
	
	//29
	M7,4,
	M7,4+4,
	M7,4,
	
	//30
	H1_,4,
	M7,4+4,
	H2_,2,
	H1_,2,
	
	//31
	H2_,4+2,
	P,2,
	P,4,
	M4,2,
	M4,2,
	
	//32
	M7,4,
	H1_,4,
	H2_,4,
	H1_,4,
	
	
	//33
	M7,4,
	M7,4,
	P,4,
	M7,4,
	
	
	//34
	H1_,4,
	M7,4,
	H3,4,
	H2_,2,
	H1_,2,
	
	
	//35
	H1_,4+4,
	H2_,4,
	P,4,
	
	
	//37
	M7,4,
	H1_,4,
	H4_,4,
	H1_,2,
	M7,2,
	
	
	//38
	M7,2,
	P,2,
	M4_,4,
	M4_,4+4,
	
	//39
	H1_,2,
	M7,2,
	M7,4,
	H1_,4,
	H3,4,
	
	
	//40
	H2_,4,
	H3,4,
	H2_,4,
	H1_,2,
	M7,2,
	
	
	//41
	M7,4,
	P,4,
	M7,4+4,
	
	
	//42
	M7,4+2,
	P,2,
	H2_,4+4,
	
	
	//43
	H1_,4+4,
	M7,4,
	
	
	//44
	M6_,4+2,
	P,2,
	P,4,
	M4_,2,
	M4_,2,
	
	
	//45
	M7,4,
	H1_,4,
	H2_,4,
	H1_,4,
	
	
	//46
	M7,4,
	M7,4+4,
	M7,4,
	
	
	//47
	M5_,2,
	M6_,2,
	M6_,4+4,
	M5_,2,
	M4_,2,
	
	
	//48
	M4_,4+4,
	P,4,
	M4_,2,
	M4_,2,
	
	
	//49
	M7,4,
	H1_,4,
	H2_,4,
	H1_,4,
	
	
	//50
	M7,4,
	M7,4,
	P,4,
	M7,4,
	
	
	//51
	H1_,4+4+4,
	H1_,2,
	H2_,2,
	
	
	//52
	H2_,4+2,
	P,2,
	P,4,
	M7,2,
	M7,2,
	
	
	//53
	M7,4,
	H1_,4,
	H4_,2,
	M7,2,
	M7,4,
	
	
	//54
	M7,4,
	H4_,4,
	H4_,2,
	P,2,
	M7,2,
	M7,2,
	
	//55
	M7,4,
	H4_,4,
	H4_,2,
	H1_,2,
	M6_,4,


	//56
	M7,4,
	H4_,4,
	H4_,2,
	P,2,
	H4_,2,
	H4_,2,
	
	
	//57
	M4_,4,
	M7,4,
	P,4,
	M4_,4,
	
	
	//58
	M4_,4,
	M7,4,
	M7,4,
	H2_,2,
	H1_,2,
	
	//59
	H1_,4,
	P,4,
	M7,4,
	H2_,2,
	H3,2,
		
	//60
	H3,4,
	H2_,4,
	M7,4,
	M6_,4,
		
	M7,4+4+4+4,
		
	
	
	0xFF	//终止
};

unsigned long FreqSelect,MusicSelect;

void main()
{
	  LCD_Init();
		LCD_ShowString(1,2,"Lycoris Recoil");
	Timer0Init();
	while(1)
	{
		if(Music[MusicSelect]!=0xFF)	//如果不是停止标志位
		{
			FreqSelect=Music[MusicSelect];	//选择音符对应的频率
			MusicSelect++;
			Delay(SPEED/4*Music[MusicSelect]);	//选择音符对应的时值
			MusicSelect++;
			TR0=0;
			Delay(5);	
			TR0=1;
		}
		else	
		{
			TR0=0;
			while(1);
		}
	}
}

void Timer0_Routine() interrupt 1
{
	if(FreqTable[FreqSelect])	//???????
	{
		/*取对应频率值的重装载值到定时器*/
		TL0 = FreqTable[FreqSelect]%256;		//设置定时初值
		TH0 = FreqTable[FreqSelect]/256;		//设置定时初值
		Buzzer=!Buzzer;	
	}
}

#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "Nixie.h"
#include "Buzzer.h"

unsigned char KeyNum;

void main()
{
	while(1)
	{
		KeyNum=Key();
		if(KeyNum)
		{
			Nixie(1,KeyNum);
			Buzzer_Time(100);
		}
	}
}
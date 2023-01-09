

# Day 

## 一、矩阵键盘介绍：

1. 采用逐行（列）扫描，减少io口数量：

   - 注意：因开发板接线问题，应采用逐列扫描；

2. 内部io口采用准双向口配置：

   - stc51单片机的P1，P2和P3都是准双向口；

   - 四种工作模式：准双向口，推挽输出，开漏输出，高阻输出；

   - 准双向口工作原理：
     
     - ![image-20230109143928655](C:\Users\86198\AppData\Roaming\Typora\typora-user-images\image-20230109143928655.png)
     
     - ![image-20230109143255007](C:\Users\86198\AppData\Roaming\Typora\typora-user-images\image-20230109143255007.png)
     
     - 输出（sw1）：
     
       要输出高电平时，sw1接上方，锁住三极管防止接地，高电平正常输出；
     
       要输出低电平时，sw1接下方，使三极管接通，电路接地，输出端被下拉至低电平；
     
     - 输入（sw2）：
     
       要输入低电平时，sw2接下方，接地后输出端下拉至低电平；
     
       要输出高电平时，若sw1接低电平，三极管导通，输出端被下拉至低电平，所以为准确输入高电平，读前先写1，“准”便是提前准备，也是接近标准双向口的意思；
     
     - ![image-20230109145019021](C:\Users\86198\AppData\Roaming\Typora\typora-user-images\image-20230109145019021.png)
     
   

## 二、矩阵键盘程序编写：

1. keil中Templates的使用：
   - ![image-20230109145420902](C:\Users\86198\AppData\Roaming\Typora\typora-user-images\image-20230109145420902.png)
   - ![image-20230109145459554](C:\Users\86198\AppData\Roaming\Typora\typora-user-images\image-20230109145459554.png)
   - 可以直接选用已有的程序模板，或者也可以自定义
   - |可以作为光标位置直接跳转

2. MatrixKey模块：
   
   - ```c
     #include <REGX52.H>
     #include "Delay.h"
     
     /**
       * @brief  矩阵键盘读取按键键码
       * @param  无
       * @retval KeyNumber 按下按键的键码值
     			如果按键按下不放，程序会停留在此函数，松手的一瞬间，返回按键键码，没有按键按下时，返回0
       */
     unsigned char MatrixKey()
     {
     	unsigned char KeyNumber=0;
     	
     	P1=0xFF;
     		P1_3=0;
     	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=1;}
     	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=5;}
     	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=9;}
     	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=13;}
     	
     	P1=0xFF;
     	P1_2=0;
     	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=2;}
     	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=6;}
     	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=10;}
     	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=14;}
     	
     	P1=0xFF;
     	P1_1=0;
     	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=3;}
     	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=7;}
     	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=11;}
     	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=15;}
     	
     	P1=0xFF;
     	P1_0=0;
     	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=4;}
     	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=8;}
     	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=12;}
     	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=16;}
     	
     	return KeyNumber;
     }
     ```
   
   - ```c
     #ifndef __MATRIXKEY_H__
     #define __MATRIXKEY_H__
     
     unsigned char MatrixKey();
     
     #endif
     ```

3. 注释：

   - ```c
     /**
       * @brief  矩阵键盘读取按键键码（简介）
       * @param  无（参数）
       * @retval KeyNumber 按下按键的键码值（返回值）
     		如果按键按下不放，程序会停留在此函数，松手的一瞬间，返回按键键码，没有按键按下时，返回0
       */
     ```

## 三、矩阵键盘密码锁：

1. 程序代码：

   - ```c
     #include <REGX52.H>
     #include "Delay.h"
     #include "LCD1602.h"
     #include "MatrixKey.h"
     
     unsigned char KeyNum;
     unsigned int Password=0,Count;
     
     void main()
     {
     	LCD_Init();
     	LCD_ShowString(1,1,"Password:");
     	LCD_ShowString(2,1,"****");
     	while(1)
     	{
     		KeyNum=MatrixKey();
     		if(KeyNum)
     		{
     			if(KeyNum<=10&&Count<4)
     			{
     				Password*=10;
     				Password+=KeyNum%10;
     				Count++;
     			}
     			LCD_ShowNum(2,1,Password,4);
     			if(KeyNum==11)
     				if(Password==9999)
     				{
     					LCD_ShowString(1,14,"OK ");
     					Password=0;
     					Count=0;
     					LCD_ShowString(2,1,"****");
     				}					
     				else
     				{
     					LCD_ShowString(1,14,"ERR");
     					Password=0;
     					Count=0;
     					LCD_ShowString(2,1,"****");
     				}
     			if(KeyNum==12)
     			{
     				Password/=10;
     				if(Count>0)
     					Count--;
     				LCD_ShowNum(2,1,Password,4);//更新显示
     			}
     		}
     	}
     }
     ```

## 四、计时器

1. 介绍：
   - 

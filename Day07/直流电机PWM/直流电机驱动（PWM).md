# 直流电机驱动（PWM)

## 一、介绍：

- 除直流电机外，还有步进电机，舵机，无刷电机，空心杯电机；

- 步进电机内部结构：

  ![image-20230119173208852](C:\Users\86198\AppData\Roaming\Typora\typora-user-images\image-20230119173208852.png)

- 舵机：根据输入电平的时间来控制选择角度；
  ![image-20230119173339740](C:\Users\86198\AppData\Roaming\Typora\typora-user-images\image-20230119173339740.png)

## 二、电机驱动方式：

1. 大功率器件直接驱动：只能转一个方向；

   - IN控制Q1三极管的导通，D1二极管用来保护Q1，因为当电流突然断开时，M电机会电流感应生成电流，当电流过大时可能会击穿Q1；

   - ![image-20230119173816677](C:\Users\86198\AppData\Roaming\Typora\typora-user-images\image-20230119173816677.png)

2. H桥驱动：可以控制转动方向；

   ![image-20230119173826263](C:\Users\86198\AppData\Roaming\Typora\typora-user-images\image-20230119173826263.png)

## 三、PWM介绍：

- 即脉冲宽度调制，在具有惯性的系统中，可以通过对一系列脉冲的宽度进行调制，来等效地获得所需要的模拟参量，常用于电机控速、开关电源等领域；

- 重要参数：
  - 频率=1/Ts(周期)
  - 占空比=Ton/Ts
  - 精度=占空比变化步距
  - ![image-20230119175243595](C:\Users\86198\AppData\Roaming\Typora\typora-user-images\image-20230119175243595.png)

## 四、LED呼吸灯：

- ```c
  #include <REGX52.H>
  
  sbit LED=P2^0;
  
  void Delay(unsigned char t)
  {
  	while(t--);
  }
  
  void main()
  {
  	unsigned char Time,i;
  	LED=0;
  	while(1)
  	{
  		for(Time=0;Time<100;Time++)
  		{
  			for(i=0;i<20;i++)
  			{
  				LED=0;
  				Delay(Time);
  				LED=1;
  				Delay(100-Time);
  			}
  		}
  		for(Time=100;Time>0;Time--)
  		{
  			for(i=0;i<20;i++)
  			{
  				LED=0;
  				Delay(Time);
  				LED=1;
  				Delay(100-Time);
  			}
  		}
  	}
  }

## 五、直流电机调速：

### 1. 产生PWM方法：

- ![image-20230119185225804](C:\Users\86198\AppData\Roaming\Typora\typora-user-images\image-20230119185225804.png)
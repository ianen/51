# LED点阵屏

## 一、显示原理：

- 类似数码管把“8”字型排列成一行或一列；
- 与数码管一样有共阴和共阳两个接法；
- LED点阵屏需要进行逐行或逐列扫描；

## 二、开发板引脚对应关系：

- 点阵屏：![image-20230112140006602](C:\Users\86198\AppData\Roaming\Typora\typora-user-images\image-20230112140006602.png)

- D对应到74HC595：

  ![image-20230112140139408](C:\Users\86198\AppData\Roaming\Typora\typora-user-images\image-20230112140139408.png)

  接至P34，35，36口；

- 74HC595介绍：

  ![image-20230112140840438](C:\Users\86198\AppData\Roaming\Typora\typora-user-images\image-20230112140840438.png)

## 三、LED点阵屏显示图形：

### 1. sfr和sbit：

1. sfr:特殊功能寄存器声明，在头文件中将对应特殊功能寄存器的地址赋给相应的名称；
2. sbit：特殊位声明，指定某个寄存器的单一位；

### 2. 可位寻址和不可位寻址：

- 位的数量是寄存器的8倍，单片机无法对所有位进行编码，所以每8个寄存器中只有1个可位寻址；
- 若要只操作其中以位而不影响其他位时，可以用&=、|=、^=来进行位操作；

### 3. 74HC595载入D口函数：

- ```c
  void _74HC595_WriteByte(unsigned char Byte)
  {
  	unsigned char i;
  	for(i=0;i<8;i++)
  	{
  		SER=Byte&(0x80>>i);
  		SCK=1;
  		SCK=0;
  	}
  	RCK=1;
  	RCK=0;
  //	P2=~Byte;
  }
  

### 4. LED点阵显示特定列函数：

- ```c
  void MatrixLED_ShowColumn(unsigned char Column,Data)
  {
  	_74HC595_WriteByte(Data);
  	P0=~(0x80>>Column); 
  	Delay(1);//防止出现残影
  	P0=0xFF;//清零
  }

- 单列中01从列的最下面往上；

## 二、LED点阵屏显示动画：

- 原理：通过按顺序显示数组区域形成动画
- 文字生成.exe可以生成相应的文字数组
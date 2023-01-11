# Day01

## 一. Markdown语法：

### 1. 标题：

># 标题：#（空格）内容
>## 二级标题：##
>### 三级：###
>#### 四级：####
>...

### 2. 字体：

>**粗体：**两边**  （Ctrl+B）
>*斜体：* 两边* （Ctrl+I）
>***粗斜：***** ** 
>~~删除线~~:~~ ~~

### 3. 引用：

> （英）》

### 4. 分割线:

>三个"--"
>***
>三个"*"
>***

### 5. 图片:

>![微信图片_20220629151803](C:\Users\86198\Pictures\Saved Pictures\微信图片_20220629151803.jpg)

>![名字] (地址)
>地址：本地路径/在线地址

### 6. 超链接:

> [[名字] (网址）](https://editor.csdn.net/md?not_checkout=1&articleId=127622288)

### 7. 列表:

>有序列表：1. 加空格
>无序列表：- 加空格

### 8. 表格:

| 学院       | 班级 | 姓名 |
| ---------- | ---- | ---- |
| 计算机学院 | 17   | 某人 |

实现方式：
***
学院|班级|姓名

--|--|--

计算机学院|17|某人
***

### 9. 代码:

> 三个"`"加编程语言

```c
#include <stdio.h>
int main()
{
	printf("你好吖");
	return 0;
}
```

## 二. github仓库与git

### 1. 上传步骤:

1. 下载git；

2. 在项目根目录下右键打开Git Bash

3. 输入git init创建空仓库（在根目录创建.git隐藏文件夹）；

4. 输入touch .gitignore创建gitignore文件，编辑要忽略的文件（注意：文件夹采用/文件夹名/，文件采用.文件格式）；
   输入touch readme.md创建readme.md文件用于介绍；(非必须);

5. 输入git add .将非忽略文件添加到索引区；

6. 输入git status查看索引区情况（非必须）；

7. 输入git commit -m “提交信息”,暂存区中的所有文件添加到本地仓库;

8. . 输入git remote add demo https://github.com/ghs2022/demo.git，其中demo为远程仓库名，网址为远程仓库网址，用于配置远程仓库；

9. 输入git push -u demo “master”，将本地仓库推送到远程仓库；

   > ![img](https://www.runoob.com/wp-content/uploads/2014/05/trees.png)

### 2. 分支:

1. 创建一个叫做"feature_x"的分支，并切换过去：
   `git checkout -b feature_x`

2. 切换回主分支：
   `git checkout master`

3. 再把新建的分支删掉：
   `git branch -d feature_x`

4. 除非你将分支推送到远端仓库，不然该分支就是 *不为他人所见的*：
   `git push origin <branch>`

   > ![img](https://www.runoob.com/wp-content/uploads/2014/05/branches.png)

### 3. 更新与合并：

1. 要更新你的本地仓库至最新改动，执行：
   `git pull`
   以在你的工作目录中 *获取（fetch）* 并 *合并（merge）* 远端的改动。
2. 要合并其他分支到你的当前分支（例如 master），执行：
   `git merge <branch>`
3. 在这两种情况下，git 都会尝试去自动合并改动。遗憾的是，这可能并非每次都成功，并可能出现*冲突（conflicts）*。 这时候就需要你修改这些文件来手动合并这些*冲突（conflicts）*。改完之后，你需要执行如下命令以将它们标记为合并成功：
   `git add <filename>`
4. 在合并改动之前，你可以使用如下命令预览差异：
   `git diff <source_branch> <target_branch>`

### 4. 标签：

1. 执行如下命令创建一个叫做 *1.0.0* 的标签：
   `git tag 1.0.0 1b2e1d63ff`
2. *1b2e1d63ff* 是你想要标记的提交 ID 的前 10 位字符。可以使用下列命令获取提交 ID：
   `git log`
   你也可以使用少一点的提交 ID 前几位，只要它的指向具有唯一性

### 5. 替换本地改动：

1. 使用如下命令替换掉本地改动：
   `git checkout -- <filename>`

   此命令会使用 HEAD 中的最新内容替换掉你的工作目录中的文件。已添加到暂存区的改动以及新文件都不会受到影响

2. 假如你想丢弃你在本地的所有改动与提交，可以到服务器上获取最新的版本历史，并将你本地主分支指向它：
   `git fetch origin`
   `git reset --hard origin/master`

### 6. 其他：

1. 内建的图形化 git：
   `gitk`
2. 彩色的 git 输出：
   `git config color.ui true`
3. 显示历史记录时，每个提交的信息只显示一行：
   `git config format.pretty oneline`
4. 交互式添加文件到暂存区：
   `git add -i`

## 三. 51单片机学习

### 1. 点亮LED：

1. 代码：

   ```c
   #include <REGX52.H>
   
   void main()
   {
   	P2=0xFE;
   }
   ```

2. 开发板上电阻数字表示：

   数字+尾数（代表后接几个零）

   eg. 102-  >  1000  ->1kΩ

### 2. LED闪烁：

1. 代码：

   ```c
   #include <REGX52.H>
   #include <INTRINS.H>
   void Delay500ms()		//@12.000MHz
   {
   	unsigned char i, j, k;
   
   	_nop_();
   	i = 4;
   	j = 205;
   	k = 187;
   	do
   	{
   		do
   		{
   			while (--k);
   		} while (--j);
   	} while (--i);
   }
   
   
   int main()
   {
   	while(1)
   	{
   		P2=0xFE;
   		Delay500ms();
   		P2=0xFF;
   		Delay500ms();
   	}
   }
   ```

### 3. LED流水灯：

1. 代码：

   ```c
   #include <REGX52.H>
   #include <INTRINS.H>
   
   void Delay1ms(unsigned int xms)		//@12.000MHz
   {
   	unsigned char i, j;
   	while(xms)
   	{
   		i = 2;
   		j = 239;
   		do
   		{
   			while (--j);
   		} while (--i);
   		xms--;
   	}
   }
   
   void main()
   {
   	while(1)
   	{
   		P2=0xFE;
   		Delay1ms(500);
   		P2=0xFD;
   		Delay1ms(500);
   		P2=0xFB;
   		Delay1ms(500);
   		P2=0xF7;
   		Delay1ms(500);
   		P2=0xEF;
   		Delay1ms(500);
   		P2=0xDE;
   		Delay1ms(500);
   		P2=0xBE;
   		Delay1ms(500);
   		P2=0x7E;
   		Delay1ms(500);
   	}
   }
   ```

### 4. 独立按键控制LED亮灭：

1. 代码：

   ```c
   #include <REGX52.H>
   void main()
   {
   	P2_0=1;
   	while(1)
   	{
   		if(P3_1==0)
   			P2_0=0;
   		else
   			P2_0=1;
   	}
   }
   ```

### 5. 静态数码管：

1. 代码：

   ```c
   #include <REGX52.H>
   
   unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0x00};
   void Nixie(unsigned char Location,Number)
   {
   	switch(Location)
   	{
   		case 1:P2_4=1;P2_3=1;P2_2=1;break;
   		case 2:P2_4=1;P2_3=1;P2_2=0;break;
   		case 3:P2_4=1;P2_3=0;P2_2=1;break;
   		case 4:P2_4=1;P2_3=0;P2_2=0;break;
   		case 5:P2_4=0;P2_3=1;P2_2=1;break;
   		case 6:P2_4=0;P2_3=1;P2_2=0;break;
   		case 7:P2_4=0;P2_3=0;P2_2=1;break;
   		case 8:P2_4=0;P2_3=0;P2_2=0;break;
   	}
   	P0=NixieTable[Number];
   }
   void main()
   {
   	Nixie(5,11);
   	while(1);
   }
   ```

2. 74LS138作用：

   将八个引脚减少至三个引脚；

   

![image-20230110134719852](C:\Users\86198\AppData\Roaming\Typora\typora-user-images\image-20230110134719852.png)

3. 74HC245：双向数据缓冲器

   ![image-20230110134836072](C:\Users\86198\AppData\Roaming\Typora\typora-user-images\image-20230110134836072.png)

### 6. 动态数码管：

1. 代码：

   ```c
   #include <REGX52.H>
   
   void Delay(unsigned int xms)		//@12.000MHz
   {
   	unsigned char i, j;
   	while(xms--)
   	{
   		i = 2;
   		j = 239;
   		do
   		{
   			while (--j);
   		} while (--i);
   	}
   }
   
   unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0x00};
   void Nixie(unsigned char Location,Number)
   {
   	switch(Location)
   	{
   		case 1:P2_4=1;P2_3=1;P2_2=1;break;
   		case 2:P2_4=1;P2_3=1;P2_2=0;break;
   		case 3:P2_4=1;P2_3=0;P2_2=1;break;
   		case 4:P2_4=1;P2_3=0;P2_2=0;break;
   		case 5:P2_4=0;P2_3=1;P2_2=1;break;
   		case 6:P2_4=0;P2_3=1;P2_2=0;break;
   		case 7:P2_4=0;P2_3=0;P2_2=1;break;
   		case 8:P2_4=0;P2_3=0;P2_2=0;break;
   	}
   	P0=NixieTable[Number];
   	Delay(1);
   }
   void main()
   {
   	while(1)
   	{
   		Nixie(1,1);
   		Nixie(2,2);
   		Nixie(3,3);
   	}
   }
   ```

2. 残影问题：

   - 原因：位选 段选 位选 段选 切换过程中数据会串到下一位
   - 解决：中间用Delay函数延迟1ms；

3. 数码管驱动方式：

   ![image-20230110135416851](C:\Users\86198\AppData\Roaming\Typora\typora-user-images\image-20230110135416851.png)

### 7.学习使用矩阵键盘：

1. 矩阵键盘介绍：

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

2. 矩阵键盘程序编写：

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

3. 矩阵键盘密码锁：

   1. 程序代码：

      ```c
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
      注：因为是重新回头来记笔记所以有点简陋:)

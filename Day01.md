# Day01

## 一. Markdown语法：

### 1.标题：

># 标题：#（空格）内容
>## 二级标题：##
>### 三级：###
>#### 四级：####
>...

### 2.字体：

>**粗体：**两边**  （Ctrl+B）
>*斜体：* 两边* （Ctrl+I）
>***粗斜：***** ** 
>~~删除线~~:~~ ~~

### 3.引用：

> （英）》

### 4.分割线:

>三个"--"
>***
>三个"*"
>***

### 5.图片:

>![微信图片_20220629151803](C:\Users\86198\Pictures\Saved Pictures\微信图片_20220629151803.jpg)

>![名字] (地址)
>地址：本地路径/在线地址

### 6.超链接:

> [[名字] (网址）](https://editor.csdn.net/md?not_checkout=1&articleId=127622288)

### 7.列表:

>有序列表：1. 加空格
>无序列表：- 加空格

### 8.表格:

| 学院       | 班级 | 姓名 |
| ---------- | ---- | ---- |
| 计算机学院 | 17   | 某人 |

实现方式：
***
学院|班级|姓名

--|--|--

计算机学院|17|某人
***

### 9.代码:

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

### 1.上传步骤:

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

### 2.更新步骤:

1. 
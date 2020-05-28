/*
WARNING: We've only compiled it for Windows.
*/
/*
MIT License

Copyright (c) 2020 FLY code studio

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
/*
WARNING: We've only compiled it for Windows.
小学生加减法出题程序
...................版本0.2 
版本0.2的更新：
	修复了提示信息后加负号不能正确返回提示的bug;
	修复了退出答题没有清屏的bug.
	改进了超长的退格代码。用函数实现退格。 
	
特色：
     题目和结果不超过三位数；
	 支持按键实时监测操作；  
	 键入数字时，**实时错误提示** ； 
	 统计和显示用户一次测试的做题情况。 

*/

# include <stdio.h> 
# include <time.h>
# include <stdlib.h>
# define ADD '+'
# define SUB '-'
# define OUTCODE 1000

//运算单元，题目以此为基础。每一题就是一个单元 
typedef struct calcUnit
{
	int A;	
	int B;
	char SYMBLE;
} CU;

void backSpace(int i)
{
	int j;
	for(j = 0; j < i; j++)
	{
		printf("\b");
	}
	for(j = 0; j < i; j++)
	{
		printf(" ");
	}
	for(j = 0; j < i; j++)
	{
		printf("\b");
	}
}
//创建一个运算单元 
CU randomCreateCU()
{
	CU cu;
	int temp;
	srand(time(NULL));
	temp = rand()%100;
	if(temp >= 50)
	{
		cu.SYMBLE = ADD;
	}
	else
	{
		cu.SYMBLE = SUB;
	}
	cu.A = rand()%1000;
	cu.B = rand()%1000;
	
	//保证A，B, A +/- B不超过三位数 
	if(cu.SYMBLE == ADD)
	{
		if(cu.A + cu.B >= 1000)
		{
			cu.A /= 10;
			cu.B /= 10;
		}
	}
	else
	{
		if(cu.A - cu.B <= -1000)
		{
			cu.A /= 10;
			cu.B /= 10;
		}
	}
	return cu; 
}

void showMenuFace(void)
{
	printf("\
\n\
\n\
\n\
               小学生加减法出题程序 \n\
                                版本 0.2\n\
\n\
\n\
           =============菜 单===========\n\
\n\
\n\
                   Enter 开始测试\n\
                   Esc   退出程序\n\
");
	return;
}

void showTestMessage(int rightNum, int wrongNum, CU cu)
{
	printf("\n\
             **您现在正在进行测试!**\n\
   [已作答:%4d;正确:%4d;错误:%4d;准确率:%3d%%]\n\
    PROMPT: NumKeys=Write Esc=Esc Enter=CONFIRM\n\
    ===========================================\n\
\n\
         题  目：\n\
\n\
\n\
\n\
                   %3d %c %-3d =  ? \n\
\n\
\n\
\n\
\n\
    ===========================================\n\
\n\
         回答区：\n\
                    \
", rightNum + wrongNum, rightNum, wrongNum, (rightNum + wrongNum)==0?0:(int)(1.0*rightNum/(rightNum + wrongNum)*100), cu.A, cu.SYMBLE, cu.B);
	return;
}
void outputScore(FILE * fp, int T, int F)
{
	fprintf(fp, "\
\n\
\n\
\n\
   =================== 您 的 成 绩 ===================\n\
\n\
\n\
                   已作答:       %4d\n\
\n\
                     正确:       %4d\n\
                     错误:       %4d\n\
\n\
                   正确率:       %3d%% \n\
\n\
   ===================================================\n\
", T + F, T, F, (T + F)==0?0:(int)(1.0*T/(T + F)*100));
	system("pause");
	return;
}
int getUserAnswer()
{
	int isMessage = 0;//检测输入是否处于提示状态 
	int numLen = 0;
	int ans = 0;
	int isNegative = 0;
	while(1)
	{
		char c = getch(); 
		if(c >='0' && c <= '9' && numLen < 3)		//合法的输入！
		{
			if(isMessage)
			{
				isMessage = 0;
				backSpace(18);//清除额外信息的显示
			}
			numLen++;
			ans = ans *10 + (c-'0');
			putchar(c);
		}
		else if(c == '-' && numLen == 0 && isNegative == 0)			//负数支持！ 
		{
			if(isMessage)
			{
				isMessage = 0;
				backSpace(18);//清除额外信息的显示 
				continue;
			}
			isNegative = 1;
			printf("-"); 
		}
		else if(c == '\b')											//退格 
		{
			if(isMessage)
			{
				isMessage = 0;
				backSpace(18);//清除额外信息的显示 
				continue;
			}
			
			if(numLen == 0 && isNegative == 1)		//没有数字，用户想撤销最前面的减号 
			{
				printf("\b \b"); 
				isNegative = 0; 
			}
			else if(numLen == 0&& isNegative == 0)	//没有可以退格的数字 
			{
				continue;
			}
			else
			{
				printf("\b \b"); 
				numLen--;
				ans /= 10;
			}
		}
		else if(c == 13)							// 回车确认！ 
		{
			break;
		}
		else if(c ==27)//退出命令！ 
		{
			printf("要确定退出，请再次按一下 \"Esc\" 键。");
			c = getch();
			if(c == 27)//用户确定要退出了！ 
			{
				system("cls");
				
				ans = OUTCODE;
				break;
			}
			else//亲爱的用户又反悔了！
			{
				backSpace(35);//清除提示 
				continue;
			}
		} 
		else if(numLen == 3 && (c >= '0'&& c <= '9'))//数字太长！
		{
			if(isMessage)
			{
				backSpace(18);//清除额外信息的显示 
			} 
			isMessage = 1;
			printf("答案最多只有三位。");
		} 
		else										//奇怪的输入！ 
		{
			if(isMessage)
			{
				backSpace(18);//清除额外信息的显示
			}
			isMessage = 1;
			printf("这不是合法的按键。");
		}
	}
	if(isNegative == 1)
	{
		return -1*ans;
	}
	else
	{
		return ans;
	}
	
}
void runTest()
{
	CU cu;
	int rightNum = 0;
	int wrongNum = 0;
	int ans = 0;
	
	while(1)
	{
		system("cls");
		cu = randomCreateCU();
		showTestMessage(rightNum, wrongNum, cu);
		//非常人性化的获取用户的答案,相关繁琐细节在函数内 
		ans = getUserAnswer();
		if(ans == OUTCODE)
		{
			outputScore(stdout, rightNum, wrongNum);
			break; //直接返回 
		}
		else
		{
			if(cu.SYMBLE == ADD)			//是加法运算 ！ 
			{
				if(cu.A + cu.B == ans)
				{
					rightNum++;//用户计算正确！ 
				}
				else
				{
					wrongNum++;//用户计算错误！
				}
			}
			else if(cu.SYMBLE == SUB)		//是减法运算 ！ 
			{
				if(cu.A - cu.B == ans)
				{
					rightNum++;//用户计算正确！ 
				}
				else
				{
					wrongNum++;//用户计算错误！
				}
			}
		}//if 
	}//while(1)
} 

int before_message_and_run()
{
	system("cls"); 
	printf("\
\n\
------------------------------------------------------------\n\
提示：\n\
    按 数字键 键入结果; 按Esc退出程序。\n\
    如果结果是负数，请在前面加上一个减号\"-\"作为负号。\n\
    结果的值不超过三位数。\n\
------------------------------------------------------------\n\
");
	system("pause");
	runTest();
} 

void START()
{
	int c;
	while(1)
	{
		system("cls"); 
		showMenuFace();
		c = getch();
		switch(c)
		{
			case 13:
				before_message_and_run();
				break;
			case 27:
				printf("要确定退出，请再次按一下 \"Esc\" 键。");
				c = getch();
				if(c == 27)//用户确定退出
				{
					system("cls");
					return;
				}
				else//用户反悔了
				{
					backSpace(35);//清除提示 
					continue;
				}
			default:
				system("cls");
		}
	}
} 

int main (void)
{
	START();
	return 0;
}

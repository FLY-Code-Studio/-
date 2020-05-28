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
Сѧ���Ӽ����������
...................�汾0.2 
�汾0.2�ĸ��£�
	�޸�����ʾ��Ϣ��Ӹ��Ų�����ȷ������ʾ��bug;
	�޸����˳�����û��������bug.
	�Ľ��˳������˸���롣�ú���ʵ���˸� 
	
��ɫ��
     ��Ŀ�ͽ����������λ����
	 ֧�ְ���ʵʱ��������  
	 ��������ʱ��**ʵʱ������ʾ** �� 
	 ͳ�ƺ���ʾ�û�һ�β��Ե���������� 

*/

# include <stdio.h> 
# include <time.h>
# include <stdlib.h>
# define ADD '+'
# define SUB '-'
# define OUTCODE 1000

//���㵥Ԫ����Ŀ�Դ�Ϊ������ÿһ�����һ����Ԫ 
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
//����һ�����㵥Ԫ 
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
	
	//��֤A��B, A +/- B��������λ�� 
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
               Сѧ���Ӽ���������� \n\
                                �汾 0.2\n\
\n\
\n\
           =============�� ��===========\n\
\n\
\n\
                   Enter ��ʼ����\n\
                   Esc   �˳�����\n\
");
	return;
}

void showTestMessage(int rightNum, int wrongNum, CU cu)
{
	printf("\n\
             **���������ڽ��в���!**\n\
   [������:%4d;��ȷ:%4d;����:%4d;׼ȷ��:%3d%%]\n\
    PROMPT: NumKeys=Write Esc=Esc Enter=CONFIRM\n\
    ===========================================\n\
\n\
         ��  Ŀ��\n\
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
         �ش�����\n\
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
   =================== �� �� �� �� ===================\n\
\n\
\n\
                   ������:       %4d\n\
\n\
                     ��ȷ:       %4d\n\
                     ����:       %4d\n\
\n\
                   ��ȷ��:       %3d%% \n\
\n\
   ===================================================\n\
", T + F, T, F, (T + F)==0?0:(int)(1.0*T/(T + F)*100));
	system("pause");
	return;
}
int getUserAnswer()
{
	int isMessage = 0;//��������Ƿ�����ʾ״̬ 
	int numLen = 0;
	int ans = 0;
	int isNegative = 0;
	while(1)
	{
		char c = getch(); 
		if(c >='0' && c <= '9' && numLen < 3)		//�Ϸ������룡
		{
			if(isMessage)
			{
				isMessage = 0;
				backSpace(18);//���������Ϣ����ʾ
			}
			numLen++;
			ans = ans *10 + (c-'0');
			putchar(c);
		}
		else if(c == '-' && numLen == 0 && isNegative == 0)			//����֧�֣� 
		{
			if(isMessage)
			{
				isMessage = 0;
				backSpace(18);//���������Ϣ����ʾ 
				continue;
			}
			isNegative = 1;
			printf("-"); 
		}
		else if(c == '\b')											//�˸� 
		{
			if(isMessage)
			{
				isMessage = 0;
				backSpace(18);//���������Ϣ����ʾ 
				continue;
			}
			
			if(numLen == 0 && isNegative == 1)		//û�����֣��û��볷����ǰ��ļ��� 
			{
				printf("\b \b"); 
				isNegative = 0; 
			}
			else if(numLen == 0&& isNegative == 0)	//û�п����˸������ 
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
		else if(c == 13)							// �س�ȷ�ϣ� 
		{
			break;
		}
		else if(c ==27)//�˳���� 
		{
			printf("Ҫȷ���˳������ٴΰ�һ�� \"Esc\" ����");
			c = getch();
			if(c == 27)//�û�ȷ��Ҫ�˳��ˣ� 
			{
				system("cls");
				
				ans = OUTCODE;
				break;
			}
			else//�װ����û��ַ����ˣ�
			{
				backSpace(35);//�����ʾ 
				continue;
			}
		} 
		else if(numLen == 3 && (c >= '0'&& c <= '9'))//����̫����
		{
			if(isMessage)
			{
				backSpace(18);//���������Ϣ����ʾ 
			} 
			isMessage = 1;
			printf("�����ֻ����λ��");
		} 
		else										//��ֵ����룡 
		{
			if(isMessage)
			{
				backSpace(18);//���������Ϣ����ʾ
			}
			isMessage = 1;
			printf("�ⲻ�ǺϷ��İ�����");
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
		//�ǳ����Ի��Ļ�ȡ�û��Ĵ�,��ط���ϸ���ں����� 
		ans = getUserAnswer();
		if(ans == OUTCODE)
		{
			outputScore(stdout, rightNum, wrongNum);
			break; //ֱ�ӷ��� 
		}
		else
		{
			if(cu.SYMBLE == ADD)			//�Ǽӷ����� �� 
			{
				if(cu.A + cu.B == ans)
				{
					rightNum++;//�û�������ȷ�� 
				}
				else
				{
					wrongNum++;//�û��������
				}
			}
			else if(cu.SYMBLE == SUB)		//�Ǽ������� �� 
			{
				if(cu.A - cu.B == ans)
				{
					rightNum++;//�û�������ȷ�� 
				}
				else
				{
					wrongNum++;//�û��������
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
��ʾ��\n\
    �� ���ּ� ������; ��Esc�˳�����\n\
    �������Ǹ���������ǰ�����һ������\"-\"��Ϊ���š�\n\
    �����ֵ��������λ����\n\
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
				printf("Ҫȷ���˳������ٴΰ�һ�� \"Esc\" ����");
				c = getch();
				if(c == 27)//�û�ȷ���˳�
				{
					system("cls");
					return;
				}
				else//�û�������
				{
					backSpace(35);//�����ʾ 
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

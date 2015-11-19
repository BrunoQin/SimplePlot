#pragma once
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <cmath>
struct node
{
	int find;
	double num;
	char sign;
};
node all[200];//后缀表达式栈 
using namespace std;
double calculate(double nowX, char cal[300], int length)
{
	char sign1[200];
	double finalNum[200];

	int zzAll;//后缀表达式栈指针 
	int zzChar;//运算符栈指针 
	int zzFinal;//计算后缀表达式的数栈 
	int testNum;// 检测当前数字是否多位 
	int testPoint;
	int countPoint;
	int testCorrect;
	char nowSign;

	zzAll = 0;
	zzChar = 0;
	zzFinal = 0;
	testNum = 0;
	testPoint = 0;
	countPoint = 0;
	testCorrect = 1;
	for (int i = 0; i<length - 1; i++)

	{

		nowSign = cal[i];


		if (nowSign != '\n')
		{
			if (nowSign - '0' >= 0 && nowSign - '0' <= 9)
			{
				if (testNum == 0 && testPoint == 0)
				{
					all[zzAll].find = 1;
					all[zzAll].num = nowSign - '0';
					zzAll++;
					testNum = 1;
				}
				else
				{
					if (testNum)all[zzAll - 1].num = all[zzAll - 1].num * 10 + nowSign - '0';
					else
					{
						if (testPoint == 1)
						{
							all[zzAll - 1].num = all[zzAll - 1].num + pow(10, -countPoint)*(nowSign - '0');
							countPoint++;
						}
						else
						{
							testCorrect = 0;
							return -999999997;
						}
					}
				}

			}
			else if (nowSign == 'x')
			{
				all[zzAll].find = 1;
				all[zzAll].num = nowX;
				zzAll++;
				testNum = 0;
				testPoint = 0;
				countPoint = 0;
			}
			else if (nowSign == '.')
			{
				testPoint++;
				countPoint = 1;
				testNum = 0;
			}


			else
			{

				testNum = 0;
				testPoint = 0;
				countPoint = 0;
				if (zzChar == 0 && (nowSign == '+' || nowSign == '-' || nowSign == '*' || nowSign == '/' || nowSign == '^' || nowSign == 'l' || nowSign == 'a' || nowSign == 's' || nowSign == 'c'))
				{


					sign1[0] = nowSign;
					zzChar++;
					if (nowSign == 'l' || nowSign == 'a' || nowSign == 's' || nowSign == 'c')i = i + 2;


				}
				else
				{
					if (nowSign == '^')
					{
						/*while(sign1[zzChar-1]=='^')
						{
						all[zzAll].find=0;
						all[zzAll].sign=sign1[zzChar-1];
						zzChar--;
						zzAll++;
						}*/
						sign1[zzChar] = nowSign;
						zzChar++;
					}
					else if (nowSign == '*' || nowSign == '/')
					{
						while (sign1[zzChar - 1] == '^' || sign1[zzChar - 1] == '*' || sign1[zzChar - 1] == '/' || sign1[zzChar - 1] == 'l' || sign1[zzChar - 1] == 'a' || sign1[zzChar - 1] == 's' || sign1[zzChar - 1] == 'c')//运算符高者出栈 
						{
							all[zzAll].find = 0;
							all[zzAll].sign = sign1[zzChar - 1];
							zzChar--;
							zzAll++;
						}
						sign1[zzChar] = nowSign;
						zzChar++;
					}
					else if (nowSign == '+' || nowSign == '-')
					{

						while (sign1[zzChar - 1] == '^' || sign1[zzChar - 1] == '*' || sign1[zzChar - 1] == '/' || sign1[zzChar - 1] == '+' || sign1[zzChar - 1] == '-' || sign1[zzChar - 1] == 'l' || sign1[zzChar - 1] == 'a' || sign1[zzChar - 1] == 's' || sign1[zzChar - 1] == 'c')
						{
							all[zzAll].find = 0;
							all[zzAll].sign = sign1[zzChar - 1];
							zzChar--;
							zzAll++;
						}
						sign1[zzChar] = nowSign;
						zzChar++;

					}
					else if (nowSign == 'l')
					{

						i = i + 2;
						/*while(sign1[zzChar-1]=='^')
						{
						all[zzAll].find=0;
						all[zzAll].sign=sign1[zzChar-1];
						zzChar--;
						zzAll++;
						}*/
						sign1[zzChar] = nowSign;
						zzChar++;
					}
					else if (nowSign == 'a')
					{
						i = i + 2;
						/*while(sign1[zzChar-1]=='^')
						{
						all[zzAll].find=0;
						all[zzAll].sign=sign1[zzChar-1];
						zzChar--;
						zzAll++;
						}*/
						sign1[zzChar] = nowSign;
						zzChar++;
					}
					else if (nowSign == 's')
					{
						i = i + 2;

						/*while(sign1[zzChar-1]=='^')
						{
						all[zzAll].find=0;
						all[zzAll].sign=sign1[zzChar-1];
						zzChar--;
						zzAll++;
						}*/
						sign1[zzChar] = nowSign;
						zzChar++;
					}
					else if (nowSign == 'c')
					{
						i = i + 2;

						/*while(sign1[zzChar-1]=='^')
						{
						all[zzAll].find=0;
						all[zzAll].sign=sign1[zzChar-1];
						zzChar--;
						zzAll++;
						}*/
						sign1[zzChar] = nowSign;
						zzChar++;
					}

					else if (nowSign == '(')
					{
						sign1[zzChar] = nowSign;
						zzChar++;

					}
					else if (nowSign == ')')
					{
						while (sign1[zzChar - 1] != '(')
						{
							all[zzAll].find = 0;
							all[zzAll].sign = sign1[zzChar - 1];
							zzChar--;
							zzAll++;
							if (zzChar <= 0)
							{
								testCorrect = 0;
								return -999999999;
							}
						}
						zzChar--;
					}
					else
					{
						testCorrect = 0;
						return -999999998;

					}




				}



			}

		}

	}
	//算式读完多余运算符出栈 
	while (zzChar&&testCorrect)
	{
		if (sign1[zzChar - 1] != '(')
		{
			all[zzAll].find = 0;
			all[zzAll].sign = sign1[zzChar - 1];
			zzChar--;
			zzAll++;
		}
		else
		{
			testCorrect = 0;
			return -999999999;
		}
	}
	//后缀表达式计算 
	for (int i = 0; i<zzAll; i++)
	{
		if (all[i].find)
		{
			finalNum[zzFinal] = all[i].num;
			zzFinal++;
		}
		else
		{
			if (all[i].sign == '^')
			{
				finalNum[zzFinal - 2] = pow(finalNum[zzFinal - 2], finalNum[zzFinal - 1]);
				zzFinal = zzFinal - 1;
			}
			if (all[i].sign == '*')
			{
				finalNum[zzFinal - 2] = finalNum[zzFinal - 2] * finalNum[zzFinal - 1];
				zzFinal = zzFinal - 1;
			}
			if (all[i].sign == '/')
			{
				finalNum[zzFinal - 2] = finalNum[zzFinal - 2] / finalNum[zzFinal - 1];
				zzFinal = zzFinal - 1;
			}
			if (all[i].sign == '+')
			{
				finalNum[zzFinal - 2] = finalNum[zzFinal - 2] + finalNum[zzFinal - 1];
				zzFinal = zzFinal - 1;
			}
			if (all[i].sign == '-')
			{
				if (zzFinal >= 2)
				{
					finalNum[zzFinal - 2] = finalNum[zzFinal - 2] - finalNum[zzFinal - 1];
					zzFinal = zzFinal - 1;
				}
				else finalNum[zzFinal - 1] = -finalNum[zzFinal - 1];

			}
			if (all[i].sign == 'l')finalNum[zzFinal - 1] = log2(finalNum[zzFinal - 1]);
			if (all[i].sign == 'a')finalNum[zzFinal - 1] = abs(finalNum[zzFinal - 1]);
			if (all[i].sign == 's')finalNum[zzFinal - 1] = sin(finalNum[zzFinal - 1]);
			if (all[i].sign == 'c')finalNum[zzFinal - 1] = cos(finalNum[zzFinal - 1]);
		}
	}
	return finalNum[0];

}
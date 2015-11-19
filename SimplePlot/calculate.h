#include<map>
#include<cmath>
#include<set>
#include<string>
#include "stack.h"
#include "stack_num.h"
using namespace std;

class calculate {
private:
	string str;
	char ch;
	char pre_op;
	char next_num;
	map<char, int> opera;
	set<char> operation;
	set<char> number;
	stack_num *num ;
	stack *op ;
public:
	calculate()
	{
		num = new stack_num();
		op = new stack();
		number.insert('0');
		number.insert('1');
		number.insert('2');
		number.insert('3');
		number.insert('4');
		number.insert('5');
		number.insert('6');
		number.insert('7');
		number.insert('8');
		number.insert('9');
		number.insert('p');
		number.insert('e');
		number.insert('x');
		number.insert('.');
		operation.insert('+');
		operation.insert('-');
		operation.insert('*');
		operation.insert('^');
		operation.insert('/');
		operation.insert('S');
		operation.insert('C');
		operation.insert('T');
		operation.insert('Q');
		operation.insert('G');
		operation.insert('F');
		operation.insert('L');
		operation.insert('(');
		operation.insert(')');
		operation.insert('#');
		opera.insert(pair<char, int>('+', 1));
		opera.insert(pair<char, int>('-', 1));
		opera.insert(pair<char, int>('*', 2));
		opera.insert(pair<char, int>('/', 2));
		opera.insert(pair<char, int>('^', 4));
		opera.insert(pair<char, int>('S', 3));
		opera.insert(pair<char, int>('C', 3));
		opera.insert(pair<char, int>('T', 3));
		opera.insert(pair<char, int>('L', 3));
		opera.insert(pair<char, int>('Q', 3));
		opera.insert(pair<char, int>('F', 3));
		opera.insert(pair<char, int>('G', 3));
		opera.insert(pair<char, int>('(', 8));
		opera.insert(pair<char, int>('#', 0));
		opera.insert(pair<char, int>(')', 0));
	}
	double cal(string str, double x)
	{
		str[str.length()] = '#';
		for (int i = 0;i < str.length();i++)
		{
			float ans;
			ch = str[i];
			if (number.find(ch) != number.end())
			{
				if (ch == 'p')
				{
					ans = 3.1415;
					i++;
					ch = str[i];
				}
				else if (ch == 'e')
				{
					ans = 2.73;
					i++;
					ch = str[i];
				}
				else if (ch == 'x')
				{
					ans = x;
					i++;
					ch = str[i];
				}
				else
				{
					ans = ch - 48;
					int index = 1;
					int _index = 1;
					i++;
					next_num = str[i];
					while (number.find(next_num) != number.end())
					{
						float next_ans = next_num - 48;
						if (next_num != '.')
						{
							for (int k = 1;k <= index;k++)
								ans = ans * 10;
							ans = ans + next_ans;
							index++;
							i++;
							next_num = str[i];
						}
						else
						{
							i++;
							next_num = str[i];

							while (number.find(next_num) != number.end())
							{
								float next_ans = next_num - 48;
								for (int k = 1;k <= _index;k++)
									next_ans = next_ans / 10;
								ans = ans + next_ans;
								_index++;
								i++;
								next_num = str[i];
							}
						}
					}
					ch = next_num;
				}
				num->push(ans);
			}

			if (operation.find(ch) != operation.end())
			{
				if (op->isEmpty())
					op->push(ch);
				else if(!op->isEmpty())
				{
					bool isblanket = false;
					pre_op = op->peek();
					while (opera[ch] < opera[pre_op] || opera[ch] == opera[pre_op] == 2)
					{
						if (pre_op == '(')
						{
							if (ch == ')')
							{
								op->pop();
								pre_op = op->peek();
								//break;
							}
							else{
								isblanket = true;
								op->push(ch);
								break;
							}

						}
						else if (pre_op == '+')
						{
							float a = num->pop();
							float b = num->pop();
							num->push(b + a);
							op->pop();
							if (!op->isEmpty())
							{
								pre_op = op->peek();
							}
							else
							{
								break;
							}
						}
						else if (pre_op == '-')
						{
							float a = num->pop();
							float b = num->pop();
							num->push(b - a);
							op->pop();
							if (!op->isEmpty())
							{
								pre_op = op->peek();
							}
							else
							{
								break;
							}
						}
						else if (pre_op == '*')
						{
							float a = num->pop();
							float b = num->pop();
							num->push(b * a);
							op->pop();
							if (!op->isEmpty())
							{
								pre_op = op->peek();
							}
							else
							{
								break;
							}
						}
						else if (pre_op == '/')
						{
							float a = num->pop();
							if (a == 0)
							{
								cout << "error" << endl;
								return 0;
							}
							float b = num->pop();
							float f = b / a;
							f = ((float)((int)(f * 100))) / 100;
							num->push(f);
							op->pop();
							if (!op->isEmpty())
							{
								pre_op = op->peek();
							}
							else
							{
								break;
							}
						}
						else if (pre_op == '^')
						{
							float a = num->pop();
							float b = num->pop();
							num->push(pow(b, a));
							op->pop();
							if (!op->isEmpty())
							{
								pre_op = op->peek();
							}
							else
							{
								break;
							}
						}
						else if (pre_op == 'T')
						{
							float a = num->pop();
							num->push(tan(a));
							op->pop();
							if (!op->isEmpty())
							{
								pre_op = op->peek();
							}
							else
							{
								break;
							}
						}
						else if (pre_op == 'S')
						{
							float a = num->pop();
							num->push(sin(a));
							op->pop();
							if (!op->isEmpty())
							{
								pre_op = op->peek();
							}
							else
							{
								break;
							}
						}
						else if (pre_op == 'C')
						{
							float a = num->pop();
							num->push(cos(a));
							op->pop();
							if (!op->isEmpty())
							{
								pre_op = op->peek();
							}
							else
							{
								break;
							}
						}
						else if (pre_op == 'L')
						{
							float a = num->pop();
							num->push(log((long double)a));
							op->pop();
							if (!op->isEmpty())
							{
								pre_op = op->peek();
							}
							else
							{
								break;
							}
						}
						else if (pre_op == 'F')
						{
							float a = num->pop();
							num->push(-a);
							op->pop();
							if (!op->isEmpty())
							{
								pre_op = op->peek();
							}
							else
							{
								break;
							}
						}
						else if (pre_op == 'Q')
						{
							float a = num->pop();
							num->push(sqrt(a));
							op->pop();
							if (!op->isEmpty())
							{
								pre_op = op->peek();
							}
							else
							{
								break;
							}
						}
						else if (pre_op == 'G')
						{
							float a = num->pop();
							float b = num->pop();
							num->push((log10((long double)a)) / (log10((long double)b)));
							op->pop();
							if (!op->isEmpty())
							{
								pre_op = op->peek();
							}
							else
							{
								break;
							}
						}

					}//while·ûºÅÍËÕ»
					if (ch != ')'&&isblanket == false)
					{
						op->push(ch);
					}

				}//else if (!op->isEmpty())
			}
			else
			{
				cout << "char error: " << str[i] << endl;
			}
		}
		return num->peek();
	}
};
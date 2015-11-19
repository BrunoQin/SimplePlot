#pragma once
#include<iostream>
class stack_num {
private:
	float stacklist[100];
	int top;
public:
	stack_num(void)
	{
		this->top = -1;
	}
	~stack_num(void)
	{
		this->top = -1;
	}
	void push(const float &item)
	{
		if (!isFull())
		{
			top += 1;
			this->stacklist[top] = item;
		}
		else
			std::cout << "Out of the Stack" << std::endl;
	}
	float pop(void)
	{
		if (!isEmpty())
		{
			int ebp = top;
			top -= 1;
			return stacklist[ebp];
		}
		else
			return -1;
	}
	float peek(void) const
	{
		return stacklist[top];
	}
	void clearstack(void)
	{
		for (int i = top;i >= 0;i--)
			stacklist[i] = 0;
		top = -1;
		std::cout << "clear done" << std::endl;
	}
	bool isFull(void)const
	{
		return top > 100 ? true : false;
	}
	bool isEmpty(void)const
	{
		return top < 0 ? true : false;
	}

};
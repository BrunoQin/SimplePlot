#pragma once
#include<iostream>
class stack {
private:
	char stacklist[100];
	int top;
public:
	stack(void)
	{
		this->top = -1;
	}
	~stack(void)
	{
		this->top = -1;
	}
	void push(const char &item)
	{
		if (!isFull())
		{
			top += 1;
			this->stacklist[top] = item;
		}
		else
			std::cout << "Out of the Stack" << std::endl;
	}
	char pop(void)
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
	char peek(void) const
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
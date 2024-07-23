
#include "headers/stack.h"//以向量类，派生出模板类


int main()
{
	int i;
	Stack<int>stk;
	for (i = 0; i < 10; i++)
	{
		//进行100次入栈操作
		stk.push(i);
	}
	cout << "--------------------------------------------01.get the top of stack---------------------------------------------" << endl;
	int top = stk.top();
	cout << "the current top element of this stack is:" << top << endl;
	cout << endl;

	cout << "-------------------02.continually pop until the stack is empty and print the element of stack-------------------" << endl;
	while (!stk.empty())
	{
		cout << stk.top() << " ";
		stk.pop();
	}
	cout << endl;
	cout << endl << "The test for stack is over!" << endl;

	return 0;
}

#pragma once
#include"Vector.h"//�������࣬������ģ����


template <typename T>
class Stack : public Vector<T>
{	//����������/ĩ����Ϊջ��/��
public:
	//size()��empty()�Լ��������Žӿڣ�����ֱ������
	void push(T const& e)
	{
		//ֵ��ע����ǣ�����insert�ӿ�ҵ���ڱ�׼���������Լ���ʵ�֣���������Ҫ��ʾ��ָ��
		//�����õ�����һ�����ذ汾
		Vector<T>::insert(e);
	} //��ջ����Ч�ڽ���Ԫ����Ϊ������ĩԪ�ز���

	T pop()
	{
		return Vector<T>::remove(Vector<T>::size() - 1);
	} //��ջ����Ч��ɾ��������ĩԪ��

	T& top()
	{
		return (*this)[Vector<T>::size() - 1];
	} //ȡ����ֱ�ӷ���������ĩԪ��
};


int main()
{
	int i;
	Stack<int>stk;
	for (i = 0; i < 10; i++)
	{
		//����100����ջ����
		stk.push(i);
	}
	cout << "-------------------01.ȡ������--------------------------------------------" << endl;
	int top = stk.top();
	cout << "the current top element of this stack is:" << top << endl;
	cout << endl;

	cout << "-------------------02.���ϵص�ջ��ֱ��ջΪ��,�����ջ�е�����-------------" << endl;
	while (!stk.empty())
	{
		cout << stk.top() << " ";
		stk.pop();
	}
	cout << endl;
	cout << endl << "test over!" << endl;

	system("pause");
	return 0;
}

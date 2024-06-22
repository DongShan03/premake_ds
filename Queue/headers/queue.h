#ifndef LIST_H
#define LIST_H

#include "../../List/headers/list.h"
using namespace std;

template<typename T>
class Queue :public List<T>
{
	//����ģ���ࣨ�̳�Listԭ�нӿڣ�
public:
	//size(),empty(),�Լ��������Žӿھ���ֱ������
	void enqueue(T const& e)
	{
		List<T>::insertAsLast(e);//��ӣ�β������
	}

	T dequeue()
	{
		return List<T>::remove(List<T>::first());//��ӣ��ײ�����
	}

	T& front()
	{
		return List<T>::first()->data;//����
	}
};
#endif // !LIST_H
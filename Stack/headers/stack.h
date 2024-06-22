#ifndef VECTOR_H
#define VECTOR_H

#include "../../Vector/headers/vector.h"

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


#endif // !VECTOR_H
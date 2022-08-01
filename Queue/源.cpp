#include"List.h"

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

int main()
{
	Queue<int>que;
	for (int i = 0; i < 100; i++)
	{
		que.enqueue(i);
	}

	int i = 0;
	while (!que.empty())
	{
		cout << que.front() << "  ";
		i++;
		if (i % 10 == 0)
		{
			cout << endl;
		}
		que.dequeue();
	}
	system("pause");
	return 0;
}

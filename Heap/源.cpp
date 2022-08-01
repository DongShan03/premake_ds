
#include"Vector.h"

#define InHeap(n,i) (((-1)<i))&&((i)<(n))//�ж�PQ[i]�Ƿ�Ϸ�
#define Parent(i)  ((i-1)>>1)//PQ[i]�ĸ��ڵ�(floor((i-1)/2),i��������)
#define LastInternal(n)  Parent(n-1)//���һ���ڲ��ڵ�(Ҳ��ĩ�ڵ�ĸ���)
#define LChild(i)	(1+((i)<<1))//PQ[i]������
#define RChild(i)	((1+(i)<<1))//PQ[i]���Һ���
#define ParentValid(i)	(0<i)//�ж�PQ[i]�Ƿ��и���
#define LChildValid(n,i)	InHeap(n,LChild(i)) //�ж�PQ[i]�Ƿ���һ��(��)����
#define RChildValid(n,i)	InHeap(n,RChild(i)) //�ж�PQ[i]�Ƿ�����������
#define Bigger(PQ,i,j)	(lt(PQ[i],PQ[j])?j:i)//ȡ����(��ʱǰ������)
#define ProperParent(PQ,n,i) /*���ӣ����ࣩ�����еĴ���*/\
		(RChildValid(n,i)?Bigger(PQ,Bigger(PQ,i,LChild(i)),RChild(i)):\
		(LChildValid(n,i)?Bigger(PQ,i,LChild(i)):i\
		)\
		)//���ʱ���ڵ����ȣ���˿ɱ��ⲻ��Ҫ�Ľ���


template<typename T>
struct PQ
{
	//���ȼ�����PQģ����
	virtual void insert(T) = 0;//���ձȽ���ȷ�������ȼ�����������
	virtual T getMax() = 0;//ȡ�����ȼ���ߵĴ���
	virtual T delMax() = 0;//ɾ�����ȼ���ߵĴ���
};


template<typename T>
class PQ_ComplHeap :public PQ<T>, public Vector<T>
{
	//��ȫ�����
protected:

	Rank percolateDown(Rank n, Rank i);//����

	Rank percolateUp(Rank i);//����

	void heapify(Rank n);//Floyd�����㷨

public:

	PQ_ComplHeap()
	{
		//Ĭ�Ϲ��캯��
	}

	PQ_ComplHeap(T* A, Rank n)
	{
		Vector<T>::copyFrom(A, 0, n);//��������
		heapify(n);
	}

	void insert(T e);//���ձȽ���ȷ�������ȼ����򣬲������

	T getMax();//��ȡ���ȼ���ߵĴ���
	T delMax();//ɾ�����ȼ���ߵĴ���

};//PQ_ComlHeap

template<typename T>
T PQ_ComplHeap<T>::getMax()
{
	return Vector<T>::_elem[0];//ȡ���ȼ���ߵĴ���
}


template<typename T>
void PQ_ComplHeap<T>::insert(T e)
{
	//������������ȫ�����֮��
	Vector<T>::insert(e);//���Ƚ�������������ĩβ
	percolateUp(Vector<T>::_size - 1);//�ٶԸô���ʵʩ���˵���
}


//��Ҫ����
//�������еĵ�i������ʵʩ���˲�����i<_size
template<typename T>
Rank PQ_ComplHeap<T>::percolateUp(Rank i)
{
	while (ParentValid(i))//ֻҪԪ��i���и�����δ�ִ�Ѷ�����
	{
		Rank j = Parent(i);//��i֮������j
		if (lt(Vector<T>::_elem[i], Vector<T>::_elem[j]))
		{
			//һ����ǰ���ӹ�ϵ�����������˼����
			break;
		}
		else
		{
			//�����ӹ�ϵ�Ե�������������һ��
			swap(Vector<T>::_elem[i], Vector<T>::_elem[j]);
			i = j;//�����ܹ�������һ�������
		}
	}
	return i;//�����������յִ��λ��
}


template<typename T>
T PQ_ComplHeap<T>::delMax()
{
	//ɾ���ǿ���ȫ����������ȼ���ߵ�Ԫ��
	T maxElem = Vector<T>::_elem[0];
	Vector<T>::_elem[0] = Vector<T>::_elem[--Vector<T>::_size];//ժ���Ѷ��״�������֮��ĩ����
	percolateDown(Vector<T>::_size, 0);//���¶Ѷ�ʵʩ����
	return maxElem;//���ش�ǰ���ݵ�������
}


//��������ǰn�������еĵ�i���������ˣ�i<n
template<typename T>
Rank PQ_ComplHeap<T>::percolateDown(Rank n, Rank i)
{
	Rank j;//i����(��������)�����У���Ϊ����
	while (i != (j = ProperParent(this->_elem, n, i)))//ֻҪi����j
	{
		//��
		std::swap(Vector<T>::_elem[i], Vector<T>::_elem[j]);
		i = j;//���߻�λ�����������½����i
	}
	return i;//�������˵ִ��λ��(��i��j)
}



template<typename T>
void PQ_ComplHeap<T>::heapify(Rank n)
{
	//Floyd�����㷨��O(n)ʱ��
	for (int i = LastInternal(n); InHeap(n, i); i--)//�Ե׶�������
	{
		percolateDown(n, i);//���˸��ڲ��ڵ�
	}
}


template<typename T>
void Vector<T>::heapSort(Rank lo, Rank hi)
{
	//0<=lo <hi<=size
	PQ_ComplHeap<T>H(Vector<T>::_elem + lo, hi - lo);//��һ�������������齨��һ����ȫ�����,O(n)
	while (!H.Vector<T>::empty())
	{
		//������ժ�����Ԫ������������ĺ�׺��ֱ���ѿ�
		Vector<T>::_elem[--hi] = H.delMax();//��Ч�ڶѶ���ĩԪ�ضԻ�������
	}
}

int  main()
{
	Vector<int>obj;
	for (int i = 0; i < 100; i++)
	{
		obj.insert(i);
	}
	obj.unsort();
	obj.traverse(visit);
	cout << endl;
	obj.heapSort(0, 100);
	obj.traverse(visit);
	system("pause");
	return 0;
}

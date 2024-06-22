#include "../../Vector/headers/vector.h"

#define lt(a, b) ((a < b) ? true : false)
#define InHeap(n,i) (((-1)<i))&&((i)<(n))//判断PQ[i]是否合法
#define Parent(i)  ((i-1)>>1)//PQ[i]的父节点(floor((i-1)/2),i无论正负)
#define LastInternal(n)  Parent(n-1)//最后一个内部节点(也即末节点的父亲)
#define LChild(i)	(1+((i)<<1))//PQ[i]的左孩子
#define RChild(i)	((1+(i)<<1))//PQ[i]的右孩子
#define ParentValid(i)	(0<i)//判断PQ[i]是否有父亲
#define LChildValid(n,i)	InHeap(n,LChild(i)) //判断PQ[i]是否有一个(左)孩子
#define RChildValid(n,i)	InHeap(n,RChild(i)) //判断PQ[i]是否有两个孩子
#define Bigger(PQ,i,j)	(lt(PQ[i],PQ[j])?j:i)//取大者(等时前者优先)
#define ProperParent(PQ,n,i) /*父子（至多）三者中的大者*/\
		(RChildValid(n,i)?Bigger(PQ,Bigger(PQ,i,LChild(i)),RChild(i)):\
		(LChildValid(n,i)?Bigger(PQ,i,LChild(i)):i\
		)\
		)//相等时父节点优先，如此可避免不必要的交换

template<typename T>
struct PQ
{
	//优先级队列PQ模板类
	virtual void insert(T) = 0;//按照比较器确定的优先级次序插入词条
	virtual T getMax() = 0;//取出优先级最高的词条
	virtual T delMax() = 0;//删除优先级最高的词条
};


template<typename T>
class PQ_ComplHeap :public PQ<T>, public Vector<T>
{
	//完全二叉堆
protected:

	Rank percolateDown(Rank n, Rank i);//下滤

	Rank percolateUp(Rank i);//上滤

	void heapify(Rank n);//Floyd建堆算法

public:

	PQ_ComplHeap()
	{
		//默认构造函数
	}

	PQ_ComplHeap(T* A, Rank n)
	{
		Vector<T>::copyFrom(A, 0, n);//批量构造
		heapify(n);
	}

	void insert(T e);//按照比较器确定的优先级次序，插入词条

	T getMax();//读取优先级最高的词条
	T delMax();//删除优先级最高的词条

};//PQ_ComlHeap

#include "getMax.h"
#include "insert.h"
#include "percolateUp.h"
#include "delMax.h"
#include "percolateDown.h"
#include "heapify.h"
#include "heapSort.h"
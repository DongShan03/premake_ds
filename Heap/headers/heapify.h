template<typename T>
void PQ_ComplHeap<T>::heapify(Rank n)
{
	//Floyd建堆算法，O(n)时间
	for (int i = LastInternal(n); InHeap(n, i); i--)//自底而上依次
	{
		percolateDown(n, i);//下滤各内部节点
	}
}

template<typename T>
void PQ_ComplHeap<T>::insert(T e)
{
	//将词条插入完全二叉堆之中
	Vector<T>::insert(e);//首先将词条接至向量末尾
	percolateUp(Vector<T>::_size - 1);//再对该词条实施上滤调整
}

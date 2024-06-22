template<typename T>
T PQ_ComplHeap<T>::delMax()
{
	//删除非空完全二叉堆中优先级最高的元素
	T maxElem = Vector<T>::_elem[0];
	Vector<T>::_elem[0] = Vector<T>::_elem[--Vector<T>::_size];//摘除堆顶首词条，代之以末词条
	percolateDown(Vector<T>::_size, 0);//对新堆顶实施下滤
	return maxElem;//返回此前备份的最大词条
}

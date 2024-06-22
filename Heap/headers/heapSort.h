template<typename T>
void Vector<T>::heapSort(Rank lo, Rank hi)
{
	//0<=lo <hi<=size
	PQ_ComplHeap<T>H(Vector<T>::_elem + lo, hi - lo);//将一个待排序区间组建成一个完全二叉堆,O(n)
	while (!H.Vector<T>::empty())
	{
		//反复的摘除最大元并归入已排序的后缀，直至堆空
		Vector<T>::_elem[--hi] = H.delMax();//等效于堆顶与末元素对换后下滤
	}
}
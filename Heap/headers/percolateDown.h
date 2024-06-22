
//対向量中前n个词条中的第i个进行下滤，i<n
template<typename T>
Rank PQ_ComplHeap<T>::percolateDown(Rank n, Rank i)
{
	Rank j;//i及其(至多两个)孩子中，堪为父者
	while (i != (j = ProperParent(this->_elem, n, i)))//只要i不是j
	{
		//则
		std::swap(Vector<T>::_elem[i], Vector<T>::_elem[j]);
		i = j;//二者换位，并考察其下降后的i
	}
	return i;//返回下滤抵达的位置(亦i亦j)
}

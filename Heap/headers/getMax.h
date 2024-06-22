
template<typename T>
T PQ_ComplHeap<T>::getMax()
{
	return Vector<T>::_elem[0];//取优先级最高的词条
}

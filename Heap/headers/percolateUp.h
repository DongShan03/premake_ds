//重要操作
//对向量中的第i个词条实施上滤操作，i<_size
template<typename T>
Rank PQ_ComplHeap<T>::percolateUp(Rank i)
{
	while (ParentValid(i))//只要元素i具有父亲尚未抵达堆顶，则
	{
		Rank j = Parent(i);//将i之父记作j
		if (lt(Vector<T>::_elem[i], Vector<T>::_elem[j]))
		{
			//一旦当前父子关系不在逆序，上滤即完成
			break;
		}
		else
		{
			//否则父子关系对调，继续考察上一层
			swap(Vector<T>::_elem[i], Vector<T>::_elem[j]);
			i = j;//这是能够考察上一层的条件
		}
	}
	return i;//返回上滤最终抵达的位置
}

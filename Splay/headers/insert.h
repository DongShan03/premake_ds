template<typename T>
BinNodePosi(T) Splay<T>::insert(const T& e)
{
	//将关键码e插入伸展树中
	if (!BinTree<T>::_root)
	{
		BinTree<T>::_size++;
		return BinTree<T>::_root = new BinNode<T>(e);//处理原树为空的退化情况
	}
	if (e == Splay<T>::search(e)->data)
	{
		return BinTree<T>::_root;//确认目标节点不存在
	}
	BinTree<T>::_size++;
	BinNodePosi(T) t = BinTree<T>::_root;//创建新节点，以下调整<=7个指针以完成布局重构
	if (BinTree<T>::_root->data < e)
	{
		//插入新根，以t和t->rc为左右孩子
		t->parent = BinTree<T>::_root = new BinNode<T>(e, NULL, t, t->rc);//2+3个
		if (HasRChild(*t))
		{
			t->rc->parent = BinTree<T>::_root;
			t->rc = NULL;//<=2个
		}
	}
	else//插入新根，以t->lc和t为左右孩子
	{
		t->parent = BinTree<T>::_root = new BinNode<T>(e, NULL, t->lc, t);//2+3个
		if (HasLChild(*t))
		{
			t->lc->parent = BinTree<T>::_root;
			t->lc = NULL;//<=2个
		}
	}
	BinTree<T>::updateHeightAbove(t);//更新t及其祖先(实际上只有_root一个)的高度
	return BinTree<T>::_root;//新节点必然置于树根，返回之
}//无论e是否存在于原树之中,返回时总有_root->data=e

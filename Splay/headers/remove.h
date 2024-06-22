template<typename T>
bool Splay<T>::remove(const T& e)//从伸展树中删除关键码e
{
	if (!BinTree<T>::_root || (e != Splay<T>::search(e)->data))
	{
		//若数空或者目标不存在，则无法删除
		return false;
	}
	BinNodePosi(T)w = BinTree<T>::_root;//assert：经过search()之后的节点e已经被伸展至树根
	if (!HasLChild(*BinTree<T>::_root))//若无左子树，直接删除
	{
		BinTree<T>::_root = BinTree<T>::_root->rc;
		if (BinTree<T>::_root)
		{
			BinTree<T>::_root->parent = NULL;
		}
	}
	else if (!HasRChild(*BinTree<T>::_root))//若无右子树，直接删除
	{
		BinTree<T>::_root = BinTree<T>::_root->lc;
		if (BinTree<T>::_root)
		{
			BinTree<T>::_root->parent = NULL;
		}
	}
	else
	{
		//若左右子树同时存在
		BinNodePosi(T)lTree = BinTree<T>::_root->lc;
		lTree->parent = NULL;
		BinTree<T>::_root->lc = NULL;//暂时将左子树切除
		BinTree<T>::_root = BinTree<T>::_root->rc;
		BinTree<T>::_root->parent = NULL;//只保留右子树
		Splay<T>::search(w->data);//以原树根为目标做一次（必定失败的）查找
		BinTree<T>::_root->lc = lTree;
		//assert:至此，右子树中最小节点必然延伸至树根，而且因为没有雷同节点，其左子树必空，于是
		lTree->parent = BinTree<T>::_root;//只需将左子树接回原位即可
	}
	release(w->data);
	release(w);
	BinTree<T>::_size--;//只需将左子树接回原位即可
	if (BinTree<T>::_root)
	{
		BinTree<T>::updateHeight(BinTree<T>::_root);//此后若书非空，则树根的高度需要更新
	}
	return true;//返回成功标志
}//若目标节点存在且被删除，返回True否则返回False

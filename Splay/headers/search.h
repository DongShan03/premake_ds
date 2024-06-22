template<typename T>
BinNodePosi(T)& Splay<T>::search(const T& e)
{
	//在伸展树中查找e
	BinNodePosi(T) p = searchIn(BinTree<T>::_root, e, BST<T>::_hot = NULL);
	BinTree<T>::_root = Splay<T>::splay(p ? p : BST<T>::_hot);//将最后一个被访问的节点伸展至树根
	return BinTree<T>::_root;
}//与其他BST不同，无论查找成功与否，_root都指向最终被访问过的节点

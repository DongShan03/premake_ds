template <typename T>
BinNodePosi(T) RedBlack<T>::insert(const T& e)
{
    //将e插入红黑树
    BinNodePosi(T)& x = BST<T>::search(e);
    if (x)
    {
        return x; //确认目标不存在（留意对_hot的设置）
    }
    x = new BinNode<T>(e, BST<T>::_hot, NULL, NULL, -1);
    BinTree<T>::_size++; //创建红节点x：以_hot为父，黑高度-1
    BinNodePosi(T) xOld = x;
    solveDoubleRed(x);
    return xOld; //经双红修正后，即可返回
} //无论e是否存在于原树中，返回时总有x->data == e

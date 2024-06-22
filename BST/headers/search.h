
template <typename T>
BinNodePosi(T)& BST<T>::search(const T& e)
{
    //在BST中查找关键码e
    if (!BinTree<T>::_root || e == BinTree<T>::_root->data)
    {
        _hot = NULL;
        return BinTree<T>::_root;
    } //在树根v处命中

    for (_hot = BinTree<T>::_root; ; )
    {
        //自顶而下
        BinNodePosi(T)& c = (e < _hot->data) ? _hot->lc : _hot->rc; //确定方向
        if (!c || e == c->data)
        {
            return c;
        }
        _hot = c; //命中返回，或者深入一层
    } //无论命中或失败，hot均指向v之父亲（或为NULL）
} //返回目标节点位置的引用，以便后续插入、删除操作


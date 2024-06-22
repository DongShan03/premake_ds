template <typename T> //将e紧靠当前节点之前插入于当前节点所属列表（设有哨兵头节点header）
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e)
{
    ListNodePosi(T) x = new ListNode(e, pred, this); //创建新节点
    pred->succ = x;
    pred = x; //设置正向链接
    return x; //返回新节点的位置
}


template <typename T> //将e紧随当前节点之后插入于当前节点所属列表（设有哨兵尾节点trailer）
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e)
{
    ListNodePosi(T) x = new ListNode(e, this, succ); //创建新节点
    succ->pred = x;
    succ = x; //设置逆向链接
    return x; //返回新节点的位置
}

template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const& e)
{
    _size++;
    return header->insertAsSucc(e);
} //e当作首节点插入


template <typename T>
ListNodePosi(T) List<T>::insertAsLast(T const& e)
{
    _size++;
    return trailer->insertAsPred(e);
} //e当作末节点插入

template <typename T>
ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p, T const& e)
{
    _size++;
    return p->insertAsSucc(e);
} //e当作p的后继插入（After）


template <typename T>
ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p, T const& e)
{
    _size++;
    return p->insertAsPred(e);
} //e当作p的前驱插入（Before）

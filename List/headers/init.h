template <typename T>
void List<T>::init()
{ //列表初始化，在创建列表对象时统一调用
    header = new ListNode<T>; //创建头哨兵节点
    trailer = new ListNode<T>; //创建尾哨兵节点
    header->succ = trailer;
    header->pred = NULL;
    trailer->pred = header;
    trailer->succ = NULL;
    _size = 0; //记录规模
}

template <typename T> //复制列表中自位置p起的n项（assert: p为合法位置，且至少有n-1个后继节点）
List<T>::List(ListNodePosi(T) p, int n)
{
    copyNodes(p, n);
}


template <typename T> //整体复制列表L
List<T>::List(List<T> const& L)
{
    copyNodes(L.first(), L._size);
}


template <typename T> //复制L中自第r项起的n项（assert: r+n <= L._size）
List<T>::List(List<T> const& L, int r, int n)
{
    ListNodePosi(T) p = L.first();
    while (0 < r--)
    {
        p = p->succ;
    }
    copyNodes(p, n);
}


template <typename T> List<T>::~List() //列表析构器
{
    clear();
    delete header;
    delete trailer;
} //清空列表，释放头、尾哨兵节点
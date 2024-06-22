template <typename T>
void List<T>::traverse(void (*visit) (T&)) //借助函数指针机制遍历
{
    //这里为了输出美观，每10个元素换一行
    int i = 0;
    for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
    {
        visit(p->data);
        i++;
        if (i % 10 == 0)
        {
            cout << endl;
        }
    }
}

template <typename T>
template <typename VST> //元素类型、操作器
void List<T>::traverse(VST& visit) //借助函数对象机制遍历
{
    for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
    {
        visit(p->data);
    }
}
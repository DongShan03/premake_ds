template <typename T>
int List<T>::deduplicate()
{
    int oldSize = _size;
    ListNodePosi(T) p = first();
    for (Rank r = 0; p != trailer; p = p->succ) //O(n)
    {
        if (ListNodePosi(T) q = find(p->data, r, p))
        {
            remove(q); //此时q与p雷同，但删除前者更为简明
        }
        else
        {
            r++; //r为无重前缀的长度
        }
    }
    return oldSize - _size; //删除元素总数
}
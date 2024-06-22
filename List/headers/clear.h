template <typename T>
int List<T>::clear()
{ //清空列表
    int oldSize = _size;
    while (0 < _size)
    {
        remove(header->succ); //反复删除首节点，直至列表变空
    }
    return oldSize;
}
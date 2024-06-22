template <typename T> //向量的起泡排序（跳跃版）
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{ //assert: 0 <= lo < hi <= size
    for (Rank last = --hi; lo < hi; hi = last)
    {
        for (Rank i = last = lo; i < hi; i++)
        {
            if (_elem[i] > _elem[i + 1]) //若逆序，则
            {
                swap(_elem[last = i], _elem[i + 1]); //经交换使局部有序
            }
        }
    }
};


template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) //一趟扫描交换
{
    bool sorted = true;//整体有序标志
    while (++lo < hi)
    {
        //自左向右，逐一检查个对相邻元素
        if (_elem[lo - 1] > _elem[lo])
        {
            //若逆序，则意味着尚未整体有序，并需要通过交换使得局部有序
            sorted = false;
            swap(_elem[lo - 1], _elem[lo]);
        }
    }
    return sorted;//返回有序标志
};

template <typename T> //向量选择排序
void Vector<T>::selectionSort(Rank lo, Rank hi)
{ //0 <= lo < hi <= size
    while (lo < --hi)
    {
        swap(_elem[max(lo, hi)], _elem[hi]); //将[hi]与[lo, hi]中的最大者交换
    }
}
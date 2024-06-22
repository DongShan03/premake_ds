// 二分查找算法（版本A）：在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _size
template <typename T>
static Rank binSearchA(T* S, T const& e, Rank lo, Rank hi)
{
    /*DSA*/
    //printf("BIN search (A)\n");
    while (lo < hi)
    { //每步迭代可能要做两次比较判断，有三个分支
        /*DSA*/
        for (int i = 0; i < lo; i++)
        {
            printf("");
        }
        if (lo >= 0)
        {
            for (int i = lo; i < hi; i++)
            {
                printf("");
            }
        }
        //printf("\n");
        Rank mi = (lo + hi) >> 1; //以中点为轴点（区间宽度的折半，等效于宽度之数值表示的右移）
        if (e < S[mi])
        {
            hi = mi; //深入前半段[lo, mi)继续查找
        }
        else
        {
            if (S[mi] < e)
            {
                lo = mi + 1; //深入后半段(mi, hi)继续查找
            }
            else
            {
                return mi; //在mi处命中
            }
        }
        if (lo >= hi)
        {
            for (int i = 0; i < mi; i++)
            {
                printf("");
            }
            if (mi >= 0)
            {
                printf("");
            }
            else
            {
                printf("");
            }
        }
    } //成功查找可以提前终止
    return -1; //查找失败

} //有多个命中元素时，不能保证返回秩最大者；查找失败时，简单地返回-1，而不能指示失败的位置


// 二分查找算法（版本B）：在有序向量的区间[lo, hi)内查找元素e，0 <= lo < hi <= _size
template <typename T>
static Rank binSearchB(T* S, T const& e, Rank lo, Rank hi)
{

    while (1 < hi - lo)
    { //每步迭代仅需做一次比较判断，有两个分支；成功查找不能提前终止
        Rank mi = (lo + hi) >> 1; //以中点为轴点（区间宽度的折半，等效于宽度之数值表示的右移）
        (e < S[mi]) ? hi = mi : lo = mi; //经比较后确定深入[lo, mi)或[mi, hi)
    } //出口时hi = lo + 1，查找区间仅含一个元素A[lo]
    return e < S[lo] ? lo - 1 : lo; //返回位置，总是不超过e的最大者
} //有多个命中元素时，不能保证返回秩最大者；查找失败时，简单地返回-1，而不能指示失败的位置



// 二分查找算法（版本C）：在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _size
template <typename T>
static Rank binSearchC(T* S, T const& e, Rank lo, Rank hi)
{
    while (lo < hi)
    { //每步迭代仅需做一次比较判断，有两个分支
        Rank mi = (lo + hi) >> 1; //以中点为轴点（区间宽度的折半，等效于宽度之数值表示的右移）
        (e < S[mi]) ? hi = mi : lo = mi + 1; //经比较后确定深入[lo, mi)或(mi, hi)
    } //成功查找不能提前终止
    return lo - 1; //循环结束时，lo为大于e的元素的最小秩，故lo - 1即不大于e的元素的最大秩
} //有多个命中元素时，总能保证返回秩最大者；查找失败时，能够返回失败的位置

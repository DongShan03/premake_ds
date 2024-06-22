// 随机生成期望高度为h的二叉树
template <typename T> bool randomBinTree(BinTree<T>& bt, BinNodePosi(T) x, int h)
{
    if (0 >= h)
    {
        return false; //至多h层
    }
    if (0 < dice(h)) //以1/h的概率终止当前分支的生长
    {
        randomBinTree(bt, bt.insertAsLC(x, dice((T)h * h * h)), h - 1);
    }
    if (0 < dice(h)) //以1/h的概率终止当前分支的生长
    {
        randomBinTree(bt, bt.insertAsRC(x, dice((T)h * h * h)), h - 1);
    }
    return true;
}

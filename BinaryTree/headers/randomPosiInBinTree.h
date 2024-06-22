
// 在二叉树中随机确定一个节点位置
template <typename T> BinNodePosi(T) randomPosiInBinTree(BinNodePosi(T) root)
{
    if (!HasChild(*root))
    {
        return root;
    }
    if (!HasLChild(*root))
    {
        return dice(6) ? randomPosiInBinTree(root->rc) : root;
    }
    if (!HasRChild(*root))
    {
        return dice(6) ? randomPosiInBinTree(root->lc) : root;
    }
    return dice(2) ? randomPosiInBinTree(root->lc) : randomPosiInBinTree(root->rc);
}
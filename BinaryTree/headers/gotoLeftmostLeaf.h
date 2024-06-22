template <typename T> //在以S栈顶节点为根的子树中，找到最高左侧可见叶节点
static void gotoLeftmostLeaf(Stack<BinNodePosi(T)>& S)
{ //沿途所遇节点依次入栈
    while (BinNodePosi(T) x = S.top()) //自顶而下，反复检查当前节点（即栈顶）
    {
        if (HasLChild(*x))
        { //尽可能向左
            if (HasRChild(*x))
            {
                S.push(x->rc); //若有右孩子，优先入栈
            }
            S.push(x->lc); //然后才转至左孩子
        }
        else //实不得已
        {
            S.push(x->rc); //才向右
        }
    }
    S.pop(); //返回之前，弹出栈顶的空节点
}

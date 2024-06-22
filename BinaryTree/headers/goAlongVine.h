template <typename T> //从当前节点出发，沿左分支不断深入，直至没有左分支的节点
static void goAlongVine(BinNodePosi(T) x, Stack<BinNodePosi(T)>& S)
{
    while (x)
    {
        S.push(x);
        x = x->lc;
    } //当前节点入栈后随即向左侧分支深入，迭代直到无左孩子
}
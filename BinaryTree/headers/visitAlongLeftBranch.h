template<typename T, typename VST>
static void visitAlongLeftBranch(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)>& S)
{
    while (x)
    {
        visit(x);
        S.push(x->rc);
        x = x->lc;
    }
}
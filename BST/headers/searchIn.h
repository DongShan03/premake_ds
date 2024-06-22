template<typename T>//在以根为e的(AVL,Splay,rbTree)BST子树中查找关键码e
static BinNodePosi(T)& searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot)
{
    if (!v || (e == v->data))
    {
        return v;
    }
    hot = v;
    return searchIn(((e < v->data) ? v->lc : v->rc), e, hot);//深入一层递归查找
}//返回时，返回值指向命中节点(或者假想的通配哨兵)，hot指向其父亲(退化视为初始值NULL)

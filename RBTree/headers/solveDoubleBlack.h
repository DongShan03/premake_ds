
template <typename T>
void RedBlack<T>::solveDoubleBlack(BinNodePosi(T) r)
{
    BinNodePosi(T) p = r ? r->parent : BST<T>::_hot;
    if (!p)
    {
        return; //r的父亲
    }
    BinNodePosi(T) s = (r == p->lc) ? p->rc : p->lc; //r的兄弟
    if (IsBlack(s))
    {
        //兄弟s为黑
        BinNodePosi(T) t = NULL; //s的红孩子（若左、右孩子皆红，左者优先；皆黑时为NULL）
        if (IsRed(s->rc))
        {
            t = s->rc; //右子
        }
        if (IsRed(s->lc))
        {
            t = s->lc; //左子
        }
        if (t)
        {
            //黑s有红孩子：BB-1
            RBColor oldColor = p->color; //备份原子树根节点p颜色，并对t及其父亲、祖父
            // 以下，通过旋转重平衡，并将新子树的左、右孩子染黑
            BinNodePosi(T) b = FromParentTo(*p) = BST<T>::rotateAt(t); //旋转
            if (HasLChild(*b))
            {
                b->lc->color = RB_BLACK;
                updateHeight(b->lc);
            } //左子
            if (HasRChild(*b))
            {
                b->rc->color = RB_BLACK;
                updateHeight(b->rc);
            } //右子
            b->color = oldColor; updateHeight(b); //新子树根节点继承原根节点的颜色
        }
        else
        {
            //黑s无红孩子
            s->color = RB_RED; s->height--; //s转红
            if (IsRed(p))
            { //BB-2R
                p->color = RB_BLACK; //p转黑，但黑高度不变
            }
            else
            {
                p->height--; //p保持黑，但黑高度下降
                solveDoubleBlack(p); //递归上溯
            }
        }
    }
    else
    {
        //兄弟s为红：BB-3
        s->color = RB_BLACK;
        p->color = RB_RED; //s转黑，p转红
        BinNodePosi(T) t = IsLChild(*s) ? s->lc : s->rc; //取t与其父s同侧
        BST<T>::_hot = p;
        FromParentTo(*p) = BST<T>::rotateAt(t); //对t及其父亲、祖父做平衡调整
        solveDoubleBlack(r); //继续修正r处双黑——此时的p已转红，故后续只能是BB-1或BB-2R
    }
}

template <typename T>
BinNodePosi(T) AVL<T>::rotateAt(BinNodePosi(T) v)
{ //v为非空孙辈节点
    BinNodePosi(T) p = v->parent;
    BinNodePosi(T) g = p->parent; //视v、p和g相对位置分四种情况
    if (IsLChild(*p)) /* zig */
        if (IsLChild(*v))
        { /* zig-zig */
            p->parent = g->parent; //向上联接
            return AVL<T>::connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
        }
        else
        { /* zig-zag */
            v->parent = g->parent; //向上联接
            return AVL<T>::connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
        }
    else  /* zag */
    {
        if (IsRChild(*v))
        { /* zag-zag */
            p->parent = g->parent; //向上联接
            return AVL<T>::connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
        }
        else
        { /* zag-zig */
            v->parent = g->parent; //向上联接
            return AVL<T>::connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
        }
    }
}

template <typename T>
static BinNodePosi(T) BST_removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot)
{
    BinNodePosi(T) w = x; //实际被摘除的节点，初值同x
    BinNodePosi(T) succ = NULL; //实际被删除节点的接替者
    if (!HasLChild(*x)) //若*x的左子树为空，则可
    {
        succ = x = x->rc; //直接将*x替换为其右子树
    }
    else if (!HasRChild(*x)) //若右子树为空，则可
    {
        succ = x = x->lc; //对称地处理——注意：此时succ != NULL
    }
    else
    { //若左右子树均存在，则选择x的直接后继作为实际被摘除节点，为此需要
        w = w->succ(); //（在右子树中）找到*x的直接后继*w
        swap(x->data, w->data); //交换*x和*w的数据元素
        BinNodePosi(T) u = w->parent;
        ((u == x) ? u->rc : u->lc) = succ = w->rc; //隔离节点*w
    }
    hot = w->parent; //记录实际被删除节点的父亲
    if (succ)
    {
        succ->parent = hot; //并将被删除节点的接替者与hot相联
    }
    release(w->data);
    release(w);
    return succ; //释放被摘除节点，返回接替者
} //release()负责释放复杂结构，与算法无直接关系，具体实现详见代码包

template <typename T>
bool BST<T>::remove(const T& e)
{
    //从BST树中删除关键码e
    BinNodePosi(T)& x = search(e);
    if (!x)
    {
        return false; //确认目标存在（留意_hot的设置）
    }
    BST_removeAt(x, _hot);
    BinTree<T>::_size--; //实施删除
    BinTree<T>::updateHeightAbove(_hot); //更新_hot及其历代祖先的高度
    return true;
} //删除成功与否，由返回值指示
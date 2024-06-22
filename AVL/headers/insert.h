
#define AVLFromParentTo(x)  ( IsRoot(x) ? BinTree<T>::_root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )/*来自父亲的引用*/
template <typename T>
BinNodePosi(T) AVL<T>::insert(const T& e)
{ //将关键码e插入AVL树中
    BinNodePosi(T)& x = BST<T>::search(e);
    if (x)
    {
        return x; //确认目标节点不存在
    }
    
    BinNodePosi(T) xx = x = new BinNode<T>(e, BST<T>::_hot);
    // if (BST<T>::_hot)
    //     cout << BST<T>::_hot->data << endl;
    BinTree<T>::_size++; //创建新节点x
    // 此时，x的父亲_hot若增高，则其祖父有可能失衡

    for (BinNodePosi(T) g = BST<T>::_hot; g; g = g->parent)
    {
        //从x之父出发向上，逐层检查各代祖先g
        if (!AvlBalanced(*g))
        { //一旦发现g失衡，则（采用“3 + 4”算法）使之复衡，并将子树
            if (IsRoot(*g))
            {
                BinTree<T>::_root = AVL<T>::rotateAt(tallerChild(tallerChild(g)));
            }
            else if (IsLChild(*g))
            {
                (*g).parent->lc = AVL<T>::rotateAt(tallerChild(tallerChild(g)));
            }
            else {
                (*g).parent->rc = AVL<T>::rotateAt(tallerChild(tallerChild(g)));
            }
            break; //g复衡后，局部子树高度必然复原；其祖先亦必如此，故调整随即结束
        }
        else //否则（g依然平衡），只需简单地
        {
            BST<T>::updateHeight(g); //更新其高度（注意：即便g未失衡，高度亦可能增加）
        }
    } //至多只需一次调整；若果真做过调整，则全树高度必然复原
    return xx; //返回新节点位置
} //无论e是否存在于原树中，总有AVL::insert(e)->data == e

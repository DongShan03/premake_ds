#include "../../BinaryTree/headers/bintree.h"

using namespace std;

template <typename T>
class BST : public BinTree<T>
{
    //由BinTree派生BST模板类
protected:
    BinNodePosi(T) _hot; //“命中”节点的父亲
public: //基本接口：以virtual修饰，强制要求所有派生类（BST变种）根据各自的规则对其重写
    virtual BinNodePosi(T)& search(const T& e); //查找
    virtual BinNodePosi(T) insert(const T& e); //插入
    virtual bool remove(const T& e); //删除
    virtual BinNodePosi(T) rotateAt(BinNodePosi(T) v);
    virtual BinNodePosi(T) connect34(
        BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
        BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3
    );
};

template <typename T> BinNodePosi(T) BST<T>::connect34(
    BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
    BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3
) {
    //*DSA*/print(a); print(b); print(c); printf("\n");
    a->lc = T0; if (T0) T0->parent = a;
    a->rc = T1; if (T1) T1->parent = a; BinTree<T>::updateHeight(a);
    c->lc = T2; if (T2) T2->parent = c;
    c->rc = T3; if (T3) T3->parent = c; BinTree<T>::updateHeight(c);
    b->lc = a; a->parent = b;
    b->rc = c; c->parent = b; BinTree<T>::updateHeight(b);
    return b; //该子树新的根节点
}


#include "rotateAt.h"
#include "remove.h"
#include "search.h"
#include "insert.h"
#include "searchIn.h"
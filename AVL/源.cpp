#include"BST.h"


using namespace std;


#define tallerChild(x) ( \
   stature( (x)->lc ) > stature( (x)->rc ) ? (x)->lc : ( /*���*/ \
   stature( (x)->lc ) < stature( (x)->rc ) ? (x)->rc : ( /*�Ҹ�*/ \
   IsLChild( * (x) ) ? (x)->lc : (x)->rc /*�ȸߣ��븸��xͬ���ߣ�zIg-zIg��zAg-zAg������*/ \
   ) \
   ) \
)


template <typename T>
class AVL : public BST<T>
{
    //��BST����AVL��ģ����
public:
    BinNodePosi(T) connect34(
        BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
        BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3
    );

    BinNodePosi(T) rotateAt(BinNodePosi(T)x);//��x���丸���游��ͳһ����ת����

    BinNodePosi(T) insert(const T& e); //���루��д��

    bool remove(const T& e); //ɾ������д��
};


template <typename T>
BinNodePosi(T) AVL<T>::rotateAt(BinNodePosi(T) v)
{ //vΪ�ǿ��ﱲ�ڵ�
    BinNodePosi(T) p = v->parent;
    BinNodePosi(T) g = p->parent; //��v��p��g���λ�÷��������
    if (IsLChild(*p)) /* zig */
        if (IsLChild(*v))
        { /* zig-zig */
            p->parent = g->parent; //��������
            return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
        }
        else
        { /* zig-zag */
            v->parent = g->parent; //��������
            return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
        }
    else  /* zag */
    {
        if (IsRChild(*v))
        { /* zag-zag */
            p->parent = g->parent; //��������
            return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
        }
        else
        { /* zag-zig */
            v->parent = g->parent; //��������
            return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
        }
    }
}


template <typename T>
BinNodePosi(T) AVL<T>::insert(const T& e)
{ //���ؼ���e����AVL����
    BinNodePosi(T)& x = BST<T>::search(e);
    if (x)
    {
        return x; //ȷ��Ŀ��ڵ㲻����
    }
    BinNodePosi(T) xx = x = new BinNode<T>(e, BST<T>::_hot);
    BinTree<T>::_size++; //�����½ڵ�x
    // ��ʱ��x�ĸ���_hot�����ߣ������游�п���ʧ��
    for (BinNodePosi(T) g = BST<T>::_hot; g; g = g->parent)
    {
        //��x֮���������ϣ�������������g
        if (!AvlBalanced(*g))
        { //һ������gʧ�⣬�򣨲��á�3 + 4���㷨��ʹ֮���⣬��������
            FromParentTo(*g) = AVL<T>::rotateAt(tallerChild(tallerChild(g))); //���½���ԭ��
            break; //g����󣬾ֲ������߶ȱ�Ȼ��ԭ�������������ˣ��ʵ����漴����
        }
        else //����g��Ȼƽ�⣩��ֻ��򵥵�
        {
            BST<T>::updateHeight(g); //������߶ȣ�ע�⣺����gδʧ�⣬�߶���������ӣ�
        }
    } //����ֻ��һ�ε�����������������������ȫ���߶ȱ�Ȼ��ԭ
    return xx; //�����½ڵ�λ��
} //����e�Ƿ������ԭ���У�����AVL::insert(e)->data == e


template <typename T>
bool AVL<T>::remove(const T& e)
{ //��AVL����ɾ���ؼ���e
    BinNodePosi(T)& x = BST<T>::search(e);
    if (!x)
    {
        return false; //ȷ��Ŀ����ڣ�����_hot�����ã�
    }
    removeAt(x, BST<T>::_hot);
    BinTree<T>::_size--; //�Ȱ�BST����ɾ��֮���˺�ԭ�ڵ�֮��_hot�������Ⱦ�����ʧ�⣩
    for (BinNodePosi(T) g = BST<T>::_hot; g; g = g->parent)
    { //��_hot�������ϣ�������������g
        if (!AvlBalanced(*g)) //һ������gʧ�⣬�򣨲��á�3 + 4���㷨��ʹ֮���⣬��������������
        {
            g = FromParentTo(*g) = AVL<T>::rotateAt(tallerChild(tallerChild(g))); //ԭ����
        }
        BST<T>::updateHeight(g); //��������߶ȣ�ע�⣺����gδʧ�⣬�߶�����ܽ��ͣ�
    } //����������(logn)�ε������������Ƿ�����������ȫ���߶Ⱦ����ܽ���
    return true; //ɾ���ɹ�
} //��Ŀ��ڵ�����ұ�ɾ��������true�����򷵻�false


template <typename T>
BinNodePosi(T) AVL<T>::connect34(
    BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
    BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3
)
{
    a->lc = T0;
    if (T0)
    {
        T0->parent = a;
    }
    a->rc = T1;
    if (T1)
    {
        T1->parent = a;
    }
    BST<T>::updateHeight(a);
    c->lc = T2;
    if (T2)
    {
        T2->parent = c;
    }
    c->rc = T3;
    if (T3)
    {
        T3->parent = c;
    }
    BST<T>::updateHeight(c);
    b->lc = a;
    a->parent = b;
    b->rc = c;
    c->parent = b;
    BST<T>::updateHeight(b);
    return b; //�������µĸ��ڵ�
}


int main()
{
    AVL<int>obj;

    for (int i = 0; i < 15; i++)
    {
        obj.insert(i);
    }

    if (!obj.search(5))
    {
        cout << "element 5 was not found!" << endl;
    }
    else
    {
        cout << "element 5 was found!" << endl;
    }

    obj.remove(1);

    if (obj.empty())
    {
        cout << "Tree is empty" << endl;
    }

    if (!obj.search(1))
    {
        cout << "element 1 was not found!" << endl;
    }
    else
    {
        cout << "element 1 was found!" << endl;
    }


    obj.travIn(visit<int>);
    system("pause");
    return 0;
}

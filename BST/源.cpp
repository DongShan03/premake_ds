
#include"BinTree.h"

using namespace std;


template <typename T>
class BST : public BinTree<T>
{
    //��BinTree����BSTģ����
protected:
    BinNodePosi(T) _hot; //�����С��ڵ�ĸ���
public: //�����ӿڣ���virtual���Σ�ǿ��Ҫ�����������ࣨBST���֣����ݸ��ԵĹ��������д
    virtual BinNodePosi(T)& search(const T& e); //����
    virtual BinNodePosi(T) insert(const T& e); //����
    virtual bool remove(const T& e); //ɾ��
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
    return b; //�������µĸ��ڵ�
}


template <typename T> BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v) { //vΪ�ǿ��ﱲ�ڵ�
    /*DSA*/if (!v) { printf("\a\nFail to rotate a null node\n"); exit(-1); }
    BinNodePosi(T) p = v->parent; BinNodePosi(T) g = p->parent; //��v��p��g���λ�÷��������
    if (IsLChild(*p)) /* zig */
        if (IsLChild(*v)) { /* zig-zig */ //*DSA*/printf("\tzIg-zIg: ");
            p->parent = g->parent; //��������
            return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
        }
        else { /* zig-zag */  //*DSA*/printf("\tzIg-zAg: ");
            v->parent = g->parent; //��������
            return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
        }
    else  /* zag */
        if (IsRChild(*v)) { /* zag-zag */ //*DSA*/printf("\tzAg-zAg: ");
            p->parent = g->parent; //��������
            return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
        }
        else { /* zag-zig */  //*DSA*/printf("\tzAg-zIg: ");
            v->parent = g->parent; //��������
            return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
        }
}




template <typename T>
BinNodePosi(T)& BST<T>::search(const T& e)
{
    //��BST�в��ҹؼ���e
    if (!BinTree<T>::_root || e == BinTree<T>::_root->data)
    {
        _hot = NULL;
        return BinTree<T>::_root;
    } //������v������

    for (_hot = BinTree<T>::_root; ; )
    {
        //�Զ�����
        BinNodePosi(T)& c = (e < _hot->data) ? _hot->lc : _hot->rc; //ȷ������
        if (!c || e == c->data)
        {
            return c;
        }
        _hot = c; //���з��أ���������һ��
    } //�������л�ʧ�ܣ�hot��ָ��v֮���ף���ΪNULL��
} //����Ŀ��ڵ�λ�õ����ã��Ա�������롢ɾ������


template <typename T>
bool BST<T>::remove(const T& e)
{
    //��BST����ɾ���ؼ���e
    BinNodePosi(T)& x = search(e);
    if (!x)
    {
        return false; //ȷ��Ŀ����ڣ�����_hot�����ã�
    }
    removeAt(x, _hot);
    BinTree<T>::_size--; //ʵʩɾ��
    BinTree<T>::updateHeightAbove(_hot); //����_hot�����������ȵĸ߶�
    return true;
} //ɾ���ɹ�����ɷ���ֵָʾ


template <typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot)
{
    BinNodePosi(T) w = x; //ʵ�ʱ�ժ���Ľڵ㣬��ֵͬx
    BinNodePosi(T) succ = NULL; //ʵ�ʱ�ɾ���ڵ�Ľ�����
    if (!HasLChild(*x)) //��*x��������Ϊ�գ����
    {
        succ = x = x->rc; //ֱ�ӽ�*x�滻Ϊ��������
    }
    else if (!HasRChild(*x)) //��������Ϊ�գ����
    {
        succ = x = x->lc; //�ԳƵش�����ע�⣺��ʱsucc != NULL
    }
    else
    { //���������������ڣ���ѡ��x��ֱ�Ӻ����Ϊʵ�ʱ�ժ���ڵ㣬Ϊ����Ҫ
        w = w->succ(); //�����������У��ҵ�*x��ֱ�Ӻ��*w
        swap(x->data, w->data); //����*x��*w������Ԫ��
        BinNodePosi(T) u = w->parent;
        ((u == x) ? u->rc : u->lc) = succ = w->rc; //����ڵ�*w
    }
    hot = w->parent; //��¼ʵ�ʱ�ɾ���ڵ�ĸ���
    if (succ)
    {
        succ->parent = hot; //������ɾ���ڵ�Ľ�������hot����
    }
    release(w->data);
    release(w);
    return succ; //�ͷű�ժ���ڵ㣬���ؽ�����
} //release()�����ͷŸ��ӽṹ�����㷨��ֱ�ӹ�ϵ������ʵ����������



template <typename T>
BinNodePosi(T) BST<T>::insert(const T& e)
{ //���ؼ���e����BST����
    BinNodePosi(T)& x = search(e);
    if (x)
    {
        return x; //ȷ��Ŀ�겻���ڣ������_hot�����ã�
    }
    x = new BinNode<T>(e, _hot); //�����½ڵ�x����eΪ�ؼ��룬��_hotΪ��
    BinTree<T>::_size++; //����ȫ����ģ
    BinTree<T>::updateHeightAbove(x); //����x�����������ȵĸ߶�
    return x; //�²���Ľڵ㣬��ΪҶ��
} //����e�Ƿ������ԭ���У�����ʱ����x->data == e



template<typename T>//���Ը�Ϊe��(AVL,Splay,rbTree)BST�����в��ҹؼ���e
static BinNodePosi(T)& searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot)
{
    if (!v || (e == v->data))
    {
        return v;
    }
    hot = v;
    return searchIn(((e < v->data) ? v->lc : v->rc), e, hot);//����һ��ݹ����
}//����ʱ������ֵָ�����нڵ�(���߼����ͨ���ڱ�)��hotָ���丸��(�˻���Ϊ��ʼֵNULL)






int main()
{
    BST<int>obj;
    obj.insert(1);
    obj.insert(10);
    obj.insert(5);
    obj.travIn(visit<int>);
    cout << endl;
    if (!obj.search(5))
    {
        cout << "element 5 not found!" << endl;
    }
    obj.remove(1);
    if (obj.empty())
    {
        cout << "Tree is empty" << endl;
    }
    getchar();
    return 0;
}

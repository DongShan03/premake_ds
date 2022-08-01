#include"BST.h"

using namespace std;

template <typename T>
class RedBlack : public BST<T>
{
    //RedBlack��ģ����
protected:
    void solveDoubleRed(BinNodePosi(T) x); //˫������
    void solveDoubleBlack(BinNodePosi(T) x); //˫������
    int updateHeight(BinNodePosi(T) x); //���½ڵ�x�ĸ߶�
public:
    BinNodePosi(T) insert(const T& e); //���루��д��
    bool remove(const T& e); //ɾ������д��
    // BST::search()������ӿڿ�ֱ������
};


template <typename T>
BinNodePosi(T) RedBlack<T>::insert(const T& e)
{
    //��e��������
    BinNodePosi(T)& x = BST<T>::search(e);
    if (x)
    {
        return x; //ȷ��Ŀ�겻���ڣ������_hot�����ã�
    }
    x = new BinNode<T>(e, BST<T>::_hot, NULL, NULL, -1);
    BinTree<T>::_size++; //������ڵ�x����_hotΪ�����ڸ߶�-1
    BinNodePosi(T) xOld = x;
    solveDoubleRed(x);
    return xOld; //��˫�������󣬼��ɷ���
} //����e�Ƿ������ԭ���У�����ʱ����x->data == e



template <typename T>
bool RedBlack<T>::remove(const T& e)
{
    //�Ӻ������ɾ���ؼ���e
    BinNodePosi(T)& x = BST<T>::search(e);
    if (!x)
    {
        return false; //ȷ��Ŀ����ڣ�����_hot�����ã�
    }
    BinNodePosi(T) r = removeAt(x, BST<T>::_hot);
    if (!(--BinTree<T>::_size))
    {
        return true; //ʵʩɾ��
    }
    // assert: _hotĳһ���Ӹձ�ɾ�����ұ�r��ָ�ڵ㣨������NULL�����档���¼���Ƿ�ʧ�⣬������Ҫ����
    if (!BST<T>::_hot) //���ձ�ɾ�����Ǹ��ڵ㣬�����úڣ������ºڸ߶�
    {
        BinTree<T>::_root->color = RB_BLACK;
        updateHeight(BinTree<T>::_root);
        return true;
    }
    // assert: ���£�ԭx����r���طǸ���_hot�طǿ�
    if (BlackHeightUpdated(*BST<T>::_hot))
    {
        return true; //���������ȵĺ������Ȼƽ�⣬���������
    }
    if (IsRed(r)) //������rΪ�죬��ֻ������ת��
    {
        r->color = RB_BLACK;
        r->height++;
        return true;
    }
    // assert: ���£�ԭx����r����Ϊ��ɫ
    solveDoubleBlack(r);
    return true; //��˫�ڵ����󷵻�
} //��Ŀ��ڵ�����ұ�ɾ��������true�����򷵻�false



template <typename T>
void RedBlack<T>::solveDoubleBlack(BinNodePosi(T) r)
{
    BinNodePosi(T) p = r ? r->parent : BST<T>::_hot;
    if (!p)
    {
        return; //r�ĸ���
    }
    BinNodePosi(T) s = (r == p->lc) ? p->rc : p->lc; //r���ֵ�
    if (IsBlack(s))
    {
        //�ֵ�sΪ��
        BinNodePosi(T) t = NULL; //s�ĺ캢�ӣ������Һ��ӽԺ죬�������ȣ��Ժ�ʱΪNULL��
        if (IsRed(s->rc))
        {
            t = s->rc; //����
        }
        if (IsRed(s->lc))
        {
            t = s->lc; //����
        }
        if (t)
        {
            //��s�к캢�ӣ�BB-1
            RBColor oldColor = p->color; //����ԭ�������ڵ�p��ɫ������t���丸�ס��游
            // ���£�ͨ����ת��ƽ�⣬���������������Һ���Ⱦ��
            BinNodePosi(T) b = FromParentTo(*p) = BST<T>::rotateAt(t); //��ת
            if (HasLChild(*b))
            {
                b->lc->color = RB_BLACK;
                updateHeight(b->lc);
            } //����
            if (HasRChild(*b))
            {
                b->rc->color = RB_BLACK;
                updateHeight(b->rc);
            } //����
            b->color = oldColor; updateHeight(b); //���������ڵ�̳�ԭ���ڵ����ɫ
        }
        else
        {
            //��s�޺캢��
            s->color = RB_RED; s->height--; //sת��
            if (IsRed(p))
            { //BB-2R
                p->color = RB_BLACK; //pת�ڣ����ڸ߶Ȳ���
            }
            else
            {
                p->height--; //p���ֺڣ����ڸ߶��½�
                solveDoubleBlack(p); //�ݹ�����
            }
        }
    }
    else
    {
        //�ֵ�sΪ�죺BB-3
        s->color = RB_BLACK;
        p->color = RB_RED; //sת�ڣ�pת��
        BinNodePosi(T) t = IsLChild(*s) ? s->lc : s->rc; //ȡt���丸sͬ��
        BST<T>::_hot = p;
        FromParentTo(*p) = BST<T>::rotateAt(t); //��t���丸�ס��游��ƽ�����
        solveDoubleBlack(r); //��������r��˫�ڡ�����ʱ��p��ת�죬�ʺ���ֻ����BB-1��BB-2R
    }
}


/******************************************************************************************
 * RedBlack˫������㷨������ڵ�x���丸��Ϊ��ɫ�����⡣��Ϊ�����������
 *    RR-1��2����ɫ��ת��2�κڸ߶ȸ��£�1~2����ת�����ٵݹ�
 *    RR-2��3����ɫ��ת��3�κڸ߶ȸ��£�0����ת����Ҫ�ݹ�
 ******************************************************************************************/
template <typename T>
void RedBlack<T>::solveDoubleRed(BinNodePosi(T) x)
{
    //x��ǰ��Ϊ��
    if (IsRoot(*x)) //���ѣ��ݹ飩ת������������ת�ڣ������ڸ߶�Ҳ��֮����
    {
        BinTree<T>::_root->color = RB_BLACK;
        BinTree<T>::_root->height++;
        return;
    } //����x�ĸ���p�ش���
    BinNodePosi(T) p = x->parent; if (IsBlack(p)) return; //��pΪ�ڣ������ֹ����������
    BinNodePosi(T) g = p->parent; //��ȻpΪ�죬��x���游�ش��ڣ��ұ�Ϊ��ɫ
    BinNodePosi(T) u = uncle(x); //���£���x�常u����ɫ�ֱ���
    if (IsBlack(u))
    {
        //uΪ��ɫ����NULL��ʱ 
        if (IsLChild(*x) == IsLChild(*p)) //��x��pͬ�ࣨ��zIg-zIg��zAg-zAg������
        {
            p->color = RB_BLACK; //p�ɺ�ת�ڣ�x���ֺ�
        }
        else //��x��p��ࣨ��zIg-zAg��zAg-zIg������
        {
            x->color = RB_BLACK; //x�ɺ�ת�ڣ�p���ֺ�
        }
        g->color = RB_RED; //g�ض��ɺ�ת��
        // �����䱣֤�ܹ�����Ⱦɫ�������������ж϶��ò���ʧ
            // ����ת�󽫸��úڡ������ú죬��������Ⱦɫ��Ч�ʸ���
        BinNodePosi(T) gg = g->parent; //���游��great-grand parent��
        BinNodePosi(T) r = FromParentTo(*g) = BST<T>::rotateAt(x); //��������������ڵ�
        r->parent = gg; //��ԭ���游����
    }
    else
    {
        //��uΪ��ɫ 
        p->color = RB_BLACK;
        p->height++; //p�ɺ�ת��
        u->color = RB_BLACK;
        u->height++; //u�ɺ�ת��
        if (!IsRoot(*g))
        {
            g->color = RB_RED; //g���Ǹ�����ת��
        }
        solveDoubleRed(g); //��������g��������β�ݹ飬���Ż�Ϊ������ʽ��
    }
}



template <typename T>
int RedBlack<T>::updateHeight(BinNodePosi(T) x)
{
    //���½ڵ�߶�
    x->height = __max(stature(x->lc), stature(x->rc)); //����һ��ڸ߶���ȣ����ǳ���˫��
    // ������и��ڵ����Һ��ӵĺڸ߶�ͨ�����
    // ����֮����ȡ����ֵ���Ǳ�����ɾ���ڵ���ƽ����������У���ȷ���±�ɾ���ڵ㸸�׵ĺڸ߶�
    // ����rotateAt()����ݱ�ɾ���ڵ������ߣ��߶�Сһ�����ø��ڵ�ĺڸ߶�
    return IsBlack(x) ? x->height++ : x->height; //����ǰ�ڵ�Ϊ�ڣ����������
} //��ͳһ����stature(NULL) = -1����height�Ⱥڸ߶���һ�����ڲ���Ӱ�쵽�����㷨�еıȽ��ж�




int main()
{
    RedBlack<int>obj;

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

    obj.remove(5);

    if (obj.empty())
    {
        cout << "Tree is empty" << endl;
    }

    if (!obj.search(5))
    {
        cout << "element 5 was not found!" << endl;
    }
    else
    {
        cout << "element 5 was found!" << endl;
    }


    obj.travIn(visit<int>);
    system("pause");
    return 0;
}

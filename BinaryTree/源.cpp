#include<memory>

#include"Stack.h"
#include"Queue.h"


using namespace std;


#define BinNodePosi(T) BinNode<T>* //�ڵ�λ��
#define stature(p) ((p) ? (p)->height : -1) //�ڵ�߶ȣ��롰�����߶�Ϊ-1����Լ����ͳһ��
#define HeightUpdated(x)( (x).height == 1 + __max( stature( (x).lc ), stature( (x).rc ) ) ) /*�߶ȸ��³�������*/  
#define Balanced(x) ( stature( (x).lc ) == stature( (x).rc ) ) //����ƽ������
#define BalFac(x) ( stature( (x).lc ) - stature( (x).rc ) ) //ƽ������
#define AvlBalanced(x) ( ( -2 < BalFac(x) ) && ( BalFac(x) < 2 ) ) //AVLƽ������
#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //����ӵ��һ������
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //ͬʱӵ����������
#define IsLeaf(x) ( ! HasChild(x) )
#define sibling(p) ( IsLChild( * (p) ) ? (p)->parent->rc : (p)->parent->lc )/*�ֵ�*/ 
#define uncle(x) ( IsLChild( * ( (x)->parent ) ) ? (x)->parent->parent->rc : (x)->parent->parent->lc )/*����*/ 
#define FromParentTo(x)  ( IsRoot(x) ? BinTree<T>::_root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )/*���Ը��׵�����*/
#define IsBlack(p) ( ! (p) || ( RB_BLACK == (p)->color ) ) //�ⲿ�ڵ�Ҳ�����ڽڵ�
#define IsRed(p) ( ! IsBlack(p) ) //�Ǻڼ���
#define BlackHeightUpdated(x) ( ( stature( (x).lc ) == stature( (x).rc ) ) && ( (x).height == ( IsRed(& x) ? stature( (x).lc ) : stature( (x).lc ) + 1 ) ) ) /*RedBlack�߶ȸ�������*/


typedef enum
{
    RB_RED,
    RB_BLACK
} RBColor; //�ڵ���ɫ


template <typename T>
struct Cleaner
{
    static void clean(T x)
    {   //�൱�ڵݹ��
#ifdef _DEBUG
        static int n = 0;
        if (7 > strlen(typeid (T).name()))
        {
            //��������һ�ź��ԣ�ֻ�����������
            printf("\t<%s>[%d]=", typeid (T).name(), ++n);
            print(x);
            printf(" purged\n");
        }
#endif
    }
};


static int dice(int range)
{
    return rand() % range;
} //ȡ[0, range)�е��������


static int dice(int lo, int hi)
{
    return lo + rand() % (hi - lo);
} //ȡ[lo, hi)�е��������


static float dice(float range)
{
    return rand() % (1000 * (int)range) / (float)1000.;
}


static double dice(double range)
{
    return rand() % (1000 * (int)range) / (double)1000.;
}


static char dice()
{
    return (char)(32 + rand() % 96);
}


template <typename T>
struct Cleaner<T*>
{
    static void clean(T* x)
    {
        if (x)
        {
            delete x;
        } //������а���ָ�룬�ݹ��ͷ�

#ifdef _DEBUG
        static int n = 0;
        printf("\t<%s>[%d] released\n", typeid (T*).name(), ++n);
#endif
    }
};


template <typename T>
void release(T x)
{
    Cleaner<T>::clean(x);
}


template <typename T>
struct BinNode
{
    //�������ڵ�ģ����
    // ��Ա��Ϊ���������ͳһ���ţ����߿ɸ�����Ҫ��һ����װ��

    T data; //��ֵ
    BinNodePosi(T) parent;
    BinNodePosi(T) lc;
    BinNodePosi(T) rc; //���ڵ㼰���Һ���
    int height; //�߶ȣ�ͨ�ã�
    int npl; //Null Path Length����ʽ�ѣ�Ҳ��ֱ����height���棩
    RBColor color; //��ɫ���������

 // ���캯��

    BinNode() :
        parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) { }

    BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
        int h = 0, int l = 1, RBColor c = RB_RED) :
        data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) { }

    // �����ӿ�

    int size(); //ͳ�Ƶ�ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ

    BinNodePosi(T) insertAsLC(T const&); //��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�

    BinNodePosi(T) insertAsRC(T const&); //��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�

    BinNodePosi(T) succ(); //ȡ��ǰ�ڵ��ֱ�Ӻ��

    template <typename VST>
    void travLevel(VST&); //������α���

    template <typename VST>
    void travPre(VST&); //�����������

    template <typename VST>
    void travIn(VST&); //�����������

    template <typename VST>
    void travPost(VST&); //�����������

 // �Ƚ������е�����������һ���������в��䣩
    bool operator< (BinNode const& bn)
    {
        return data < bn.data;
    } //С��

    bool operator== (BinNode const& bn)
    {
        return data == bn.data;
    } //����

};


template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const& e)
{
    return lc = new BinNode(e, this);
} //��e��Ϊ��ǰ�ڵ�����Ӳ��������


template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const& e)
{
    return rc = new BinNode(e, this);
} //��e��Ϊ��ǰ�ڵ���Һ��Ӳ��������


template <typename T>
int BinNode<T>::size()
{ //ͳ�Ƶ�ǰ�ڵ���������������Ϊ����������ģ
    int s = 1; //���뱾��
    if (lc)
    {
        s += lc->size(); //�ݹ������������ģ
    }
    if (rc)
    {
        s += rc->size(); //�ݹ������������ģ
    }
    return s;
}


template <typename T>
BinNodePosi(T) BinNode<T>::succ()
{ //��λ�ڵ�v��ֱ�Ӻ��
    BinNodePosi(T) s = this; //��¼��̵���ʱ����
    if (rc)
    { //�����Һ��ӣ���ֱ�Ӻ�̱����������У�����ؾ���
        s = rc; //��������
        while (HasLChild(*s))
        {
            s = s->lc; //�����С���Ľڵ�
        }
    }
    else
    { //����ֱ�Ӻ��Ӧ�ǡ�����ǰ�ڵ���������������е�������ȡ�������ؾ���
        while (IsRChild(*s))
        {
            s = s->parent; //������������֧�����ϳ����Ϸ��ƶ�
        }
        s = s->parent; //����ٳ����Ϸ��ƶ�һ�������ִ�ֱ�Ӻ�̣�������ڣ�
    }
    return s;
}


template <typename T> template <typename VST> //Ԫ�����͡�������
void BinNode<T>::travIn(VST& visit)
{ //��������������㷨ͳһ���
    switch (rand() % 5)
    { //�˴������ѡ���������ԣ�������ѡ��
    case 1:
    {
        travIn_I1(this, visit);
        break; //������#1
    }
    case 2:
    {
        travIn_I2(this, visit);
        break; //������#2
    }
    case 3:
    {
        travIn_I3(this, visit);
        break; //������#3
    }
    case 4:
    {
        travIn_I4(this, visit);
        break; //������#4
    }
    default:
    {
        travIn_R(this, visit);
        break; //�ݹ��
    }
    }
}


template <typename T> //�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ�
static void goAlongVine(BinNodePosi(T) x, Stack<BinNodePosi(T)>& S)
{
    while (x)
    {
        S.push(x);
        x = x->lc;
    } //��ǰ�ڵ���ջ���漴������֧���룬����ֱ��������
}


template <typename T, typename VST> //Ԫ�����͡�������
void travIn_I1(BinNodePosi(T) x, VST& visit)
{ //��������������㷨��������#1��
    Stack<BinNodePosi(T)> S; //����ջ
    while (true)
    {
        goAlongVine(x, S); //�ӵ�ǰ�ڵ������������ջ
        if (S.empty())
        {
            break; //ֱ�����нڵ㴦�����
        }
        x = S.pop();
        visit(x->data); //����ջ���ڵ㲢����֮
        x = x->rc; //ת��������
    }
}


template <typename T, typename VST> //Ԫ�����͡�������
void travIn_I2(BinNodePosi(T) x, VST& visit)
{ //��������������㷨��������#2��
    Stack<BinNodePosi(T)> S; //����ջ
    while (true)
    {
        if (x)
        {
            S.push(x); //���ڵ��ջ
            x = x->lc; //�������������
        }
        else if (!S.empty())
        {
            x = S.pop(); //��δ���ʵ�������Ƚڵ���ջ
            visit(x->data); //���ʸ����Ƚڵ�
            x = x->rc; //�������ȵ�������
        }
        else
        {
            break; //�������
        }
    }
}


template <typename T, typename VST> //Ԫ�����͡�������
void travIn_I3(BinNodePosi(T) x, VST& visit)
{ //��������������㷨��������#3�����踨��ջ��
    bool backtrack = false; //ǰһ���Ƿ�մ����������ݡ���ʡȥջ����O(1)�����ռ�
    while (true)
    {
        if (!backtrack && HasLChild(*x)) //�����������Ҳ��Ǹոջ��ݣ���
        {
            x = x->lc; //�������������
        }
        else
        { //���򡪡�����������ոջ��ݣ��൱������������
            visit(x->data); //���ʸýڵ�
            if (HasRChild(*x))
            { //�����������ǿգ���
                x = x->rc; //������������������
                backtrack = false; //���رջ��ݱ�־
            }
            else
            { //���������գ���
                if (!(x = x->succ()))
                {
                    break; //���ݣ����ִ�ĩ�ڵ�ʱ���˳����أ�
                }
                backtrack = true; //�����û��ݱ�־
            }
        }
    }
}


template <typename T, typename VST> //Ԫ�����͡�������
void travIn_I4(BinNodePosi(T) x, VST& visit)
{ //���������������������#4������ջ���־λ��
    while (true)
    {
        if (HasLChild(*x)) //��������������
        {
            x = x->lc; //�������������
        }
        else
        { //����
            visit(x->data); //���ʵ�ǰ�ڵ㣬��
            while (!HasRChild(*x)) //���ϵ������ҷ�֧��
            {
                if (!(x = x->succ()))
                {
                    return; //������ֱ�Ӻ�̣���û�к�̵�ĩ�ڵ㴦��ֱ���˳���
                }
                else
                {
                    visit(x->data); //�����µĵ�ǰ�ڵ�
                }
            }
            x = x->rc; //��ֱ�����ҷ�֧����ת��ǿյ�������
        }
    }
}


template <typename T, typename VST> //Ԫ�����͡�������
void travIn_R(BinNodePosi(T) x, VST& visit)
{ //��������������㷨���ݹ�棩
    if (!x)
    {
        return;
    }
    travIn_R(x->lc, visit);
    visit(x->data);
    travIn_R(x->rc, visit);
}


template <typename T> template <typename VST> //Ԫ�����͡�������
void BinNode<T>::travLevel(VST& visit)
{ //��������α����㷨
    Queue<BinNodePosi(T)> Q; //��������
    Q.enqueue(this); //���ڵ����
    while (!Q.empty())
    { //�ڶ����ٴα��֮ǰ����������
        BinNodePosi(T) x = Q.dequeue();
        visit(x->data); //ȡ�����׽ڵ㲢����֮
        if (HasLChild(*x))
        {
            Q.enqueue(x->lc); //�������
        }
        if (HasRChild(*x))
        {
            Q.enqueue(x->rc); //�Һ������
        }
    }
}


template <typename T> template <typename VST> //Ԫ�����͡�������
void BinNode<T>::travPost(VST& visit)
{ //��������������㷨ͳһ���
    switch (rand() % 2)
    { //�˴������ѡ���������ԣ�������ѡ��
    case 1:
    {
        travPost_I(this, visit);
        break; //������
    }
    default:
    {
        travPost_R(this, visit);
        break; //�ݹ��
    }
    }
}



template <typename T> //����Sջ���ڵ�Ϊ���������У��ҵ�������ɼ�Ҷ�ڵ�
static void gotoLeftmostLeaf(Stack<BinNodePosi(T)>& S)
{ //��;�����ڵ�������ջ
    while (BinNodePosi(T) x = S.top()) //�Զ����£�������鵱ǰ�ڵ㣨��ջ����
    {
        if (HasLChild(*x))
        { //����������
            if (HasRChild(*x))
            {
                S.push(x->rc); //�����Һ��ӣ�������ջ
            }
            S.push(x->lc); //Ȼ���ת������
        }
        else //ʵ������
        {
            S.push(x->rc); //������
        }
    }
    S.pop(); //����֮ǰ������ջ���Ŀսڵ�
}

template <typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST& visit)
{
    //�������ĺ�������������棩
    Stack<BinNodePosi(T)> S; //����ջ
    if (x)
    {
        S.push(x); //���ڵ���ջ
    }
    while (!S.empty())
    { //xʼ��Ϊ��ǰ�ڵ�
        if (S.top() != x->parent) //��ջ����x֮������Ϊ���֣�
        {
            gotoLeftmostLeaf(S); //�����������������ҵ�HLVFL���൱�ڵݹ����룩
        }
        x = S.pop();
        visit(x->data); //����ջ������ǰһ�ڵ�֮��̣���������֮
    }
}


template <typename T, typename VST> //Ԫ�����͡�������
void travPost_R(BinNodePosi(T) x, VST& visit)
{ //��������������㷨���ݹ�棩
    if (!x)
    {
        return;
    }
    travPost_R(x->lc, visit);
    travPost_R(x->rc, visit);
    visit(x->data);
}


template <typename T> template <typename VST> //Ԫ�����͡�������
void BinNode<T>::travPre(VST& visit)
{ //��������������㷨ͳһ���
    switch (rand() % 3)
    { //�˴������ѡ���������ԣ�������ѡ��
    case 1:
    {
        travPre_I1(this, visit);
        break; //������#1
    }
    case 2:
    {
        travPre_I2(this, visit);
        break; //������#2
    }
    default:
    {
        travPre_R(this, visit);
        break; //�ݹ��
    }
    }
}


template <typename T, typename VST> //Ԫ�����͡�������
void travPre_I1(BinNodePosi(T) x, VST& visit)
{ //��������������㷨��������#1��
    Stack<BinNodePosi(T)> S; //����ջ
    if (x)
    {
        S.push(x); //���ڵ���ջ
    }
    while (!S.empty())
    { //��ջ���֮ǰ����ѭ��
        x = S.pop();
        visit(x->data); //���������ʵ�ǰ�ڵ㣬��ǿպ��ӵ���ջ����Ϊ���Һ���
        if (HasRChild(*x))
        {
            S.push(x->rc);
        }
        if (HasLChild(*x))
        {
            S.push(x->lc);
        }
    }
}


//�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ㣻��;�ڵ���������������
template <typename T, typename VST> //Ԫ�����͡�������
static void visitAlongVine(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)>& S)
{
    while (x)
    {
        visit(x->data); //���ʵ�ǰ�ڵ�
        S.push(x->rc); //�Һ�����ջ�ݴ棨���Ż���ͨ���жϣ�����յ��Һ�����ջ��
        x = x->lc;  //�����֧����һ��
    }
}


template <typename T, typename VST> //Ԫ�����͡�������
void travPre_I2(BinNodePosi(T) x, VST& visit)
{ //��������������㷨��������#2��
    Stack<BinNodePosi(T)> S; //����ջ
    while (true)
    {
        visitAlongVine(x, visit, S); //�ӵ�ǰ�ڵ��������������
        if (S.empty())
        {
            break; //ֱ��ջ��
        }
        x = S.pop(); //������һ�������
    }
}


template <typename T, typename VST> //Ԫ�����͡�������
void travPre_R(BinNodePosi(T) x, VST& visit)
{ //��������������㷨���ݹ�棩
    if (!x)
    {
        return;
    }
    visit(x->data);
    travPre_R(x->lc, visit);
    travPre_R(x->rc, visit);
}


template <typename T> class BinTree
{
    //������ģ����
protected:
    int _size;

    BinNodePosi(T) _root; //��ģ�����ڵ�

    virtual int updateHeight(BinNodePosi(T) x); //���½ڵ�x�ĸ߶�

    void updateHeightAbove(BinNodePosi(T) x); //���½ڵ�x�������ȵĸ߶�

public:

    BinTree() : _size(0), _root(NULL)
    {

    } //���캯��

    ~BinTree()
    {
        if (0 < _size)
        {
            remove(_root);
        }
    } //��������

    int size() const
    {
        return _size;
    } //��ģ

    bool empty() const
    {
        return !_root;
    } //�п�

    BinNodePosi(T) root() const
    {
        return _root;
    } //����

    BinNodePosi(T) insertAsRoot(T const& e); //������ڵ�

    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e); //e��Ϊx�����ӣ�ԭ�ޣ�����

    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e); //e��Ϊx���Һ��ӣ�ԭ�ޣ�����

    BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>*& T); //T��Ϊx����������

    BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>*& T); //T��Ϊx����������

    int remove(BinNodePosi(T) x); //ɾ����λ��x���ڵ�Ϊ�������������ظ�����ԭ�ȵĹ�ģ

    BinTree<T>* secede(BinNodePosi(T) x); //������x�ӵ�ǰ����ժ����������ת��Ϊһ�ö�������

    template <typename VST> //������
    void travLevel(VST& visit)
    {
        if (_root)
        {
            _root->travLevel(visit);
        }
    } //��α���

    template <typename VST> //������
    void travPre(VST& visit)
    {
        if (_root)
        {
            _root->travPre(visit);
        }
    } //�������

    template <typename VST> //������
    void travIn(VST& visit)
    {
        if (_root)
        {
            _root->travIn(visit);
        }
    } //�������

    template <typename VST> //������
    void travPost(VST& visit)
    {
        if (_root)
        {
            _root->travPost(visit);
        }
    } //�������

    bool operator< (BinTree<T> const& t) //�Ƚ������������в��䣩
    {
        return _root && t._root && lt(_root, t._root);
    }

    bool operator== (BinTree<T> const& t) //�е���
    {
        return _root && t._root && (_root == t._root);
    }

}; //BinTree


template <typename T> //���������������㷨����S�����ڵ�x�����������룬S�����ÿ�
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>*& S)
{ //x->lc == NULL
    if (x->lc = S->_root)
    {
        x->lc->parent = x; //����
    }
    _size += S->_size;
    updateHeightAbove(x); //����ȫ����ģ��x�������ȵĸ߶�
    S->_root = NULL;
    S->_size = 0;
    release(S);
    S = NULL;
    return x; //�ͷ�ԭ�������ؽ���λ��
}


template <typename T> //���������������㷨����S�����ڵ�x�����������룬S�����ÿ�
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>*& S)
{
    //x->rc == NULL
    if (x->rc = S->_root)
    {
        x->rc->parent = x; //����
    }
    _size += S->_size;
    updateHeightAbove(x); //����ȫ����ģ��x�������ȵĸ߶�
    S->_root = NULL;
    S->_size = 0;
    release(S);
    S = NULL;
    return x; //�ͷ�ԭ�������ؽ���λ��
}


template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e)
{
    _size = 1; return _root = new BinNode<T>(e);
} //��e�������ڵ����յĶ�����


template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e)
{
    _size++;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;
} //e����Ϊx������


template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e)
{
    _size++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
} //e����Ϊx���Һ���


template <typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
int BinTree<T>::remove(BinNodePosi(T) x)
{
    //assert: xΪ�������еĺϷ�λ��
    FromParentTo(*x) = NULL; //�ж����Ը��ڵ��ָ��
    updateHeightAbove(x->parent); //�������ȸ߶�
    int n = removeAt(x);
    _size -= n;
    return n; //ɾ������x�����¹�ģ������ɾ���ڵ�����
}


template <typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
static int removeAt(BinNodePosi(T) x)
{ //assert: xΪ�������еĺϷ�λ��
    if (!x)
    {
        return 0; //�ݹ��������
    }
    int n = 1 + removeAt(x->lc) + removeAt(x->rc); //�ݹ��ͷ���������
    release(x->data);
    release(x);
    return n; //�ͷű�ժ���ڵ㣬������ɾ���ڵ�����
} //release()�����ͷŸ��ӽṹ�����㷨��ֱ�ӹ�ϵ


template <typename T> //���������������㷨��������x�ӵ�ǰ����ժ���������װΪһ�ö�����������
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x)
{
    //assert: xΪ�������еĺϷ�λ��
    FromParentTo(*x) = NULL; //�ж����Ը��ڵ��ָ��
    updateHeightAbove(x->parent); //����ԭ�����������ȵĸ߶�
    BinTree<T>* S = new BinTree<T>;
    S->_root = x;
    x->parent = NULL; //������xΪ��
    S->_size = x->size();
    _size -= S->_size;
    return S; //���¹�ģ�����ط������������
}


template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x) //���½ڵ�x�߶�
{
    return x->height = 1 + __max(stature(x->lc), stature(x->rc));
} //���������������


template <typename T> void BinTree<T>::updateHeightAbove(BinNodePosi(T) x) //���¸߶�
{
    while (x)
    {
        updateHeight(x);
        x = x->parent;
    }
} //��x�����������������ȡ����Ż�


template <typename T>
struct Double //�������󣺱���һ��T�����
{
    virtual void operator() (T& e)
    {
        e *= 2;
    }
}; //����T��ֱ�ӱ���


template <typename T>
struct Hailstone
{ //�������󣺰���Hailstone����ת��һ��T�����
    virtual void operator() (T& e)
    { //����T��ֱ������������
        int step = 0; //ת�����貽��
        while (1 != e)
        { //���桢ż��ת����ֱ��Ϊ1
            (e % 2) ? e = 3 * e + 1 : e /= 2;
            step++;
        }
        e = step; //����ת����������
    }
};






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


int testID = 0; //���Ա��


// ������������߶�Ϊh�Ķ�����
template <typename T> bool randomBinTree(BinTree<T>& bt, BinNodePosi(T) x, int h)
{
    if (0 >= h)
    {
        return false; //����h��
    }
    if (0 < dice(h)) //��1/h�ĸ�����ֹ��ǰ��֧������
    {
        randomBinTree(bt, bt.insertAsLC(x, dice((T)h * h * h)), h - 1);
    }
    if (0 < dice(h)) //��1/h�ĸ�����ֹ��ǰ��֧������
    {
        randomBinTree(bt, bt.insertAsRC(x, dice((T)h * h * h)), h - 1);
    }
    return true;
}


// �ڶ����������ȷ��һ���ڵ�λ��
template <typename T> BinNodePosi(T) randomPosiInBinTree(BinNodePosi(T) root)
{
    if (!HasChild(*root))
    {
        return root;
    }
    if (!HasLChild(*root))
    {
        return dice(6) ? randomPosiInBinTree(root->rc) : root;
    }
    if (!HasRChild(*root))
    {
        return dice(6) ? randomPosiInBinTree(root->lc) : root;
    }
    return dice(2) ? randomPosiInBinTree(root->lc) : randomPosiInBinTree(root->rc);
}






//һ���򵥵Ĳ�������
int main()
{
    BinTree<int>bt;
    //�����������Ϊ1
    BinNode<int>* root = bt.insertAsRoot(1);
    BinNode<int>* LeOfRoot = bt.insertAsLC(root, 2);
    BinNode<int>* RiOfRoot = bt.insertAsRC(root, 3);

    //���õڶ���ڵ�  ����Ϊ 4 5 6 7
    BinNode<int>* four, * five, * six, * seven;
    four = bt.insertAsLC(LeOfRoot, 4);
    five = bt.insertAsRC(LeOfRoot, 5);
    six = bt.insertAsLC(RiOfRoot, 6);
    seven = bt.insertAsRC(RiOfRoot, 7);

    //����������

    //�������
    bt.travPre(visit<int>);
    cout << endl;

    //�������
    bt.travIn(visit<int>);
    cout << endl;

    //�������
    bt.travPost(visit<int>);
    cout << endl;

    //�������
    bt.travLevel(visit<int>);
    cout << endl;

    //������ɾ���ڵ�
    bt.remove(seven);
    //�ٴα�������������ɾ��Ч��
    bt.travLevel(visit<int>);
    cout << endl;

    //���ڵ�Ϊ3������ժ����Ȼ�����ԭ���Ķ������Լ��¶�����
    BinTree<int>* newTree = bt.secede(RiOfRoot);
    bt.travLevel(visit<int>);
    cout << endl;
    newTree->travLevel(visit<int>);
    cout << endl;


    //�������Ĺ�ģ
    cout << "size:" << bt.size() << endl;


    system("pause");
    return 0;

}

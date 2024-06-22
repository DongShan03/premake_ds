#pragma once
#include<memory>
#include "../../Stack/headers/stack.h"
#include "../../Queue/headers/queue.h"

using namespace std;


#define BinNodePosi(T) BinNode<T>* //节点位置
#define stature(p) ((p) ? (p)->height : -1) //节点高度（与“空树高度为-1”的约定相统一）
#define HeightUpdated(x)( (x).height == 1 + __max( stature( (x).lc ), stature( (x).rc ) ) ) /*高度更新常规条件*/  
#define Balanced(x) ( stature( (x).lc ) == stature( (x).rc ) ) //理想平衡条件
#define BalFac(x) ( stature( (x).lc ) - stature( (x).rc ) ) //平衡因子
#define AvlBalanced(x) ( ( -2 < BalFac(x) ) && ( BalFac(x) < 2 ) ) //AVL平衡条件
#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //至少拥有一个孩子
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //同时拥有两个孩子
#define IsLeaf(x) ( ! HasChild(x) )
#define sibling(p) ( IsLChild( * (p) ) ? (p)->parent->rc : (p)->parent->lc )/*兄弟*/ 
#define uncle(x) ( IsLChild( * ( (x)->parent ) ) ? (x)->parent->parent->rc : (x)->parent->parent->lc )/*叔叔*/ 
#define FromParentTo(x)  ( IsRoot(x) ? BinTree<T>::_root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )/*来自父亲的引用*/
#define IsBlack(p) ( ! (p) || ( RB_BLACK == (p)->color ) ) //外部节点也视作黑节点
#define IsRed(p) ( ! IsBlack(p) ) //非黑即红
#define BlackHeightUpdated(x) ( ( stature( (x).lc ) == stature( (x).rc ) ) && ( (x).height == ( IsRed(& x) ? stature( (x).lc ) : stature( (x).lc ) + 1 ) ) ) /*RedBlack高度更新条件*/


typedef enum
{
    RB_RED,
    RB_BLACK
} RBColor; //节点颜色


#ifndef CLEAN_DEBUG
#define CLEAN_DEBUG
template <typename T>
struct Cleaner
{
    static void clean(T x)
    {   //相当于递归基
#ifdef _DEBUG
        static int n = 0;
        if (7 > strlen(typeid (T).name()))
        {
            //复杂类型一概忽略，只输出基本类型
            printf("\t<%s>[%d]=", typeid (T).name(), ++n);
            print(x);
            printf(" purged\n");
        }
#endif
    }
};

template <typename T>
struct Cleaner<T*>
{
    static void clean(T* x)
    {
        if (x)
        {
            delete x;
        } //如果其中包含指针，递归释放

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

#endif


static int dice(int range)
{
    return rand() % range;
} //取[0, range)中的随机整数


static int dice(int lo, int hi)
{
    return lo + rand() % (hi - lo);
} //取[lo, hi)中的随机整数


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
struct BinNode
{
    //二叉树节点模板类
    // 成员（为简化描述起见统一开放，读者可根据需要进一步封装）

    T data; //数值
    BinNodePosi(T) parent;
    BinNodePosi(T) lc;
    BinNodePosi(T) rc; //父节点及左、右孩子
    int height; //高度（通用）
    int npl; //Null Path Length（左式堆，也可直接用height代替）
    RBColor color; //颜色（红黑树）

 // 构造函数

    BinNode() :
        parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) { }

    BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
        int h = 0, int l = 1, RBColor c = RB_RED) :
        data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) { }

    // 操作接口

    int size(); //统计当前节点后代总数，亦即以其为根的子树的规模

    BinNodePosi(T) insertAsLC(T const&); //作为当前节点的左孩子插入新节点

    BinNodePosi(T) insertAsRC(T const&); //作为当前节点的右孩子插入新节点

    BinNodePosi(T) succ(); //取当前节点的直接后继

    template <typename VST>
    void travLevel(VST&); //子树层次遍历

    template <typename VST>
    void travPre(VST&); //子树先序遍历

    template <typename VST>
    void travIn(VST&); //子树中序遍历

    template <typename VST>
    void travPost(VST&); //子树后序遍历

 // 比较器、判等器（各列其一，其余自行补充）
    bool operator< (BinNode const& bn)
    {
        return data < bn.data;
    } //小于

    bool operator== (BinNode const& bn)
    {
        return data == bn.data;
    } //等于

};


#include "goAlongVine.h"
#include "gotoLeftmostLeaf.h"
#include "visitAlongVine.h"
#include "bninsert.h"
#include "bnsize.h"
#include "bnsucc.h"
#include "bntravIn.h"
#include "bntravPre.h"
#include "bntravPost.h"
#include "bntravLevel.h"
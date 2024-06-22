#include "../../BST/headers/bst.h"//基于BST实现Splay树

using namespace std;


template<typename T>
class Splay :public BST<T>
{
	//由BST派生的Splay树模板类
protected:
	BinNodePosi(T)splay(BinNodePosi(T) v);//将节点v伸至根
public:
	BinNodePosi(T)& search(const T& e);//查找(重写)
	BinNodePosi(T) insert(const T& e);//插入(重写)
	bool remove(const T& e);//删除(重写)
};


template<typename NodePosi>inline //在节点*p与*lc(可能为空)之间建立父(左)子关系
void attachAsLChild(NodePosi p, NodePosi lc)
{
	p->lc = lc;
	if (lc)
	{
		lc->parent = p;
	}
}


template<typename NodePosi> //在节点*p与*rc(可能为空)之间建立父(右)子关系
void attachAsRChild(NodePosi p, NodePosi rc)
{
	p->rc = rc;
	if (rc)
	{
		rc->parent = p;
	}
}

#include "splay.h"
#include "search.h"
#include "remove.h"
#include "insert.h"
#pragma once
#include "../../BST/headers/bst.h"//基于BST实现Splay树

using namespace std;


template<typename T>
class Splay :public BST<T>
{
	//由BST派生的Splay树模板类
protected:
	BinNodePosi(T) splay(BinNodePosi(T) v);//将节点v伸至根
public:
	BinNodePosi(T)& search(const T& e);//查找(重写)
	BinNodePosi(T) insert(const T& e);//插入(重写)
	bool remove(const T& e);//删除(重写)
};




#include "splay.h"
#include "search.h"
#include "remove.h"
#include "insert.h"
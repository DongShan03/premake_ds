#include"BST.h"//����BSTʵ��Splay��


using namespace std;


template<typename T>
class Splay :public BST<T>
{
	//��BST������Splay��ģ����
protected:
	BinNodePosi(T)splay(BinNodePosi(T) v);//���ڵ�v������
public:
	BinNodePosi(T)& search(const T& e);//����(��д)
	BinNodePosi(T) insert(const T& e);//����(��д)
	bool remove(const T& e);//ɾ��(��д)
};



template<typename NodePosi>inline //�ڽڵ�*p��*lc(����Ϊ��)֮�佨����(��)�ӹ�ϵ
void attachAsLChild(NodePosi p, NodePosi lc)
{
	p->lc = lc;
	if (lc)
	{
		lc->parent = p;
	}
}


template<typename NodePosi> //�ڽڵ�*p��*rc(����Ϊ��)֮�佨����(��)�ӹ�ϵ
void attachAsRChild(NodePosi p, NodePosi rc)
{
	p->rc = rc;
	if (rc)
	{
		rc->parent = p;
	}
}


template<typename T>//Splay����չ�㷨:�ӽڵ�v���������չ
BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v)
{
	//vΪ��������ʶ���Ҫ��չ�Ľڵ��λ��
	if (!v)
	{
		return NULL;
	}
	BinNodePosi(T) p;//*v�ĸ���
	BinNodePosi(T) g;//*v���游
	while ((p = v->parent) && (g = p->parent))
	{
		//���¶��ϣ�������*v����˫����չ
		BinNodePosi(T) gg = g->parent;//ÿ��֮��*v����ԭ���游(great-grand parent)Ϊ��
		if (IsLChild(*v))
		{
			if (IsLChild(*p))
			{
				//zig-zig
				attachAsLChild(g, p->rc);
				attachAsLChild(p, v->rc);
				attachAsRChild(p, g);
				attachAsRChild(v, p);
			}
			else
			{
				//zig-zag
				attachAsLChild(p, v->rc);
				attachAsRChild(g, v->lc);
				attachAsLChild(v, g);
				attachAsRChild(v, p);
			}
		}
		else if (IsRChild(*p))
		{
			//zag-zag
			attachAsRChild(g, p->lc);
			attachAsRChild(p, v->lc);
			attachAsLChild(p, g);
			attachAsLChild(v, p);
		}
		else
		{
			//zag-zig
			attachAsRChild(p, v->lc);
			attachAsLChild(g, v->rc);
			attachAsRChild(v, g);
			attachAsLChild(v, p);
		}
		if (!gg)
		{
			v->parent = NULL;//��*vԭ�ȵ����游*gg�����ڣ���*vӦ��Ϊ���ڵ�����
		}
		else//����*gg�˺�Ӧ����*v��Ϊ���ӻ����Һ���
		{
			(g == gg->lc) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
		}
		BinTree<T>::updateHeight(g);
		BinTree<T>::updateHeight(p);
		BinTree<T>::updateHeight(v);
	}//˫����չ����ʱ������g==NULL������p���ܲ�Ϊ��
	if (p = v->parent)
	{
		//���p����ǿգ��������һ�ε���
		if (IsLChild(*v))
		{
			attachAsLChild(p, v->rc);
			attachAsRChild(v, p);
		}
		else
		{
			attachAsRChild(p, v->lc);
			attachAsLChild(v, p);
		}
		BinTree<T>::updateHeight(p);
		BinTree<T>::updateHeight(v);
	}
	v->parent = NULL;
	return v;
}//����֮��������ӦΪ����չ�Ľڵ㣬�ʷ��ؽڵ��λ���Ա��ϲ㺯����������


template<typename T>
BinNodePosi(T)& Splay<T>::search(const T& e)
{
	//����չ���в���e
	BinNodePosi(T) p = searchIn(BinTree<T>::_root, e, BST<T>::_hot = NULL);
	BinTree<T>::_root = Splay<T>::splay(p ? p : BST<T>::_hot);//�����һ�������ʵĽڵ���չ������
	return BinTree<T>::_root;
}//������BST��ͬ�����۲��ҳɹ����_root��ָ�����ձ����ʹ��Ľڵ�


template<typename T>
BinNodePosi(T) Splay<T>::insert(const T& e)
{
	//���ؼ���e������չ����
	if (!BinTree<T>::_root)
	{
		BinTree<T>::_size++;
		return BinTree<T>::_root = new BinNode<T>(e);//����ԭ��Ϊ�յ��˻����
	}
	if (e == Splay<T>::search(e)->data)
	{
		return BinTree<T>::_root;//ȷ��Ŀ��ڵ㲻����
	}
	BinTree<T>::_size++;
	BinNodePosi(T) t = BinTree<T>::_root;//�����½ڵ㣬���µ���<=7��ָ������ɲ����ع�
	if (BinTree<T>::_root->data < e)
	{
		//�����¸�����t��t->rcΪ���Һ���
		t->parent = BinTree<T>::_root = new BinNode<T>(e, NULL, t, t->rc);//2+3��
		if (HasRChild(*t))
		{
			t->rc->parent = BinTree<T>::_root;
			t->rc = NULL;//<=2��
		}
	}
	else//�����¸�����t->lc��tΪ���Һ���
	{
		t->parent = BinTree<T>::_root = new BinNode<T>(e, NULL, t->lc, t);//2+3��
		if (HasLChild(*t))
		{
			t->lc->parent = BinTree<T>::_root;
			t->lc = NULL;//<=2��
		}
	}
	BinTree<T>::updateHeightAbove(t);//����t��������(ʵ����ֻ��_rootһ��)�ĸ߶�
	return BinTree<T>::_root;//�½ڵ��Ȼ��������������֮
}//����e�Ƿ������ԭ��֮��,����ʱ����_root->data=e


template<typename T>
bool Splay<T>::remove(const T& e)//����չ����ɾ���ؼ���e
{
	if (!BinTree<T>::_root || (e != Splay<T>::search(e)->data))
	{
		//�����ջ���Ŀ�겻���ڣ����޷�ɾ��
		return false;
	}
	BinNodePosi(T)w = BinTree<T>::_root;//assert������search()֮��Ľڵ�e�Ѿ�����չ������
	if (!HasLChild(*BinTree<T>::_root))//������������ֱ��ɾ��
	{
		BinTree<T>::_root = BinTree<T>::_root->rc;
		if (BinTree<T>::_root)
		{
			BinTree<T>::_root->parent = NULL;
		}
	}
	else if (!HasRChild(*BinTree<T>::_root))//������������ֱ��ɾ��
	{
		BinTree<T>::_root = BinTree<T>::_root->lc;
		if (BinTree<T>::_root)
		{
			BinTree<T>::_root->parent = NULL;
		}
	}
	else
	{
		//����������ͬʱ����
		BinNodePosi(T)lTree = BinTree<T>::_root->lc;
		lTree->parent = NULL;
		BinTree<T>::_root->lc = NULL;//��ʱ���������г�
		BinTree<T>::_root = BinTree<T>::_root->rc;
		BinTree<T>::_root->parent = NULL;//ֻ����������
		Splay<T>::search(w->data);//��ԭ����ΪĿ����һ�Σ��ض�ʧ�ܵģ�����
		BinTree<T>::_root->lc = lTree;
		//assert:���ˣ�����������С�ڵ��Ȼ������������������Ϊû����ͬ�ڵ㣬���������ؿգ�����
		lTree->parent = BinTree<T>::_root;//ֻ�轫�������ӻ�ԭλ����
	}
	release(w->data);
	release(w);
	BinTree<T>::_size--;//ֻ�轫�������ӻ�ԭλ����
	if (BinTree<T>::_root)
	{
		BinTree<T>::updateHeight(BinTree<T>::_root);//�˺�����ǿգ��������ĸ߶���Ҫ����
	}
	return true;//���سɹ���־
}//��Ŀ��ڵ�����ұ�ɾ��������True���򷵻�False


int main()
{
	Splay<int>obj;

	for (int i = 0; i < 15; i++)
	{
		obj.insert(i);
	}
	obj.travIn(visit<int>);
	if (obj.search(5)->data != 5)
	{
		cout << "element 5 was not found!" << endl;
	}
	else
	{
		cout << "element 5 was found!" << endl;
	}

	obj.remove(1);
	cout << "After remove element with value 1." << endl;
	obj.travIn(visit<int>);
	if (obj.empty())
	{
		cout << "Tree is empty" << endl;
	}
	cout << endl;
	if (obj.search(1)->data != 1)
	{
		cout << "element 1 was not found!" << endl;
	}
	else
	{
		cout << "element 1 was found!" << endl;
	}

	obj.insert(10000);
	cout << "After insert element with value 10000." << endl;
	obj.travIn(visit<int>);
	system("pause");
	return 0;
}

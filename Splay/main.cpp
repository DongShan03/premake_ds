#include "splaytree.h"//基于BST实现Splay树


int main()
{
	Splay<int>obj;

	for (int i = 0; i < 15; i++)
	{
		obj.insert(i);
	}
	obj.travIn(bt_visit<int>);
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
	obj.travIn(bt_visit<int>);
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
	obj.travIn(bt_visit<int>);
	cout << endl;
	cout << "The test of splay tree is over!" << endl;
	return 0;
}

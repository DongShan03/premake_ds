#include "Vector/headers/vector.h"
#include "List/headers/list.h"
#include "Stack/headers/stack.h"
#include "Queue/headers/queue.h"
#include "HashTable/headers/hashtable.h"
#include "Heap/headers/heap.h"
#include "BinaryTree/headers/bintree.h"
#include "BST/headers/bst.h"
// #include "Splay/headers/splay.h"
#include "AVL/headers/avl.h"
#include "BTree/headers/btree.h"
#include "RBTree/headers/rbtree.h"
#include "Bitmap/headers/bitmap.h"

//sadsds
int main()
{
    BST<int>obj;
    for (int i = 0; i < 15; i++)
    {
        obj.insert(i);
    }
    obj.travIn(bt_visit<int>);
    cout << endl;
    if (!obj.search(5))
    {
        cout << "element 5 not found!" << endl;
    }
    obj.remove(1);
    obj.travIn(bt_visit<int>);
    cout << endl;
    if (obj.empty())
    {
        cout << "Tree is empty" << endl;
    }
    cout << "The test of BST is over!" << endl;
    return 0;
}
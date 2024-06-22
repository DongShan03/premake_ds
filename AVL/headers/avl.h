#include "../../BST/headers/bst.h"

using namespace std;





template <typename T>
class AVL : public BST<T>
{
    //由BST派生AVL树模板类
public:
    BinNodePosi(T) connect34(
        BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
        BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3
    );

    BinNodePosi(T) rotateAt(BinNodePosi(T) x);//对x及其父亲祖父做统一的旋转调整

    BinNodePosi(T) insert(const T& e); //插入（重写）

    bool remove(const T& e); //删除（重写）
};

#include "connect34.h"
#include "insert.h"
#include "remove.h"
#include "rotateAt.h"
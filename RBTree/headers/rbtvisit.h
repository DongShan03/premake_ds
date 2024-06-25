template<typename T>
void rbt_visit(T& elem)
{
    cout << elem;
};

template <typename T, typename VST> //元素类型、操作器
void rbtravIn(BinNodePosi(T) x, VST& visit)
{ //二叉树中序遍历算法（迭代版#1）
    Stack<BinNodePosi(T)> S; //辅助栈
    while (true)
    {
        goAlongVine(x, S); //从当前节点出发，逐批入栈
        if (S.empty())
        {
            break; //直至所有节点处理完毕
        }
        x = S.pop();
        visit(x->data); //弹出栈顶节点并访问之
        if (IsRed(x)) cout<< "r" << "\t";
        else cout<< "b" << "\t";
        x = x->rc; //转向右子树
    }
};

template <typename T, typename VST> //元素类型、操作器
void rbtravPre(BinNodePosi(T) x, VST& visit)
{ //二叉树先序遍历算法（迭代版#1）
    Stack<BinNodePosi(T)> S; //辅助栈
    if (x)
    {
        S.push(x); //根节点入栈
    }
    while (!S.empty())
    { //在栈变空之前反复循环
        x = S.pop();
        visit(x->data); //弹出栈顶节点并访问之
        if (IsRed(x)) cout<< "r" << "\t";
        else cout<< "b" << "\t";
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

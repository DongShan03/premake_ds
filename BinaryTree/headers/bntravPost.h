template <typename T> template <typename VST> //元素类型、操作器
void BinNode<T>::travPost(VST& visit)
{ //二叉树后序遍历算法统一入口
    switch (rand() % 2)
    { //此处暂随机选择以做测试，共两种选择
    case 1:
    {
        travPost_I(this, visit);
        break; //迭代版
    }
    default:
    {
        travPost_R(this, visit);
        break; //递归版
    }
    }
}


template <typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST& visit)
{
    //二叉树的后序遍历（迭代版）
    Stack<BinNodePosi(T)> S; //辅助栈
    if (x)
    {
        S.push(x); //根节点入栈
    }
    while (!S.empty())
    { //x始终为当前节点
        if (S.top() != x->parent) //若栈顶非x之父（而为右兄）
        {
            gotoLeftmostLeaf(S); //则在其右兄子树中找到HLVFL（相当于递归深入）
        }
        x = S.pop();
        visit(x->data); //弹出栈顶（即前一节点之后继），并访问之
    }
}


template <typename T, typename VST> //元素类型、操作器
void travPost_R(BinNodePosi(T) x, VST& visit)
{ //二叉树后序遍历算法（递归版）
    if (!x)
    {
        return;
    }
    travPost_R(x->lc, visit);
    travPost_R(x->rc, visit);
    visit(x->data);
}

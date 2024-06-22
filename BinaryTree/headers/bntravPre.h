template <typename T> template <typename VST> //元素类型、操作器
void BinNode<T>::travPre(VST& visit)
{ //二叉树先序遍历算法统一入口
    switch (rand() % 3)
    { //此处暂随机选择以做测试，共三种选择
    case 1:
    {
        travPre_I1(this, visit);
        break; //迭代版#1
    }
    case 2:
    {
        travPre_I2(this, visit);
        break; //迭代版#2
    }
    default:
    {
        travPre_R(this, visit);
        break; //递归版
    }
    }
}


template <typename T, typename VST> //元素类型、操作器
void travPre_I1(BinNodePosi(T) x, VST& visit)
{ //二叉树先序遍历算法（迭代版#1）
    Stack<BinNodePosi(T)> S; //辅助栈
    if (x)
    {
        S.push(x); //根节点入栈
    }
    while (!S.empty())
    { //在栈变空之前反复循环
        x = S.pop();
        visit(x->data); //弹出并访问当前节点，其非空孩子的入栈次序为先右后左
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

template <typename T, typename VST> //元素类型、操作器
void travPre_I2(BinNodePosi(T) x, VST& visit)
{ //二叉树先序遍历算法（迭代版#2）
    Stack<BinNodePosi(T)> S; //辅助栈
    while (true)
    {
        visitAlongVine(x, visit, S); //从当前节点出发，逐批访问
        if (S.empty())
        {
            break; //直到栈空
        }
        x = S.pop(); //弹出下一批的起点
    }
}


template <typename T, typename VST> //元素类型、操作器
void travPre_R(BinNodePosi(T) x, VST& visit)
{ //二叉树先序遍历算法（递归版）
    if (!x)
    {
        return;
    }
    visit(x->data);
    travPre_R(x->lc, visit);
    travPre_R(x->rc, visit);
}
template <typename T>
void Vector<T>::traverse(void (*visit) (T&)) //借助函数指针机制
{
    for (int i = 0; i < _size; i++)
    {
        visit(_elem[i]);
    }
    cout << endl;
} //遍历向量



//这里使用了函数指针机制


template <typename T> template <typename VST> //元素类型、操作器
void Vector<T>::traverse(VST& visit) //借助函数对象机制
{
    for (int i = 1; i <= _size; i++)
    {
        visit(_elem[i - 1]);
        //控制每一行输出20个元素
        if ((i) % 10 == 0)
        {
            printf("\n");
        }
    }
    cout << endl;
} //遍历向量
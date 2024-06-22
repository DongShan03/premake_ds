template <typename T>
struct Increase //函数对象：递增一个T类对象
{
    virtual void operator() (T& e)
    {
        e++;
    }
}; //假设T可直接递增或已重载++


template <typename T>
void increase(Vector<T>& V) //统一递增向量中的各元素
{
    V.traverse(Increase<T>());
}; //以Increase<T>()为基本操作进行遍历
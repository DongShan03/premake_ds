
template <typename T>
static bool list_lt(T* a, T* b)
{
    return list_lt(*a, *b);
} //less than


template <typename T>
static bool list_lt(T& a, T& b)
{
    return a < b;
} //less than
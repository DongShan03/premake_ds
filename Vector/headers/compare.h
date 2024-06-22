template <typename T>
static bool vector_lt(T* a, T* b)
{
    return vector_lt(*a, *b);
} //less than


template <typename T>
static bool vector_lt(T& a, T& b)
{
    return a < b;
} //less than


template <typename T>
static bool vector_eq(T* a, T* b)
{
    return vector_eq(*a, *b);
} //equal


template <typename T>
static bool vector_eq(T& a, T& b)
{
    return a == b;
} //equal
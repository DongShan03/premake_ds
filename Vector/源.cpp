#include<iostream>
#include<algorithm>
#include<ctime>

using namespace std;

typedef int Rank; //��

#define DEFAULT_CAPACITY  3 //Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ����

template <typename T>
class Vector
{
    //����ģ����
public:
    //��ģ��������������
    Rank _size;

    int _capacity;

    T* _elem;

    void copyFrom(T const* A, Rank lo, Rank hi); //������������A[lo, hi)

    void expand(); //�ռ䲻��ʱ����

    void shrink(); //װ�����ӹ�Сʱѹ��

    bool bubble(Rank lo, Rank hi); //ɨ�轻��

    void bubbleSort(Rank lo, Rank hi); //���������㷨

    Rank max(Rank lo, Rank hi); //ѡȡ���Ԫ��

    void selectionSort(Rank lo, Rank hi); //ѡ�������㷨

    void merge(Rank lo, Rank mi, Rank hi); //�鲢�㷨

    void mergeSort(Rank lo, Rank hi); //�鲢�����㷨

    void heapSort(Rank lo, Rank hi); //�������Ժ�����ȫ�ѽ��⣩

    Rank partition(Rank lo, Rank hi); //��㹹���㷨

    void quickSort(Rank lo, Rank hi); //���������㷨

    void shellSort(Rank lo, Rank hi); //ϣ�������㷨

public:
    // ���캯��
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) //����Ϊc����ģΪs������Ԫ�س�ʼΪv
    {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v);
    } //s<=c

    Vector(T const* A, Rank n)
    {
        copyFrom(A, 0, n);
    } //�������帴��

    Vector(T const* A, Rank lo, Rank hi)
    {
        copyFrom(A, lo, hi);
    } //����

    Vector(Vector<T> const& V)
    {
        copyFrom(V._elem, 0, V._size);
    } //�������帴��

    Vector(Vector<T> const& V, Rank lo, Rank hi)
    {
        copyFrom(V._elem, lo, hi);
    } //����

    // ��������
    ~Vector()
    {
        delete[] _elem;
    } //�ͷ��ڲ��ռ�

    // ֻ�����ʽӿ�
    Rank size() const
    {
        return _size;
    } //��ģ

    bool empty() const
    {
        return !_size;
    } //�п�

    Rank find(T const& e) const
    {
        return find(e, 0, _size);
    } //���������������

    Rank find(T const& e, Rank lo, Rank hi) const; //���������������

    Rank search(T const& e) const //���������������
    {
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }

    Rank search(T const& e, Rank lo, Rank hi) const; //���������������

    // ��д���ʽӿ�
    T& operator[] (Rank r); //�����±������������������������ʽ���ø�Ԫ��

    const T& operator[] (Rank r) const; //����������ֵ�����ذ汾

    Vector<T>& operator= (Vector<T> const&); //���ظ�ֵ���������Ա�ֱ�ӿ�¡����

    T remove(Rank r); //ɾ����Ϊr��Ԫ��

    int remove(Rank lo, Rank hi); //ɾ����������[lo, hi)֮�ڵ�Ԫ��

    Rank insert(Rank r, T const& e); //����Ԫ��

    Rank insert(T const& e)
    {
        return insert(_size, e);
    } //Ĭ����ΪĩԪ�ز���

    void sort(Rank lo, Rank hi); //��[lo, hi)����

    void sort()
    {
        sort(0, _size);
    } //��������

    void unsort(Rank lo, Rank hi); //��[lo, hi)����

    void unsort()
    {
        unsort(0, _size);
    } //��������

    int deduplicate(); //����ȥ��

    int uniquify(); //����ȥ��

    // ����
    void traverse(void (*) (T&)); //������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�

    template <typename VST>
    void traverse(VST&); //������ʹ�ú������󣬿�ȫ�����޸ģ�

}; //Vector


class Fib
{ //Fibonacci������
private:
    int f, g; //f = fib(k - 1), g = fib(k)����Ϊint�ͣ��ܿ�ͻ���ֵ���
public:
    Fib(int n) //��ʼ��Ϊ��С��n����СFibonacci��
    {
        f = 1;
        g = 0;
        while (g < n)
        {
            next();
        }
    } //fib(-1), fib(0)��O(log_phi(n))ʱ��

    int get()
    {
        return g;
    } //��ȡ��ǰFibonacci�O(1)ʱ��

    int next()
    {
        g += f;
        f = g - f;
        return g;
    } //ת����һFibonacci�O(1)ʱ��

    int prev()
    {
        f = g - f;
        g -= f;
        return g;
    } //ת����һFibonacci�O(1)ʱ��
};


template <typename T>
struct Increase //�������󣺵���һ��T�����
{
    virtual void operator() (T& e)
    {
        e++;
    }
}; //����T��ֱ�ӵ�����������++


template <typename T>
void increase(Vector<T>& V) //ͳһ���������еĸ�Ԫ��
{
    V.traverse(Increase<T>());
} //��Increase<T>()Ϊ�����������б���


template <typename T>
void permute(Vector<T>& V)
{ //�������������ʹ��Ԫ�صȸ��ʳ����ڸ�λ��
    for (int i = V.size(); i > 0; i--) //�Ժ���ǰ
    {
        swap(V[i - 1], V[rand() % i]); //V[i - 1]��V[0, i)��ĳһ���Ԫ�ؽ���
    }
}


template <typename T>
static bool lt(T* a, T* b)
{
    return lt(*a, *b);
} //less than


template <typename T>
static bool lt(T& a, T& b)
{
    return a < b;
} //less than


template <typename T>
static bool eq(T* a, T* b)
{
    return eq(*a, *b);
} //equal


template <typename T>
static bool eq(T& a, T& b)
{
    return a == b;
} //equal


template <typename T> //Ԫ������
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{ //����������A[lo, hi)Ϊ������������
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0; //����ռ䣬��ģ����
    while (lo < hi) //A[lo, hi)�ڵ�Ԫ����һ
    {
        _elem[_size++] = A[lo++]; //������_elem[0, hi - lo)
    }
}


template <typename T>
void Vector<T>::expand()
{ //�����ռ䲻��ʱ����
    if (_size < _capacity)
    {
        return; //��δ��Աʱ����������
    }
    if (_capacity < DEFAULT_CAPACITY)
    {
        _capacity = DEFAULT_CAPACITY; //��������С����
    }
    T* oldElem = _elem;
    _elem = new T[_capacity <<= 1]; //�����ӱ�
    for (int i = 0; i < _size; i++)
    {
        _elem[i] = oldElem[i]; //����ԭ�������ݣ�TΪ�������ͣ��������ظ�ֵ������'='��
    }
    /*DSA*/
    //printf("\n_ELEM [%x]*%d/%d expanded and shift to [%x]*%d/%d\n", oldElem, _size, _capacity/2, _elem, _size, _capacity);
    delete[] oldElem; //�ͷ�ԭ�ռ�
}


template <typename T>
void Vector<T>::shrink()
{ //װ�����ӹ�Сʱѹ��������ռ�ռ�
    if (_capacity < DEFAULT_CAPACITY << 1)
    {
        return; //����������DEFAULT_CAPACITY����
    }
    if (_size << 2 > _capacity)
    {
        return; //��25%Ϊ��
    }
    T* oldElem = _elem;
    _elem = new T[_capacity >>= 1]; //��������
    for (int i = 0; i < _size; i++)
    {
        _elem[i] = oldElem[i]; //����ԭ��������
    }
    delete[] oldElem; //�ͷ�ԭ�ռ�
}


template <typename T> //����������˳����ң��������һ��Ԫ��e��λ�ã�ʧ��ʱ������lo - 1
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const
{ //assert: 0 <= lo < hi <= _size
    while ((lo < hi--) && (e != _elem[hi])); //�Ӻ���ǰ��˳�����
    return hi; //��hi < lo������ζ��ʧ�ܣ�����hi������Ԫ�ص���
}


template <typename T> //����������������Ծ�棩
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{ //assert: 0 <= lo < hi <= size
    for (Rank last = --hi; lo < hi; hi = last)
    {
        for (Rank i = last = lo; i < hi; i++)
        {
            if (_elem[i] > _elem[i + 1]) //��������
            {
                swap(_elem[last = i], _elem[i + 1]); //������ʹ�ֲ�����
            }
        }
    }
}


template <typename T>
Rank Vector<T>::max(Rank lo, Rank hi)
{ //��[lo, hi]���ҳ������
    Rank mx = hi;
    while (lo < hi--) //����ɨ��
    {
        if (_elem[hi] > _elem[mx]) //���ϸ�Ƚ�
        {
            mx = hi; //������max�ж��ʱ��֤�������ȣ�������֤selectionSort�ȶ�
        }
    }
    return mx;
}


template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) //һ��ɨ�轻��
{
    bool sorted = true;//���������־
    while (++lo < hi)
    {
        //�������ң���һ����������Ԫ��
        if (_elem[lo - 1] > _elem[lo])
        {
            //����������ζ����δ�������򣬲���Ҫͨ������ʹ�þֲ�����
            sorted = false;
            swap(_elem[lo - 1], _elem[lo]);
        }
    }
    return sorted;//���������־
}


template <typename T> //����ѡ������
void Vector<T>::selectionSort(Rank lo, Rank hi)
{ //0 <= lo < hi <= size
    while (lo < --hi)
    {
        swap(_elem[max(lo, hi)], _elem[hi]); //��[hi]��[lo, hi]�е�����߽���
    }
}


template <typename T> //�������������䣩�Ĺ鲢
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{ //���������������[lo, mi)��[mi, hi)
    T* A = _elem + lo; //�ϲ��������A[0, hi - lo) = _elem[lo, hi)
    int lb = mi - lo;
    T* B = new T[lb]; //ǰ������B[0, lb) = _elem[lo, mi)
    for (Rank i = 0; i < lb; i++)
    {
        B[i] = A[i]; //����ǰ������
    }
    int lc = hi - mi;
    T* C = _elem + mi; //��������C[0, lc) = _elem[mi, hi)
    for (Rank i = 0, j = 0, k = 0; j < lb; ) //�鲢��������B��C��Ԫ����ȡ����С��
    {
        A[i++] = (lc <= k || B[j] <= C[k]) ? B[j++] : C[k++]; //�������A��
    }
    delete[] B; //�ͷ���ʱ�ռ�B
}


template <typename T> //�����鲢����
void Vector<T>::mergeSort(Rank lo, Rank hi)
{ //0 <= lo < hi <= size
    /*DSA*/ //printf ( "\tMERGEsort [%3d, %3d)\n", lo , hi );
    if (hi - lo < 2)
    {
        return; //��Ԫ��������Ȼ���򣬷���...
    }
    int mi = (lo + hi) / 2; //���е�Ϊ��
    mergeSort(lo, mi);
    mergeSort(mi, hi); //�ֱ�����
    merge(lo, mi, hi); //�鲢
}



template <typename T> //��㹹���㷨��ͨ������Ԫ��λ�ù�������[lo, hi)����㣬����������
Rank Vector<T>::partition(Rank lo, Rank hi)
{ //�汾A��������ʽ
    swap(_elem[lo], _elem[lo + rand() % (hi - lo)]); //��ѡһ��Ԫ������Ԫ�ؽ���
    hi--;
    T pivot = _elem[lo]; //����Ԫ��Ϊ��ѡ��㡪�������Ͻ�������Ч�����ѡȡ
    while (lo < hi)
    { //�����������˽�������м�ɨ��
        while ((lo < hi) && (pivot <= _elem[hi])) //�ڲ�С��pivot��ǰ����
        {
            hi--; //������չ�Ҷ�������
        }
        _elem[lo] = _elem[hi]; //С��pivot�߹������������
        while ((lo < hi) && (_elem[lo] <= pivot)) //�ڲ�����pivot��ǰ����
        {
            lo++; //������չ���������
        }
        _elem[hi] = _elem[lo]; //����pivot�߹����Ҳ�������
    } //assert: lo == hi
    _elem[lo] = pivot; //�����ݵ�����¼����ǰ����������֮��
    return lo; //����������
}


template <typename T> //������������
void Vector<T>::quickSort(Rank lo, Rank hi)
{ //0 <= lo < hi <= size
    /*DSA*/ //printf ( "\tQUICKsort [%3d, %3d)\n", lo, hi );
    if (hi - lo < 2)
    {
        return; //��Ԫ��������Ȼ���򣬷���...
    }
    Rank mi = partition(lo, hi); //��[lo, hi)�ڹ������
    quickSort(lo, mi); //��ǰ׺�ݹ�����
    quickSort(mi + 1, hi); //�Ժ�׺�ݹ�����
}


template <typename T> //����ϣ������
void Vector<T>::shellSort(Rank lo, Rank hi)
{ //0 <= lo < hi <= size <= 2^30
    /*DSA*/ printf("\tSHELLsort [%3d, %3d)\n", lo, hi);
    for (int d = 0x3FFFFFFF; 0 < d; d >>= 1) //PS Sequence: { 1, 3, 7, 15, ..., 1073741823 }
    {
        for (int j = lo + d; j < hi; j++)
        { //for each j in [lo+d, hi)
            T x = _elem[j];
            int i = j - d;
            while (lo <= i && _elem[i] > x)
            {
                _elem[i + d] = _elem[i];
                i -= d;
            }
            _elem[i + d] = x; //insert [j] into its subsequence
        }
    }
}

// ���ֲ����㷨���汾A��������������������[lo, hi)�ڲ���Ԫ��e��0 <= lo <= hi <= _size
template <typename T>
static Rank binSearchA(T* S, T const& e, Rank lo, Rank hi)
{
    /*DSA*/
    //printf("BIN search (A)\n");
    while (lo < hi)
    { //ÿ����������Ҫ�����αȽ��жϣ���������֧
        /*DSA*/
        for (int i = 0; i < lo; i++)
        {
            printf("");
        }
        if (lo >= 0)
        {
            for (int i = lo; i < hi; i++)
            {
                printf("");
            }
        }
        //printf("\n");
        Rank mi = (lo + hi) >> 1; //���е�Ϊ��㣨�����ȵ��۰룬��Ч�ڿ��֮��ֵ��ʾ�����ƣ�
        if (e < S[mi])
        {
            hi = mi; //����ǰ���[lo, mi)��������
        }
        else
        {
            if (S[mi] < e)
            {
                lo = mi + 1; //�������(mi, hi)��������
            }
            else
            {
                return mi; //��mi������
            }
        }
        if (lo >= hi)
        {
            for (int i = 0; i < mi; i++)
            {
                printf("");
            }
            if (mi >= 0)
            {
                printf("");
            }
            else
            {
                printf("");
            }
        }
    } //�ɹ����ҿ�����ǰ��ֹ
    return -1; //����ʧ��

} //�ж������Ԫ��ʱ�����ܱ�֤����������ߣ�����ʧ��ʱ���򵥵ط���-1��������ָʾʧ�ܵ�λ��


// ���ֲ����㷨���汾B��������������������[lo, hi)�ڲ���Ԫ��e��0 <= lo < hi <= _size
template <typename T>
static Rank binSearchB(T* S, T const& e, Rank lo, Rank hi)
{

    while (1 < hi - lo)
    { //ÿ������������һ�αȽ��жϣ���������֧���ɹ����Ҳ�����ǰ��ֹ
        Rank mi = (lo + hi) >> 1; //���е�Ϊ��㣨�����ȵ��۰룬��Ч�ڿ��֮��ֵ��ʾ�����ƣ�
        (e < S[mi]) ? hi = mi : lo = mi; //���ȽϺ�ȷ������[lo, mi)��[mi, hi)
    } //����ʱhi = lo + 1�������������һ��Ԫ��A[lo]
    return e < S[lo] ? lo - 1 : lo; //����λ�ã����ǲ�����e�������
} //�ж������Ԫ��ʱ�����ܱ�֤����������ߣ�����ʧ��ʱ���򵥵ط���-1��������ָʾʧ�ܵ�λ��



// ���ֲ����㷨���汾C��������������������[lo, hi)�ڲ���Ԫ��e��0 <= lo <= hi <= _size
template <typename T>
static Rank binSearchC(T* S, T const& e, Rank lo, Rank hi)
{
    while (lo < hi)
    { //ÿ������������һ�αȽ��жϣ���������֧
        Rank mi = (lo + hi) >> 1; //���е�Ϊ��㣨�����ȵ��۰룬��Ч�ڿ��֮��ֵ��ʾ�����ƣ�
        (e < S[mi]) ? hi = mi : lo = mi + 1; //���ȽϺ�ȷ������[lo, mi)��(mi, hi)
    } //�ɹ����Ҳ�����ǰ��ֹ
    return lo - 1; //ѭ������ʱ��loΪ����e��Ԫ�ص���С�ȣ���lo - 1��������e��Ԫ�ص������
} //�ж������Ԫ��ʱ�����ܱ�֤����������ߣ�����ʧ��ʱ���ܹ�����ʧ�ܵ�λ��



template <typename T> //����������������[lo, hi)�ڣ�ȷ��������e�����һ���ڵ����
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const
{ //assert: 0 <= lo < hi <= _size
    return (rand() % 2) ? //����50%�ĸ������ʹ�ö��ֲ��һ�Fibonacci����
        binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}


template <typename T>
T& Vector<T>::operator[] (Rank r) //�����±������
{
    return _elem[r];
} // assert: 0 <= r < _size


template <typename T>
const T& Vector<T>::operator[] (Rank r) const //����������ֵ
{
    return _elem[r];
} // assert: 0 <= r < _size


template <typename T>
T Vector<T>::remove(Rank r)
{ //ɾ����������Ϊr��Ԫ�أ�0 <= r < size
    T e = _elem[r]; //���ݱ�ɾ��Ԫ��
    remove(r, r + 1); //��������ɾ���㷨����Ч�ڶ�����[r, r + 1)��ɾ��
    return e; //���ر�ɾ��Ԫ��
}


template <typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{ //ɾ������[lo, hi)
    if (lo == hi)
    {
        return 0; //����Ч�ʿ��ǣ����������˻����������remove(0, 0)
    }
    while (hi < _size)
    {
        _elem[lo++] = _elem[hi++]; //[hi, _size)˳��ǰ��hi - lo����Ԫ
    }
    _size = lo; //���¹�ģ��ֱ�Ӷ���β��[lo, _size = hi)����
    shrink(); //���б�Ҫ��������
    return hi - lo; //���ر�ɾ��Ԫ�ص���Ŀ
}


template <typename T>
Vector<T>& Vector<T>::operator= (Vector<T> const& V)
{ //���
    if (_elem)
    {
        delete[] _elem; //�ͷ�ԭ������
    }
    copyFrom(V._elem, 0, V.size()); //���帴��
    return *this; //���ص�ǰ��������ã��Ա���ʽ��ֵ
}


template <typename T> //��e��Ϊ��ΪrԪ�ز���
Rank Vector<T>::insert(Rank r, T const& e)
{ //assert: 0 <= r <= size
    expand(); //���б�Ҫ������
    for (int i = _size; i > r; i--)
    {
        _elem[i] = _elem[i - 1]; //�Ժ���ǰ�����Ԫ��˳�κ���һ����Ԫ
    }
    _elem[r] = e; _size++; //������Ԫ�ز���������
    return r; //������
}


template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi)
{ //�ȸ��������������[lo, hi)
    T* V = _elem + lo; //��������_elem[lo, hi)������һ����V[0, hi - lo)
    for (Rank i = hi - lo; i > 0; i--) //�Ժ���ǰ
    {
        swap(V[i - 1], V[rand() % i]); //��V[i - 1]��V[0, i)��ĳһԪ���������
    }
}


template <typename T>
void Vector<T>::sort(Rank lo, Rank hi)
{ //��������[lo, hi)����
    switch (rand() % 6)
    {
    case 1:
    {
        bubbleSort(lo, hi);
        break; //��������
    }
    case 2:
    {
        selectionSort(lo, hi);
        break; //ѡ������ϰ�⣩
    }
    case 3:
    {
        mergeSort(lo, hi);
        break; //�鲢����
    }
    case 4:
    {
        quickSort(lo, hi);
        break; //�������򣨵�14�£�
    }
    default:
    {
        shellSort(lo, hi);
        break; //ϣ�����򣨵�14�£�
    }
    } //���ѡ���㷨�Գ�ֲ��ԡ�ʵ��ʱ���Ӿ���������ص����ȷ��������
}


template <typename T>
int Vector<T>::deduplicate()
{ //ɾ�������������ظ�Ԫ�أ���Ч�棩
    int oldSize = _size; //��¼ԭ��ģ
    Rank i = 1; //��_elem[1]��ʼ
    while (i < _size) //��ǰ�����һ�����Ԫ��_elem[i]
    {
        if (find(_elem[i], 0, i) < 0) //��ǰ׺[0,i)��Ѱ����֮��ͬ�ߣ�����һ����
            i++; //������ͬ�������������
        else
            remove(i); //����ɾ����ǰԪ��
    }
    return oldSize - _size; //��ɾ��Ԫ������
}


template <typename T>
int Vector<T>::uniquify()
{ //���������ظ�Ԫ���޳��㷨����Ч�棩
    Rank i = 0, j = 0; //���Ի��조���ڡ�Ԫ�ص���
    while (++j < _size) //��һɨ�裬ֱ��ĩԪ��
    {
        if (_elem[i] != _elem[j]) //������ͬ��
            _elem[++i] = _elem[j]; //���ֲ�ͬԪ��ʱ����ǰ����������ǰ���Ҳ�
    }
    _size = ++i; shrink(); //ֱ�ӽس�β������Ԫ��
    return j - i; //������ģ�仯��������ɾ��Ԫ������
}


template <typename T>
void Vector<T>::traverse(void (*visit) (T&)) //��������ָ�����
{
    for (int i = 0; i < _size; i++)
    {
        visit(_elem[i]);
    }
    cout << endl;
} //��������



//����ʹ���˺���ָ�����
template<typename T>
void visit(T& elem)
{
    cout << elem << '\t';
}

template <typename T> template <typename VST> //Ԫ�����͡�������
void Vector<T>::traverse(VST& visit) //���������������
{
    for (int i = 1; i <= _size; i++)
    {
        visit(_elem[i - 1]);
        //����ÿһ�����20��Ԫ��
        if ((i) % 10 == 0)
        {
            printf("\n");
        }
    }
    cout << endl;
} //��������


template <typename T>
static Rank fibSearchA(T* S, T const& e, Rank lo, Rank hi)
{
    /*DSA*/
    //printf("FIB search (A)\n");
    //��O(log_phi(n = hi - lo)ʱ�䴴��Fib����
    for (Fib fib(hi - lo); lo < hi; )
    {  //Fib�����Ʊ��飻�˺�ÿ��������һ�αȽϡ�������֧
        /*DSA*/
        for (int i = 0; i < lo; i++)
        {
            // printf("     ");
        }
        if (lo >= 0)
        {
            for (int i = lo; i < hi; i++)
            {
                // printf("....^");
            }
        }
        else
        {
            // printf("<<<<|");
        }
        //printf("\n");
        while (hi - lo < fib.get())
        {
            fib.prev(); //�Ժ���ǰ˳����ң���̯O(1)��
        }
        Rank mi = lo + fib.get() - 1; //ȷ������Fib(k) - 1�����
        if (e < S[mi])
        {
            hi = mi; //����ǰ���[lo, mi)��������
        }
        else
        {
            if (S[mi] < e)
            {
                lo = mi + 1; //�������(mi, hi)��������
            }
            else
            {
                return mi; //��mi������
            }
        }
        /*DSA*/
        if (lo >= hi)
        {
            for (int i = 0; i < mi; i++)
            {
                // printf("     ");
            }
            if (mi >= 0)
            {
                //  printf("....|\n");
            }
            else
            {
                // printf("<<<<|\n");
            }
        }
    } //�ɹ����ҿ�����ǰ��ֹ
    return -1; //����ʧ��
} //�ж������Ԫ��ʱ�����ܱ�֤����������ߣ�ʧ��ʱ���򵥵ط���-1��������ָʾʧ�ܵ�λ��



// Fibonacci�����㷨���汾B��������������������[lo, hi)�ڲ���Ԫ��e��0 <= lo <= hi <= _size
template <typename T>
static Rank fibSearchB(T* S, T const& e, Rank lo, Rank hi)
{
    //printf("FIB search (B)\n");
    for (Fib fib(hi - lo); lo < hi; )
    { //Fib�����Ʊ��� 
        while (hi - lo < fib.get())
        {
            fib.prev(); //�Ժ���ǰ˳����ң���̯O(1)��
        }
        Rank mi = lo + fib.get() - 1; //ȷ������Fib(k) - 1�����
        (e < S[mi]) ? hi = mi : lo = mi + 1; //�ȽϺ�ȷ������ǰ���[lo, mi)�����(mi, hi)
    } //�ɹ����Ҳ�����ǰ��ֹ
    return --lo; //ѭ������ʱ��loΪ����e��Ԫ�ص���С�ȣ���lo - 1��������e��Ԫ�ص������
} //�ж������Ԫ��ʱ�����ܱ�֤������������ߣ�����ʧ��ʱ���ܹ�����ʧ�ܵ�λ��



int main()
{
    Vector<int>obj;
    //���������*100������������
    srand((unsigned)time(NULL));
    for (int i = 0; i < 20; i++)
    {
        obj.insert(rand() % 1000);
    }

    cout << "------------------01.Initial vector:-----------------" << endl;
    obj.traverse(visit);
    cout << endl;

    cout << "------------------02.Insert a value:-----------------" << endl;
    obj.insert(1);
    obj.traverse(visit);
    cout << endl;

    cout << "------------------03.After sorted:-------------------" << endl;
    obj.sort();
    obj.traverse(visit);
    cout << endl;

    cout << "------------------04.After deduplicated:---------------" << endl;
    obj.deduplicate();
    obj.traverse(visit);
    cout << endl;

    cout << "------------------05.After shuffled:----------------" << endl;
    obj.unsort();
    obj.traverse(visit);
    cout << endl;

    cout << "------------------06.After uniquify:----------------" << endl;
    obj.insert(1, 2);
    obj.uniquify();
    obj.traverse(visit);
    cout << endl;

    cout << "------------------07.Search a element 100 one by one:----------------" << endl;
    int res = obj.find(100);
    cout << (res == -1 ? "not found!" : "founded") << endl;
    cout << endl;

    cout << "------------------08.Search a element 19 by fib search01:----------------" << endl;
    //define an array with 20 elements
    int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    res = fibSearchA(a, 19, 0, sizeof(a) / sizeof(int));
    cout << (res == -1 ? "not found!" : "founded") << endl;
    cout << endl;


    cout << "------------------09.Search a element 19 by fib search02:----------------" << endl;
    //define an array with 20 elements
    int b[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    res = fibSearchB(b, 19, 0, sizeof(b) / sizeof(int));
    cout << (res == -1 ? "not found!" : "founded") << endl;
    cout << endl;

    cout << "------------------10.Search a element 19 by binary search01:----------------" << endl;
    //define an array with 20 elements
    int c[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    res = binSearchA(b, 19, 0, sizeof(c) / sizeof(int));
    cout << (res == -1 ? "not found!" : "founded") << endl;
    cout << endl;


    cout << "------------------11.Search a element 19 by binary search02:----------------" << endl;
    //define an array with 20 elements
    int d[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    res = binSearchB(d, 19, 0, sizeof(d) / sizeof(int));
    cout << (res == -1 ? "not found!" : "founded") << endl;
    cout << endl;

    cout << "------------------12.Search a element 19 by binary search03:----------------" << endl;
    //define an array with 20 elements
    int e[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    res = binSearchC(e, 19, 0, sizeof(e) / sizeof(int));
    cout << (res == -1 ? "not found!" : "founded") << endl;
    cout << endl;


    system("pause");
    return 0;
}

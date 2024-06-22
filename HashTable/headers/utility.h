
template <typename T> struct Cleaner {
	static void clean(T x) { //相当于递归基
#ifdef _DEBUG
		static int n = 0;
		if (7 > strlen(typeid (T).name())) { //复杂类型一概忽略，只输出基本类型
			printf("\t<%s>[%d]=", typeid (T).name(), ++n);
			print(x);
			printf(" purged\n");
		}
#endif
	}
};

template <typename T>
struct Cleaner<T*>
{
	static void clean(T* x)
	{
		if (x)
		{
			delete x;
		} //如果其中包含指针，递归释放
#ifdef _DEBUG
		static int n = 0;
#endif
	}
};


template <typename T>
void release(T x)
{
	Cleaner<T>::clean(x);
}



bool isPrime(int x)//素数是指一个大于一的自然数除了1和它自身外，不能被其他自然数整除的数
{
	if (x == 2)
	{
		return true;
	}
	for (int i = 2; i < x; i++)
	{
		if (x % i == 0)
		{
			return false;
		}
	}
	return true;
}

int primeNLT(int c, int n)
{
	int d = c;
	//在[c,n)之中取最小的素数
	while (d < n)
	{
		if (!isPrime(d))
		{
			d++;
		}
		else
		{
			return d;
		}
	}
	return 0;
}
#include "../../Bitmap/headers/bitmap.h"

using namespace std;


static size_t hashCode(char c)
{
	return (size_t)c;//字符
}

static size_t hashCode(int k)
{
	return (size_t)k;//整数以及长长整数
}


static size_t hashCode(long long i)
{
	return (size_t)((i >> 32) + (int)i);
}


static size_t hashCode(char s[])
{
	int h = 0;
	for (size_t n = strlen(s), i = 0; i < n; i++)
	{
		h = (h << 5) | (h >> 27);
		h += (int)s[i];
	}
	return (size_t)h;
}

#include "Dictionary.h"
#include "Entry.h"
#include "utility.h"

template<typename K, typename V>//key,value
class HashTable :public Dictionary<K, V>
{
	//符合Dictionary接口的HashTable集合
private:
	Entry<K, V>** ht;//桶数组，存放词条指针
	int M;//桶数组容量
	int N;//词条容量
	Bitmap* lazyRemoval;//懒惰删除标记

#define lazilyRemoved(x) (lazyRemoval->test(x))
#define markAsRemoved(x) (lazyRemoval->set(x))

protected:
	int probe4Hit(const K& k);//沿关键码K对应的值查找链，找到词条匹配的桶
	int probe4Free(const K& k);//沿关键码K对应的值查找链，找到首个可用空桶
	void rehash();//重散列算法，扩充桶数组，保证装填因子在警戒线以下
public:
	HashTable(int c = 5);//创建一个容量不小于c的散列表（为测试暂时选用较小的默认值）
	~HashTable();//释放桶数组及其中的各个(非空)元素所指向的词条
	int size()const//返回当前的词条数目
	{
		return N;
	}
	bool put(K, V);//插入，禁止雷同词条
	V* get(K k);//读取
	bool remove(K k);//删除
};


template<typename K, typename V>
HashTable<K, V>::HashTable(int c)
{
	//创建散列表容量为不小于c的素数N
	M = primeNLT(c, 10000);
	N = 0;
	ht = new Entry<K, V> * [M];//开辟桶数组，初始装填因子N/M=0%
	memset(ht, 0, sizeof(Entry<K, V>*) * M);//初始化各个桶
	lazyRemoval = new Bitmap(M);//懒惰删除标记比特图
}


template<typename K, typename V>
HashTable<K, V>::~HashTable()
{
	//析构之前释放桶数组以及非空词条
	for (int i = 0; i < M; i++)
	{
		//逐一检查各个桶
		if (ht[i])
		{
			release(ht[i]);//释放非空的桶
		}
	}
	release(ht);//释放桶数组
	release(lazyRemoval);//释放懒惰删除标记
}

#include "get.h"
#include "probe4Hit.h"
#include "probe4Free.h"
#include "remove.h"
#include "put.h"
#include "rehash.h"

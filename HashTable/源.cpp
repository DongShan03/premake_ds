#pragma warning(disable:4996)

#include<iostream>
#include<memory>


using namespace std;


static size_t hashCode(char c)
{
	return (size_t)c;//�ַ�
}

static size_t hashCode(int k)
{
	return (size_t)k;//�����Լ���������
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


template <typename K, typename V>
struct Entry
{
	//����ģ����
	K key;

	V value; //�ؼ��롢��ֵ

	Entry(K k = K(), V v = V()) : key(k), value(v)
	{

	}; //Ĭ�Ϲ��캯��
	Entry(Entry<K, V> const& e) : key(e.key), value(e.value)
	{

	}; //���ڿ�¡�Ĺ��캯��

	bool operator< (Entry<K, V> const& e)
	{
		return key < e.key;
	}  //�Ƚ�����С��

	bool operator> (Entry<K, V> const& e)
	{
		return key > e.key;
	}  //�Ƚ���������

	bool operator== (Entry<K, V> const& e)
	{
		return key == e.key;
	} //�е���������

	bool operator!= (Entry<K, V> const& e)
	{
		return key != e.key;

	} //�е�����������
}; //�����ڱȽ������е������Ӵ����󣬲����ϸ����ִ��������Ӧ�Ĺؼ���


template <typename K, typename V>
struct Dictionary
{
	//�ʵ�Dictionaryģ����
	virtual int size() const = 0; //��ǰ��������
	virtual bool put(K, V) = 0; //�����������ֹ��ͬ����ʱ����ʧ�ܣ�
	virtual V* get(K k) = 0; //��ȡ����
	virtual bool remove(K k) = 0; //ɾ������
};


//λͼ��Bitmap��
class Bitmap
{
private:
	char* M;//����ͼ����ŵĿռ�M[]������ΪN*sizeof(char)*8����
	int N;
protected:
	void init(int n)
	{
		N = (n + 7) / 8;
		M = new char[N];
		memset(M, 0, N);
	}
public:
	Bitmap(int n = 8)
	{
		init(n);//��ָ����Ĭ�Ϲ�ģ��������ͼ
	}

	Bitmap(char* file, int n = 8)
	{
		//��ָ����ģ����Ĭ�Ϲ�ģ�����ļ�֮�ж�ȡ����ͼ
		init(n);
		FILE* fp = fopen(file, "r");
		fread(M, sizeof(char), N, fp);
		fclose(fp);
	}

	~Bitmap()
	{
		delete[]M;
		M = NULL;//����ʱ�ͷű���ͼ�ռ�
	}

	void set(int k)
	{
		expand(k);
		M[k >> 3] |= (0x80 >> (k & 0x07));
	}

	void clear(int k)
	{
		expand(k);
		M[k >> 3] &= ~(0x80 >> (k & 0x07));
	}

	bool test(int k)
	{
		expand(k);
		return M[k >> 3] & ((0x80) >> (k & 0x07));
	}

	void dump(char* file)
	{
		//��λͼ���嵼����ָ���ļ����Ա�˺���µ�λͼ���������ʼ��
		FILE* fp = fopen(file, "w");
		fwrite(M, sizeof(char), N, fp);
		fclose(fp);
	}

	char* bits2string(int n)
	{
		//��ǰNλת��Ϊ�ַ���
		expand(n - 1);//��ʱ���ܱ����ʵ����λΪbitmap[n-1]
		char* s = new char[n + 1];
		s[n] = '\0';
		for (int i = 0; i < n; i++)
		{
			s[i] = test(i) ? '1' : '0';
		}
		return s;//�����ַ���
	}

	void expand(int k)//�������ʵ�Bitmap[k]�ѳ��磬��������
	{
		if (k < 8 * N)
		{
			return;//�����ڽ��ڣ���������
		}
		int oldN = N;
		char* oldM = M;
		init(2 * k);//���������ƣ��ӱ�����
		memcpy_s(M, N, oldM, oldN);
		//��Ԫ����ת�����µĵĿռ�
		delete[] oldM;
	}
};


template<typename K, typename V>//key,value
class HashTable :public Dictionary<K, V>
{
	//����Dictionary�ӿڵ�HashTable����
private:
	Entry<K, V>** ht;//Ͱ���飬��Ŵ���ָ��
	int M;//Ͱ��������
	int N;//��������
	Bitmap* lazyRemoval;//����ɾ�����

#define lazilyRemoved(x) (lazyRemoval->test(x))
#define markAsRemoved(x) (lazyRemoval->set(x))

protected:
	int probe4Hit(const K& k);//�عؼ���K��Ӧ��ֵ���������ҵ�����ƥ���Ͱ
	int probe4Free(const K& k);//�عؼ���K��Ӧ��ֵ���������ҵ��׸����ÿ�Ͱ
	void rehash();//��ɢ���㷨������Ͱ���飬��֤װ�������ھ���������
public:
	HashTable(int c = 5);//����һ��������С��c��ɢ�б�Ϊ������ʱѡ�ý�С��Ĭ��ֵ��
	~HashTable();//�ͷ�Ͱ���鼰���еĸ���(�ǿ�)Ԫ����ָ��Ĵ���
	int size()const//���ص�ǰ�Ĵ�����Ŀ
	{
		return N;
	}
	bool put(K, V);//���룬��ֹ��ͬ����
	V* get(K k);//��ȡ
	bool remove(K k);//ɾ��
};



template <typename T> struct Cleaner {
	static void clean(T x) { //�൱�ڵݹ��
#ifdef _DEBUG
		static int n = 0;
		if (7 > strlen(typeid (T).name())) { //��������һ�ź��ԣ�ֻ�����������
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
		} //������а���ָ�룬�ݹ��ͷ�
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



bool isPrime(int x)//������ָһ������һ����Ȼ������1���������⣬���ܱ�������Ȼ����������
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
	//��[c,n)֮��ȡ��С������
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
}


template<typename K, typename V>
HashTable<K, V>::HashTable(int c)
{
	//����ɢ�б�����Ϊ��С��c������N
	M = primeNLT(c, 10000);
	N = 0;
	ht = new Entry<K, V> * [M];//����Ͱ���飬��ʼװ������N/M=0%
	memset(ht, 0, sizeof(Entry<K, V>*) * M);//��ʼ������Ͱ
	lazyRemoval = new Bitmap(M);//����ɾ����Ǳ���ͼ
}


template<typename K, typename V>
HashTable<K, V>::~HashTable()
{
	//����֮ǰ�ͷ�Ͱ�����Լ��ǿմ���
	for (int i = 0; i < M; i++)
	{
		//��һ������Ͱ
		if (ht[i])
		{
			release(ht[i]);//�ͷŷǿյ�Ͱ
		}
	}
	release(ht);//�ͷ�Ͱ����
	release(lazyRemoval);//�ͷ�����ɾ�����
}


template<typename K, typename V>
V* HashTable<K, V>::get(K k)
{
	//ɢ�д��������㷨
	int r = probe4Hit(k);
	return ht[r] ? &(ht[r]->value) : NULL;//��ֹ����keyֵ��ͬ
}


template<typename K, typename V>
int HashTable<K, V>::probe4Hit(const K& k)
{
	int r = hashCode(k) % M;
	while ((ht[r] && (k != ht[r]->key)) || (!ht[r] && lazilyRemoved(r)))
	{
		r = (r + 1) % M;//���Ų�����������̽���������о��г�ͻ��Ͱ���Լ���������ɾ����ǵ�Ͱ
	}
	return r;
}



template<typename K, typename V>
bool HashTable<K, V>::remove(K k)
{
	//ɢ�б����ɾ���㷨
	int r = probe4Hit(k);
	if (!ht[r])
	{
		return false;//��Ӧ���������ڵ�ʱ���޷�ɾ��
	}
	release(ht[r]);
	ht[r] = NULL;
	markAsRemoved(r);
	N--;
	return true;//�����ͷ�Ͱ�еĴ�������������ɾ����ǣ������´�������
}


template<typename K, typename V>
bool HashTable<K, V>::put(K k, V v)
{
	//ɢ�б��������
	if (ht[probe4Hit(k)])
	{
		return false;//��ͬԪ�ز����ظ�����
	}
	int r = probe4Free(k);//Ϊ�����ҵ�һ����Ͱ
	ht[r] = new Entry<K, V>(k, v);
	N++;//���룬ע������ɾ��������踴λ
	if (N * 2 > M)
	{
		rehash();//װ�����Ӹ���50%֮����ɢ��
	}
	return true;
}



template<typename K, typename V>
int HashTable<K, V>::probe4Free(const K& k)
{
	int r = hashCode(k) % M;//����ʼͰ����
	while (ht[r])//�ز�������Ͱ��̽��ֱ���׸���Ͱ(�����Ƿ��������ɾ�����)
	{
		r = (r + 1) % M;//Ϊ��֤��Ͱ�����ҵ���װ�������Լ�ɢ�б�����Ҫ��������
	}
	return r;
}


template<typename K, typename V>
void HashTable<K, V>::rehash()
{
	int old_capacity = M;
	Entry<K, V>** old_ht = ht;
	M = primeNLT(2 * M, 1048576);
	N = 0;
	ht = new Entry<K, V> * [M];
	memset(ht, 0, sizeof(Entry<K, V>*) * M);
	release(lazyRemoval);
	lazyRemoval = new Bitmap(M);
	for (int i = 0; i < old_capacity; i++)
	{
		if (old_ht[i])
		{
			put(old_ht[i]->key, old_ht[i]->value);
		}
	}
	release(old_ht);
}



int main()
{
	HashTable<int, int >obj(100);
	obj.put(12, 12);
	if (obj.get(13))
	{
		cout << "founded��" << endl;
	}
	else
	{
		cout << "not founded��" << endl;
	}

	if (obj.get(12))
	{
		cout << "founded��" << endl;
	}
	else
	{
		cout << "not founded��" << endl;
	}
	obj.remove(12);


	if (obj.get(12))
	{
		cout << "founded��" << endl;
	}
	else
	{
		cout << "not founded��" << endl;
	}

	obj.put(100, 100);
	cout << obj.size() << endl;

	system("pause");
	return 0;
}

#pragma warning(disable:4996)
#include<iostream>
#include<algorithm>
#include<memory>

using namespace std;

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


int main()
{
	int n = 1000;
	Bitmap bt(n);
	for (int i = 0; i < n; i++)
	{
		bt.set(i);
	}
	if (bt.test(20000))
	{
		cout << "founded!" << endl;
	}
	else
	{
		cout << "not founded!" << endl;
	}
	system("pause");
	return 0;
}

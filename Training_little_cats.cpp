/*
POJ - 3735
给定一个初始全为 0的序列，有三种操作
给第 i个数加一，令第 i个数清零，交换第 i和第 j个数
给定一个操作序列，问重复这个操作序列 M次后，初始序列的情况

首先 M高达 1e9，所以肯定要用矩阵优化
然后有几个trick
1. K有 100, 极限情况下会爆 int，所以要开 longlong
2. 构造矩阵的时候，不能简单地用变换矩阵去乘，不然复杂度就是 O(N^4)的
由于都是简单的初等变换，所以手动构造即可
3. 总的复杂度是 O(N^3logM)的，接近 1e7
这在 POJ上是过不了的，所以要加一个很重要的优化
for(int k=0; k<siz; k++) for(int i=0; i<siz; i++) if(n[i][k]) for(int j=0; j<siz; j++) 
	tem.n[i][j] += n[i][k]*v.n[k][j];
调整枚举顺序，当n[i][k]为 0的时候，不进行乘法，
由于这个矩阵很稀疏，所以能优化很多时间
*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <map>
#include <set>
#include <queue>
#include <bitset>
#include <string>
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define SQR(a) ((a)*(a))
#define PCUT puts("----------")

struct Matrix
{
	LL n[105][105];
	int siz;
	Matrix(int _n){siz=_n; CLR(n);}
	void E(){CLR(n); for(int i=0; i<siz; i++) n[i][i]=1;}
	Matrix operator * (const Matrix &v) const
	{
		Matrix tem(siz);
		for(int k=0; k<siz; k++) for(int i=0; i<siz; i++) if(n[i][k]) for(int j=0; j<siz; j++) 
			tem.n[i][j] += n[i][k]*v.n[k][j];
		return tem; 
	}
};
int N,M,K;
Matrix Pow(Matrix,int);
Matrix mat(0);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d%d", &N, &M, &K))
	{
		if(N==0 && M==0 && K==0) break;
		char opt; int x,y;
		mat.siz=N+1;
		mat.E();
		for(int k=0; k<K; k++)
		{
			scanf(" %c%d", &opt, &x);
			if(opt=='g')
			{
				for(int i=0; i<=N; i++) mat.n[x-1][i] += mat.n[N][i];
			}
			if(opt=='e')
			{
				for(int i=0; i<=N; i++) mat.n[x-1][i] = 0;
			}
			if(opt=='s') 
			{
				scanf("%d", &y);
				for(int i=0; i<=N; i++) swap(mat.n[x-1][i], mat.n[y-1][i]);
			}
		}
		mat = Pow(mat,M);
		for(int i=0; i<N; i++) printf("%lld ", mat.n[i][N]);
		puts("");
	}
	return 0;
}

Matrix Pow(Matrix mat, int n)
{
	Matrix res(mat.siz);
	res.E();
	while(n)
	{
		if(n&1) res = mat*res;
		mat = mat*mat;
		n>>=1;
	}
	return res;
}

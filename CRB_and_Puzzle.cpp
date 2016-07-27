/*
HDU - 5411
有 N种拼图，其中每种拼图后面只能接给定的几种拼图
问接成不超过 M长度的拼图的方案数是多少

普通dp的话被卡时了，并不能过。所以利用矩阵加速。
构造矩阵
| M 0 | | dp_i    |
| 1 1 | | S_{i-1} |
其中 dp_i表示递推到第 i位的解向量，
S_i表示前 i个“解向量之和”的和
而 M就是转移矩阵
然后矩阵快速幂之，即可解决

还有第二种方式，通过修改快速幂，来实现 log求得
M^0 + M^1 + M^2 + ...+M^n 等比数列的和
具体方式如下：
Matrix PowPlus(Matrix mat, LL n)
{
	Matrix res, t0, t1;
	t0=t1=mat;
	while(n)
	{
		if(n&1) res=res*t0 + t1;
		t1 = t1*t0 + t1;
		t0 = t0*t0;
		n>>=1;
	}
	return res;
}
其中 res初始为 0，t0和t1初始等于 mat。
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
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) ((a)*(a))

const int MOD=2015;
struct Matrix
{
	int n[60][60], siz;
	Matrix(int _n){ siz=_n; CLR(n);}
	void E(){CLR(n); for(int i=0; i<siz; i++) n[i][i]=1;}
	Matrix operator * (const Matrix &v) const
	{
		Matrix tem(siz);
		for(int i=0; i<siz; i++) for(int j=0; j<siz; j++) for(int k=0; k<siz; k++)
			tem.n[i][j] = (tem.n[i][j] + n[i][k]*v.n[k][j])%MOD;
		return tem;
	}
	void pri()
	{
		for(int i=0; i<siz; i++)
		{
			for(int j=0; j<siz; j++) printf("%d ", n[i][j]);
			puts("");
		}
	}
};
int N,M;
int Map[60][60];

Matrix Pow(Matrix, LL);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		scanf("%d%d", &N, &M);
		Matrix mat(N+2);
		for(int i=1; i<=N; i++)
		{
			int Msiz;
			scanf("%d", &Msiz);
			mat.n[i][0]=1;
			for(int j=1; j<=Msiz; j++)
			{
				int x;
				scanf("%d", &x);
				mat.n[x][i]=1;
			}
		}
		for(int i=0; i<=N+1; i++) mat.n[N+1][i]=1;
		mat = Pow(mat,M+1);
		printf("%d\n", mat.n[N+1][0]);
	}
	return 0;
}

Matrix Pow(Matrix mat, LL n)
{
	Matrix res(mat.siz);
	res.E();
	while(n)
	{
		if(n&1) res=mat*res;
		mat=mat*mat;
		n>>=1;
	}
	return res;
}


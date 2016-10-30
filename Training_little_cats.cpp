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
#include <complex>
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define SQR(a) ((a)*(a))
#define PCUT puts("\n----------")

struct Matrix
{
	LL n[110][110], siz;
	Matrix(int _n):siz(_n){CLR(n);}
	void E(){CLR(n); for(int i=0; i<siz; i++) n[i][i]=1;}
	Matrix operator * (const Matrix &rhs) const
	{
		Matrix tem(siz);
		for(int i=0; i<siz; i++) for(int k=0; k<siz; k++) if(n[i][k]) for(int j=0; j<siz; j++)
			tem.n[i][j] += n[i][k]*rhs.n[k][j];
		return tem;
	}
};

int N,M,K;

Matrix Pow(Matrix, int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d%d", &N, &M, &K))
	{
		if(N==0 && M==0 && K==0) break;
		Matrix mat(N+1);
		mat.E();
		for(int k=0; k<K; k++)
		{
			char opt[10]; int a,b;
			scanf("%s", opt);
			if(opt[0]=='g')
			{
				scanf("%d", &a); a--;
				for(int i=0; i<=N; i++) mat.n[a][i] += mat.n[N][i];
			}
			if(opt[0]=='e')
			{
				scanf("%d", &a); a--;
				for(int i=0; i<=N; i++) mat.n[a][i] = 0;
			}
			if(opt[0]=='s')
			{
				scanf("%d%d", &a, &b); a--; b--;
				for(int i=0; i<=N; i++) swap(mat.n[a][i], mat.n[b][i]);
			}
		}
		mat = Pow(mat, M);
		for(int i=0; i<N; i++) printf("%lld ", mat.n[i][N]);
		puts("");
	}
	return 0;
}

Matrix Pow(Matrix mat, int n)
{
	Matrix res(mat.siz);
	res.E();
	for(; n>0; n>>=1)
	{
		if(n&1) res = mat*res;
		mat = mat*mat;
	}
	return res;
}

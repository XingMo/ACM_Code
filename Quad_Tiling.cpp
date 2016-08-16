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

int MOD;
struct Matrix
{
	int n[16][16], siz;
	Matrix(){CLR(n); siz=16;}
	void E(){CLR(n); for(int i=0; i<siz; i++) n[i][i]=1;}
	Matrix operator * (const Matrix &v) const
	{
		Matrix tem;
		for(int i=0; i<siz; i++) for(int j=0; j<siz; j++) for(int k=0; k<siz; k++)
			tem.n[i][j] = (tem.n[i][j] + (LL)n[i][k]*v.n[k][j])%MOD;
		return tem;
	}
};

int N, M;
Matrix Pow(Matrix,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	Matrix x;
	for(int m=0; m<1<<4; m++)
	{
		int nxt=0;
		for(int i=0; i<4; i++) if(!((m>>i)&1))
		{
			nxt |= 1<<i;
		}
		x.n[nxt][m] = 1;
		if( !(nxt&3) ) x.n[nxt|3][m] = 1;
		if( !(nxt&6) ) x.n[nxt|6][m] = 1;
		if( !(nxt&12) ) x.n[nxt|12][m] = 1;
		if( !nxt ) x.n[15][m] = 1;
	}
	
	while(~scanf("%d%d", &N, &M))
	{
		if(N==0 && M==0) break;
		MOD = M;
		Matrix ans = Pow(x,N);
		printf("%d\n", ans.n[15][15]);
	}
	return 0;
}

Matrix Pow(Matrix mat, int n)
{
	Matrix res;
	res.E();
	while(n)
	{
		if(n&1) res = mat*res;
		mat = mat*mat;
		n>>=1;
	}
	return res;
}

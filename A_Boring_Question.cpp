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
#define PCUT puts("\n----------")

const int MOD=1000000007;
struct Matrix
{
	int n[4][4],siz;
	Matrix(int _n){siz=_n; CLR(n);}
	void E(){CLR(n); for(int i=0; i<siz; i++) n[i][i]=1;}
	Matrix operator * (const Matrix &v) const 
	{
		Matrix tem(siz);
		for(int i=0; i<siz; i++) for(int j=0; j<siz; j++) for(int k=0; k<siz; k++)
			tem.n[i][j] = (tem.n[i][j] + (LL)n[i][k] * v.n[k][j]) %MOD;
		return tem;
	}
	void pri()
	{
		for(int i=0; i<siz; i++,puts("")) for(int j=0; j<siz; j++) printf("%d ", n[i][j]);
	}
};

Matrix Pow(Matrix,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	Matrix mat(2);
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		int N,M;
		scanf("%d%d", &N, &M);
		if(N==0) {printf("1\n"); continue;}
		mat.n[0][0] = M; mat.n[0][1] = 1;
		mat.n[1][0] = 0; mat.n[1][1] = 1;
		mat = Pow(mat,N);
		printf("%d\n", (int)(((LL)mat.n[0][0] + mat.n[0][1])%MOD + MOD)%MOD);
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

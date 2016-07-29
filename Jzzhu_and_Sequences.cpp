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

const int MOD=1e9+7;
struct Matrix
{
	int n[4][4], siz;
	Matrix(){CLR(n); siz=2;}
	void E(){CLR(n); for(int i=0; i<siz; i++) n[i][i]=1;}
	Matrix operator * (const Matrix &v) const
	{
		Matrix tem;
		for(int i=0; i<siz; i++) for(int j=0; j<siz; j++) for(int k=0; k<siz; k++)
			tem.n[i][j] = (tem.n[i][j] + (LL)n[i][k]*v.n[k][j]%MOD)%MOD;
		return tem;
	}
};

int X,Y,N;
Matrix Pow(Matrix,LL);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	scanf("%d%d%d", &X, &Y, &N);
	if(N==1) printf("%d\n", (X%MOD+MOD)%MOD);
	else if(N==2) printf("%d\n", (Y%MOD+MOD)%MOD);
	else
	{
		N-=2;
		Matrix ans;
		ans.n[0][0]=1; ans.n[0][1]=-1;
		ans.n[1][0]=1; ans.n[1][1]=0;
		ans = Pow(ans,N);
		LL res = (LL)Y*ans.n[0][0]%MOD + (LL)X*ans.n[0][1]%MOD;
		res = (res%MOD+MOD)%MOD;
		cout << res << endl;
	}
	return 0;
}

Matrix Pow(Matrix x, LL n)
{
	Matrix res;
	res.E();
	while(n)
	{
		if(n&1) res=x*res;
		x=x*x;
		n>>=1;
	}
	return res;
}


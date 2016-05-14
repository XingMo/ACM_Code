#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
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
#define Sqr(a) (a*a)

const int maxm=500+10, MOD=1e9+7;
struct Matrix
{
	LL n[3][3];
	Matrix(){CLR(n);}
	Matrix operator * (const Matrix &v) const
	{
		Matrix temp;
		for(int i=0; i<3; i++) for(int j=0; j<3; j++) for(int k=0; k<3; k++)
			temp.n[i][j]=(temp.n[i][j]+n[i][k]*v.n[k][j])%MOD;
		return temp;
	}
	void E(){CLR(n);for(int i=0; i<3; i++) n[i][i]=1;}
	void pri(){puts("Matrix:");for(int i=0; i<3; i++) {for(int j=0; j<3; j++)printf("%lld", n[i][j]);puts("");}}
};
LL N;
int M;
LL inpt[maxm];

Matrix MPow(Matrix,LL);

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
		scanf("%lld%d", &N, &M);
		for(int i=0; i<M; i++) scanf("%lld", &inpt[i]);
		sort(inpt, inpt+M);
		M=unique(inpt, inpt+M)-inpt;
		while(M && inpt[M-1]>N) M--;
		if(!M)
		{
			puts("1");
			continue;
		}
		if(inpt[0]==0 || inpt[M-1]==N)
		{
			puts("0");
			continue;
		}
		Matrix res,zero,norm;
		res.E();
		zero.n[1][0] = zero.n[2][1] = 1;
		norm=zero;
		for(int i=0; i<3; i++) norm.n[0][i]=1;
		
		
		for(int i=0; i<M; i++)
		{
			int tims=inpt[i]-1;
			if(i) tims-=inpt[i-1];
			res=MPow(norm, tims)*res;
			res=zero*res;
		}
		res=MPow(norm, N-inpt[M-1])*res;
		printf("%lld\n", res.n[0][0]);
	}
	return 0;
}

Matrix MPow(Matrix mat, LL tims)
{
	Matrix res;
	res.E();
	while(tims)
	{
		if(tims&1) res=res*mat;
		mat=mat*mat;
		tims>>=1;
	}
	return res;
}


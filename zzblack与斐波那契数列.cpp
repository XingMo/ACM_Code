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

const LL MOD1=2238065148, MOD2=16941960;
struct Matrix
{
	LL n[2][2];
	LL mod;
	Matrix(LL a):mod(a){CLR(n);}
	void E(){CLR(n);for(int i=0; i<2; i++) n[i][i]=1;}
	Matrix operator * (const Matrix &v) const
	{
		Matrix res(mod);
		for(int i=0; i<2; i++) for(int j=0; j<2; j++) for(int k=0; k<2; k++)
			res.n[i][j]=(res.n[i][j] + (n[i][k]*v.n[k][j])%mod ) %mod;
		return res;
	}
};

LL N;
LL getT(LL);
LL getF(LL);

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
		scanf("%lld", &N);
		N=getT(N);
		N=getF(N);
		printf("%lld\n", N);
	}
	return 0;
}


LL getT(LL N)
{
	if(N==0) return 1;
	if(N==1) return 3;
	if(N==2) return 7;
	N-=2;
	
	Matrix res(MOD2),ans(MOD2);
	ans.E();
	res.n[0][0]=3; res.n[0][1]=-1; res.n[1][0]=1;
	while(N)
	{
		if(N&1) ans=res*ans;
		res=res*res;
		N>>=1;
	}

	LL tn = (7*ans.n[0][0] + 3*ans.n[0][1]) %MOD2;
	tn+=MOD2;
	return tn%MOD2;
}

LL getF(LL N)
{
	if(N==0) return 1;
	if(N==1) return 1;
	N-=2;
	
	Matrix res(MOD1),ans(MOD1);
	ans.E();
	res.n[0][0] = res.n[0][1] = res.n[1][0] = 1;
	while(N)
	{
		if(N&1) ans=res*ans;
		res=res*res;
		N>>=1;
	}
	
	return (ans.n[0][0] + ans.n[0][1]) %MOD1;
}

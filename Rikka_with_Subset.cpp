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

const int maxn=1e5+10, maxl=1<<19, MOD=998244353, PR=3;
int N, A[maxn];
LL pow2[2][maxn], fact[2][maxn];
LL PA[maxl], PB[maxl], res[maxn];

LL Pow(LL,LL,LL);
void FNT(int,LL*,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	pow2[0][0]= pow2[1][0] = fact[0][0] = fact[1][0] = 1;
	for(int i=1; i<maxn; i++) pow2[0][i] = (pow2[0][i-1]<<1)%MOD, pow2[1][i] = Pow(pow2[0][i], MOD-2, MOD);
	for(int i=1; i<maxn; i++) fact[0][i] = (fact[0][i-1]*i)%MOD,  fact[1][i] = Pow(fact[0][i], MOD-2, MOD);
	
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		scanf("%d", &N);
		for(int i=1; i<=N; i++) scanf("%d", &A[i]);
		sort(A+1, A+1+N, greater<int>());
		
		int len=1; while(len <= N<<1) len<<=1;
		CLR(PA); CLR(PB);
		for(int i=0; i<=N; i++)
		{
			PA[i] = pow2[0][N-i]*fact[1][i]%MOD;
			if(i) PB[i] = fact[0][i-1]*A[i]%MOD;
		}
		reverse(PB+1, PB+1+N);
		
		FNT(len,PA,1); FNT(len,PB,1);
		for(int i=0; i<len; i++) PA[i]=PA[i]*PB[i]%MOD;
		FNT(len,PA,-1);
		
		for(int i=1; i<=N; i++) res[i] = pow2[1][i]*fact[1][i-1]%MOD * PA[N-i+1]%MOD;
		for(int i=1; i<=N; i++) res[i] = (res[i]+res[i-1])%MOD;
		for(int i=1; i<=N; i++) printf("%lld ", (res[i]+MOD)%MOD); puts("");
	}
	return 0;
}

void FNT(int n, LL A[], int dir)
{
	for(int i=0,j=0; i<n; i++)
	{
		if(i<j) swap(A[i], A[j]);
		for(int k=n>>1; (j^=k)<k; k>>=1);
	}
	for(int len=2; len<=n; len<<=1)
	{
		int m = len>>1;
		LL wn = Pow(PR, (MOD-1)/len, MOD);
		if(dir==-1) wn = Pow(wn, MOD-2, MOD);
		for(int i=0; i<n; i+=len)
		{
			LL w=1;
			for(int j=0; j<m; j++)
			{
				LL z = w*A[i+m+j]%MOD;
				A[i+m+j] = (A[i+j]-z)%MOD;
				A[i+j] = (A[i+j]+z)%MOD;
				w = w*wn%MOD;
			}
		}
	}
	if(dir==-1)
	{
		LL inv=Pow(n, MOD-2, MOD);	
		for(int i=0; i<n; i++) A[i] = A[i]*inv%MOD;
	}
}

LL Pow(LL x, LL n, LL p)
{
	LL res=1;
	while(n)
	{
		if(n&1) res=res*x%p;
		x=x*x%p;
		n>>=1;
	}
	return res;
}

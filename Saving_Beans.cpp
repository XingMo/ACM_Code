/*
HDU - 3037
有不超过 m个球，放入 n个盒子里，求方案数

m个球放入 n个盒子，允许盒子为空
用隔板法可得方案数为 C(m+n-1, m)
所以即求 C(n-1, 0) + C(n, 1) + C(n+1, 2) + ... + C(m+n-1, m)
利用组合数公式 C(n, k) = C(n-1, k-1) + C(n-1, k)
原式 = C(n, 0) + C(n, 1) + C(n+1, 2) + ... + C(m+n-1, m)
     = C(n+1, 1) + C(n+1, 2) + ... + C(m+n-1, m)
     = C(m+n, m)
     
由于 m和 n都很大，不可能处理那么多阶乘，
所以利用 lucas定理，这样一来只需要处理到模数 p的阶乘即可
C(n,k)%p = C(n%p,k%p)*C(n/p,k/p)
问题就解决了
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

const int maxp=1e5+10;
LL N,M,P;
LL fact[maxp];

LL Pow(LL,LL,LL);
LL Lucas(LL,LL,LL);

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
		scanf("%lld%lld%lld", &N, &M, &P);
		fact[0]=1;
		for(int i=1; i<=P; i++) fact[i]=(fact[i-1]*i)%P;
		cout << Lucas(N+M,M,P) << '\n';
	}
	return 0;
}

LL Pow(LL x, LL n, LL p)
{
	LL res=1;
	while(n)
	{
		if(n&1) res=(x*res)%p;
		x=(x*x)%p;
		n>>=1;
	}
	return res;
}

LL Lucas(LL n, LL k, LL p)
{
	LL res=1;
	while(n&&k)
	{
		LL n0=n%p, k0=k%p;
		if(n0<k0) return 0;
		res = res*fact[n0]*Pow(fact[k0]*fact[n0-k0]%p, p-2, p)%p;
		n/=p;
		k/=p;
	}
	return res;
}

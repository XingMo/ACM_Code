/*
Codeforces - 451E
有 n种花，每种花有 f_i支，问从中选出 s支的方案数
其中 n<=20，S<=1e14

母函数解法：
构造母函数，(1+x+x^2+...+x^(f_1)) * ... * (1+x+x^2+...+x^(f_n))
而答案即为 x^s项的系数
利用等比数列和公式，将母函数化为 (1-x^(f_1+1)) *... * (1-x^(f_n+1)) / (1-x)^n
但是这里有一个除，没法求系数，所以要把除的那部分也化成多项式
将 1/(x-1)泰勒展开：1/(x-1) = 1+x+x^2+...
而 (1+x+x^2+...)^n 也可以看作一个母函数
其意义为从 n种花中取，每种花数量无限
利用隔板法，很容易能得到从中取 t支的方案数，
即 x^t的系数，为 C(n+t-1, n-1)
这样后面除掉的那一项就搞定了，而前面不超过 20项
因此可以暴力展开，求出每一项系数
然后再利用 lucas定理求组合数，即可得到答案
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

const int MOD=1e9+7;
LL N,S;
LL inpt[30];
LL Lucas(LL,LL,LL);
LL Pow(LL,LL,LL);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	scanf("%lld%lld", &N, &S);
	for(int i=0; i<N; i++) scanf("%lld", &inpt[i]);
	LL ans=0;
	for(int m=0; m<1<<N; m++)
	{
		LL cef=1, tp=S;
		for(int i=0; i<N; i++)
		{
			if(m&(1<<i))
			{
				tp-=inpt[i]+1;
				cef*=-1;
			}
		}
//		if(tp>S) continue;
//		tp=S-tp;
		if(tp<0) continue;
//		printf("%lld %lld %lld\n", N+tp-1, N-1, Lucas(N+tp-1, N-1, MOD));
		cef = cef*Lucas(N+tp-1, N-1, MOD)%MOD;
		ans = (ans+cef)%MOD;
	}
	cout << (ans+MOD)%MOD << '\n';
	return 0;
}

LL Lucas(LL n, LL k, LL p)
{
	if(k>n-k) k=n-k;
	LL res=1;
	while(n&&k)
	{
		LL n0=n%p, k0=k%p;
		LL a=1,b=1;
		for(LL i=n0; i>n0-k0; i--) a=a*i%p;
		for(LL i=1; i<=k0; i++) b=b*i%p;
		res = res*a*Pow(b, p-2, p)%p;
		n/=p; k/=p;
	}
	return res;
}

LL Pow(LL x, LL n, LL p)
{
	LL res=1;
	while(n)
	{
		if(n&1) res=x*res%p;
		x=x*x%p;
		n>>=1;
	}
	return res;
}

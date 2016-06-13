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

const LL MOD=1000000007;
LL exgcd(LL a, LL b, LL &x, LL &y)
{
	if(!b) {x=1; y=0; return a;}
	else
	{
		LL d=exgcd(b, a%b, y, x);
		y -= x*(a/b);
		return d;
	}
}

LL mod_inv(LL a, LL mod)
{
	LL d,x,y;
	d = exgcd(a, mod, x, y);
	return d==1? (x+mod)%mod : -1;
}

LL sPow(LL num, LL tim, LL mod)
{
	LL res=1;
	while(tim)
	{
		if(tim&1) res=(LL)res*num%mod;
		num=(LL)num*num%MOD;
		tim>>=1;
	}
	return res;
}

LL K;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	LL tinv=mod_inv(2016, MOD);
	while(~scanf("%lld", &K))
	{
		LL ans = (sPow(2,K,MOD)-sPow(2,K,2016))%MOD*tinv%MOD;
		ans = (ans+MOD)%MOD;
		printf("%lld\n", ans);
	}
	return 0;
}


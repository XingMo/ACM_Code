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

LL exgcd(LL a, LL b, LL &x, LL &y)
{
	if (!b)
	{
		x = 1, y = 0;
		return a;
	}
	LL t, res;
	res = exgcd(b, a%b, x, y);
	t = x, x = y, y = t - a / b*y;
	return res;
}

LL Mul(LL x, LL n, LL p)
{
	LL res=0;
	while(n)
	{
		if(n&1) res = (res+x)%p;
		x = x*2%p;
		n>>=1;
	}
	return res;
}

LL CRT(LL a[], LL p[], int n)
{
	LL M=1, res=0;
	for(int i=0; i<n; i++) M=M*p[i];
	for(int i=0; i<n; i++)
	{
		LL x,y;
		LL MI=M/p[i];
		exgcd( MI, p[i], x, y);
		if(x<0) x+=p[i];
		res = (res + Mul( Mul(a[i], MI, M), x, M)) %M;
	}
	if(res <= 0) res += M;
	return res;
}

int N;
LL X,Y;
LL A[20], P[20];

LL solve(LL);

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
		scanf("%d%lld%lld", &N, &X, &Y);
		for(int i=0; i<N; i++) scanf("%lld%lld", &P[i], &A[i]);
		printf("Case #%d: %lld\n", ck, solve(Y)-solve(X-1));
	}
	return 0;
}

LL solve(LL R)
{
	LL a[25], p[25];
	a[0]=0, p[0]=7;
	LL ans=0;
	for(int m=0; m<1<<N; m++)
	{
		int cnt=0;
		LL M = 7, sig;
		for(int i=0; i<N; i++) if((m>>i)&1)
		{
			cnt++;
			a[cnt] = A[i], p[cnt] = P[i];
			M *= P[i];
		}
		LL res = CRT(a,p,cnt+1);
		if(!(cnt&1)) sig=1;
		else sig=-1;
//		printf("res=%lld M=%lld\n", res, M);
		if(R<res) continue;
		ans += sig*(R-res)/M+sig;
	}
	return ans;
}



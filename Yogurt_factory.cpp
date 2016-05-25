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

const int maxn=1e4+10, INF=0x3f3f3f3f;
int N,S;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &S))
	{
		LL ans=0, tmin=INF;
		for(int i=1; i<=N; i++)
		{
			LL C,Y;
			scanf("%lld%lld", &C, &Y);
			tmin = min(C, tmin+S);
			ans+=tmin*Y;
		}
		printf("%lld\n", ans);
	}
	return 0;
}


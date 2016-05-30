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

const int maxn=1e5+10;
int N,M;
DBL dp[maxn];
int route[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		if(N==0&&M==0) break;
		CLR(route); CLR(dp);
		for(int i=0; i<M; i++)
		{
			int l,r;
			scanf("%d%d", &l, &r);
			route[l]=r;
		}
		for(int i=N-1; i>=0; i--)
		{
			if(route[i]) dp[i] = dp[route[i]];
			else
			{
				dp[i]=1.0;
				for(int j=1; j<=6; j++)
				{
					dp[i] += dp[i+j]/6.0;
				}
			}
		}
		printf("%.4f\n", dp[0]);
	}
	return 0;
}


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

const int maxn=2e3+10, INF=0x3f3f3f3f;
int N,M;
char inpt[maxn];
int cost[26];
int dp[maxn][maxn];

int DP(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		scanf(" %s", inpt+1);
		for(int i=1; i<=N; i++)
		{
			char c;
			int c0,c1;
			scanf(" %c%d%d", &c, &c0, &c1);
			cost[c-'a'] = min(c0, c1);
		}
		MST(dp,-1);
		printf("%d\n", DP(1,M));
	}
	return 0;
}

int DP(int l, int r)
{
	if(l>=r) return 0;
	if(~dp[l][r]) return dp[l][r];
	if( inpt[l] == inpt[r] ) return dp[l][r]=DP(l+1, r-1);
	
	dp[l][r]=INF;
	dp[l][r] = min(dp[l][r], DP(l+1,r) + cost[ inpt[l]-'a' ]);
	dp[l][r] = min(dp[l][r], DP(l,r-1) + cost[ inpt[r]-'a' ]);
	return dp[l][r];
}

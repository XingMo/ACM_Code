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

const DBL eps=1e-7;
int N,M,fmask;
int Map[20][20];
bool EJ[20][1<<15];
DBL dp[20][1<<15];

DBL DP(int,int);

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
		CLR(Map);
		MST(dp,0xc0); CLR(EJ);
		scanf("%d%d", &N, &M);
		fmask = (1<<N)-1;
		for(int i=0,u,v,w; i<M; i++)
		{
			scanf("%d%d%d", &u, &v, &w);
			Map[u][v] = Map[v][u] = w;
		}
		printf("Case %d: %.7f\n", ck, DP(0,1));
	}
	return 0;
}

DBL DP(int u, int mask)
{
	if(mask == fmask) 
	{
		EJ[u][mask] = 1;
		return dp[u][mask] = 0;
	}
	if(dp[u][mask] > eps) return dp[u][mask];
	dp[u][mask] = 0;
	int cnt=0;
	for(int v=0; v<N; v++) if( Map[u][v] && !((mask>>v)&1))
	{
		DP(v, mask|(1<<v));
		if(EJ[v][mask|(1<<v)])
		{
			dp[u][mask] += Map[u][v] + dp[v][mask|(1<<v)];
			cnt++;
			EJ[u][mask] = 1;
		}
	}
	if(cnt) dp[u][mask] = (dp[u][mask] + 5)/cnt;
	return dp[u][mask];
}

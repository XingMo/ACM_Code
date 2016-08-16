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
#define PCUT puts("\n----------")

const int maxn=2e5+10;
struct Graph
{
	int ndn, edn, last[maxn];
	int u[2*maxn], v[2*maxn], nxt[2*maxn];
	void init(int _n){ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u, int _v)
	{
		u[edn]=_u; v[edn]=_v;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};

int N;
Graph G;
int dp[maxn], all;
int dfs1(int,int);
int dfs2(int,int,int,int);
int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		G.init(N);
		for(int i=1,u,v; i<N; i++)
		{
			scanf("%d%d", &u, &v);
			G.adde(u,v); G.adde(v,u);
		}
		all = dfs1(1,0);
		dfs2(1,0,0,0);
		int ans = N-1;
		for(int i=1; i<=N; i++) ans = min(ans, dp[i]);
		printf("%d\n", ans);
		for(int i=1; i<=N; i++) if(dp[i]==ans)
			printf("%d ", i);
		puts("");
	}
	return 0;
}

int dfs1(int u,int f)
{
	dp[u]=0;
	for(int e=G.last[u],v; ~e; e=G.nxt[e]) if((v=G.v[e])!=f)
	{
		dp[u] += (e&1) + dfs1(v,u);
	}
	return dp[u];
}

int dfs2(int u,int f,int e0, int e1)
{
	dp[u] = (dp[u] + all-dp[u]-e1+e0);
	for(int e=G.last[u],v; ~e; e=G.nxt[e]) if((v=G.v[e])!=f)
	{
		dfs2(v,u,e0+((e&1)^1),e1+(e&1));
	}
}

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

const int maxn=1e3+10, maxm=1e4+10;
struct Graph
{
	int ndn,edn,last[maxn];
	int u[maxm],v[maxm],nxt[maxm];
	void init(int n){ndn=n; edn=0; MST(last,-1);}
	void adde(int tu, int tv)
	{
		u[edn]=tu; v[edn].tv;
		nxt[edn]=last[tu];
		last[tu]=edn++;
	}
};

struct Tarjan
{
	Graph &G;
	int dfst, dfsn[maxn], low[maxn];
	int scc_cnt, scc[maxn];
	int skt, stak[maxn];
	bool ins[maxn];
	Tarjan(Graph &a):G(a){};
	int SCC();
	int dfs(int);
};

int N,M;
Graph G;
bool Map[maxn][maxn];
bool vis[maxn];

int dfs(int);

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
		scanf("%d%d", &N, &M);
		G.init(); CLR(Map);
		for(int i=0; i<M; i++)
		{
			int u,v;
			scanf("%d%d", &u, &v);
			G.adde(u,v);
			Map[u][v]=1;
		}
		for(int i=1; i<=N; i++) if(!vis[i]) dfs(i);
		G.init();
		for(int i=1; i<=N; i++)
		{
			for(int j=1; j<=N; j++) if
		}
	}
	return 0;
}

int dfs(int u)
{
	vis[u]=1;
	for(int v=1; v<=N; v++)
	{
		if(u==v || !Map[u][v]) continue;
		if(!vis[v]) dfs(v);
		for(int i=1; i<=N; i++) Map[u][i]|=Map[v][i];
	}
}

int Tarjan::SCC()
{
	dfst=0; CLR(dfsn); CLR(low);
	scc_cnt=0; CLR(scc);
	skt=0; CLR(ins);
	
	for(int i=1; i<=G.ndn; i++) if(!dfsn[i]) dfs(i);
	
	// graph re-construct
	int tot=G.edn;
	G.init(scc_cnt);
	for(int e=0; e<tot; e++)
	{
		int u=G.u[e], v=G.v[e];
		if(scc[u] == scc[v]) continue;
		G.adde(scc[u],scc[v]);
	}
	return scc_cnt;
}

int Tarjan::dfs(int u)
{
	dfsn[u] = low[u] = ++dfst;
	stak[++skt] = u;
	ins[u] = 1;
	
	for(int e=G.last[u]; ~e; e=G.nxt[e])
	{
		int v = G.v[e];
		if(!dfsn[v])
		{
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
		else if(ins[v]) low[u] = min(low[u], low[v]);
	}
	
	if(low[u] == dfsn[u])
	{
		scc_cnt++;
		while(skt)
		{
			ins[ stak[skt] ] = 0;
			scc[ stak[skt] ] = scc_cnt;
			skt--;
			if(stak[skt+1] == u) break;
		}
	}
	
	return 0;
}


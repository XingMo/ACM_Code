/*
SCU - 4529
求dag上可重复的最小路径覆盖

可重复的最小路径覆盖和不可重复的基本一样
只要求一个传递闭包，把一个点出发的可达点都连上边
因为假设覆盖两个点 u，v中途要经过其他点
求过传递闭包之后，就可以直接用 u，v之间直接相连的边来覆盖
就转化成了不可重复的最小路径覆盖
用floyd肯定会 T，但是由于dag图的特性，可以使用dfs构图
*/
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
	int V,E;
	int ndn,edn, *last;
	int *u, *v , *nxt;
	Graph(int tv,int te):V(tv),E(te)
	{
		last=new int[V];
		u=new int[E]; v=new int[E]; nxt=new int[E];
	}
	~Graph()
	{
		delete []last;
		delete []u; delete []v; delete []nxt;
	}
	void init(int n){ndn=n; edn=0; memset(last,-1,sizeof(int)*V);}
	void adde(int tu, int tv)
	{
		u[edn]=tu; v[edn]=tv;
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

struct Hungarian
{
	Graph &G;
	int res, match[2*maxn];
	bool ins[2*maxn];
	Hungarian(Graph &g):G(g){};
	int solve();
	int dfs(int);
};

int N,M;
Graph G(maxn,maxm), div_g(2*maxn,maxn*maxn);
vector<int> reach[maxn];

Tarjan tarjan(G);
Hungarian hung(div_g);

int construct(int);

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
		
		G.init(N);
		for(int i=0; i<M; i++)
		{
			int u,v;
			scanf("%d%d", &u, &v);
			G.adde(u,v);
		}
		tarjan.SCC();
		
		div_g.init(2*G.ndn);
		for(int i=1; i<=G.ndn; i++) reach[i].clear();
		for(int i=1; i<=G.ndn; i++) if(!reach[i].size()) construct(i);
		
		printf("Case %d: %d \n", ck, G.ndn-hung.solve());
	}
	return 0;
}

int construct(int u)
{
	for(int e=G.last[u]; ~e; e=G.nxt[e])
	{
		int v=G.v[e];
		if(!reach[v].size()) construct(v);
		for(int i=0; i<(int)reach[v].size(); i++) reach[u].push_back(reach[v][i]);
	}
	
	sort(reach[u].begin(),reach[u].end());
	vector<int>::iterator iter = unique(reach[u].begin(), reach[u].end());
	reach[u].erase(iter, reach[u].end());
	
	for(int i=0; i<(int)reach[u].size(); i++) 
	{
		div_g.adde(u, reach[u][i]+G.ndn);
	}
	reach[u].push_back(u);
	return 0;
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

int Hungarian::solve()
{
	res=0;
	CLR(match);
	for(int i=1; i<=G.ndn; i++)
	{
		if(!match[i])
		{
			CLR(ins);
			if(dfs(i)) res++;
		}
	}
	return res;
}

int Hungarian::dfs(int u)
{
	for(int e=G.last[u]; ~e; e=G.nxt[e])
	{
		int v=G.v[e];
		if(ins[v]) continue;
		ins[v]=1;
		if(!match[v] || dfs(match[v]))
		{
			match[v]=u;
			match[u]=v;
			return 1;
		}
	}
	return 0;
}


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

const int maxn=4e4+10, maxq=200+10;
struct Graph
{
	int ndn, edn, last[maxn];
	int u[maxn*2], v[maxn*2], w[maxn*2], nxt[maxn*2];
	void init(int tn){ ndn=tn; edn=0; MST(last,-1);}
	void adde(int tu, int tv, int tw)
	{
		u[edn]=tu; v[edn]=tv; w[edn]=tw;
		nxt[edn]=last[tu];
		last[tu]=edn++;
	}
};

struct Tarjan
{
	Graph *G;
	int dfsn[maxn], unin[maxn];
	int dist[maxn], res[maxn];
	
	void LCA(Graph*);
	int dfs(int);
	int find(int x)
	{
		if(unin[x]==x) return x;
		return unin[x]=find(unin[x]);
	}
	int joint(int x,int y)
	{
		unin[ find(y) ] = find(x);
	}
};

int N,Q;
Graph G;
Tarjan tar;
vector<int> id[maxn], que[maxn];

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
		scanf("%d%d", &N, &Q);
		G.init(N);
		for(int i=1; i<N; i++)
		{
			int u,v,w;
			scanf("%d%d%d", &u, &v, &w);
			G.adde(u,v,w); G.adde(v,u,w);
		}
		
		for(int i=1; i<=N; i++) {que[i].clear(); id[i].clear();}
		for(int i=0; i<Q; i++)
		{
			int u,v;
			scanf("%d%d", &u, &v);
			que[u].push_back(v);
			que[v].push_back(u);
			id[u].push_back(i);
			id[v].push_back(i);
		}
		tar.LCA(&G);
		
		for(int i=0; i<Q; i++) printf("%d\n", tar.res[i]);
	}
	return 0;
}

void Tarjan::LCA(Graph *g)
{
	G=g;
	for(int i=1; i<=G->ndn; i++) unin[i]=i;
	CLR(dfsn);
	dist[1]=0;
	dfs(1);
}

int Tarjan::dfs(int u)
{
	dfsn[u]=1;
	for(int e=G->last[u]; ~e; e=G->nxt[e])
	{
		int v=G->v[e];
		if(dfsn[v]) continue;
		dist[v] = dist[u] + G->w[e];
		dfs(v);
		joint(u,v);
	}
	for(int i=0; i<(int)que[u].size(); i++)
	{
		int v=que[u][i];
		if(!dfsn[v]) continue;
		res[ id[u][i] ] = dist[u] + dist[v] - 2*dist[ find(v) ];
	}
	return 0;
}


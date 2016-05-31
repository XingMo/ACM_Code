/*
HDU - 3861
将图分成若干块，满足
1. 相互联通的两个点必须在同一块
2. 同一块中的任意两点，必须能单向可达

首先先用Tarjan缩点，
然后同一块的实际上必须在一条单向的路径上
然后问题就转化为了dag上不相交的最小路径覆盖

这个问题可以转化为二分图匹配解决
建立一个二分图，原图中任意一个点 u
在二分图中都拆成两个点，X部的u点和 Y部的 u'点
原图中的任意一条边 u->v在二分图中连上 u->v'
然后原图的总点数，减去二分图的最大匹配，即为最小路径覆盖

证明如下：
对于二分图 X部的一个点 u，如果他在 Y部有一个匹配 v'
那么对于原图，则代表了选定这条边 u->v，代表 u点在原图有后继
而没有匹配的点，即没有后继的点都是某条路径的终点，
所以原图中的路径数等于 X部中没有匹配的点数
当二分图最大匹配的时候，没有后继的点数最少
此时就产生了最小路径覆盖
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

const int maxn=5e3+10, maxm=1e5+10;
struct Graph
{
	int V,E;
	int edn, *last;
	int *u, *v, *nxt;
	Graph(int a, int b):V(a),E(b)
	{
		last=new int[V];
		u=new int[E]; v=new int[E]; nxt=new int[E];
		init();
	}
	~Graph(){delete []last;delete []u;delete []v;delete []nxt;}
	void init(){edn=0; memset(last,-1,sizeof(int)*V);}
	void adde(int tu, int tv)
	{
		u[edn] = tu;
		v[edn] = tv;
		nxt[edn] = last[tu];
		last[tu] = edn++;
	}
	void pri(){for(int i=0; i<edn; i++) printf("%d->%d\n", u[i], v[i]);}
};

struct Tarjan
{
	Graph &G;
	int dfst, dfsn[maxn], low[maxn];
	int scnt, scc[maxn];
	int skt, stak[maxn];
	bool ins[maxn];
	Tarjan(Graph &a):G(a){};
	int SCC(int);
	int dfs(int);
};

struct Hungarian
{
	Graph &G;
	int res, match[2*maxn];
	bool ins[2*maxn];
	Hungarian(Graph &a):G(a){};
	int solve(int);
	int dfs(int);
};

int N,M;
Graph graph(maxn,maxm), div_g(2*maxn,maxm);
Tarjan tarjan(graph);
Hungarian hug(div_g);

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
		graph.init();
		div_g.init();
		scanf("%d%d", &N, &M);
		for(int i=0; i<M; i++)
		{
			int u,v;
			scanf("%d%d", &u, &v);
			graph.adde(u,v);
		}
		N = tarjan.SCC(N);
		for(int i=0; i<graph.edn; i++)
		{
			int u=graph.u[i], v=graph.v[i];
			div_g.adde(u,v+N);
		}
//		div_g.pri();
		int mcnt = hug.solve(2*N);
		printf("%d\n", N-mcnt);
	}
	return 0;
}

int Tarjan::SCC(int n)
{
	dfst=0; CLR(dfsn); CLR(low);
	scnt=0; CLR(scc);
	skt=0; CLR(ins);
	
	for(int i=1; i<=n; i++) if(!dfsn[i]) dfs(i);
	
	int tot=G.edn;
	G.init();
	for(int e=0; e<tot; e++)
	{
		int u=G.u[e], v=G.v[e];
		if(scc[u] == scc[v]) continue;
		G.adde(scc[u],scc[v]);
	}
	return scnt;
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
		scnt++;
		while(skt)
		{
			ins[ stak[skt] ] = 0;
			scc[ stak[skt] ] = scnt;
			skt--;
			if(stak[skt+1] == u) break;
		}
	}
	
	return 0;
}

int Hungarian::solve(int n)
{
	res=0;
	CLR(match);
	for(int i=1; i<=n; i++)
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


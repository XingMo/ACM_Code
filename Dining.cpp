/*
POJ - 3281
有 N头牛，F种食物，D种饮料
每种食物和饮料都只有一份
每头牛都只食用固定的几种食物和饮料
问如何安排使得尽量多的牛同时有食物和饮料

这题算是网络流入门题 + 试板题了
刚开始想得太简单了，
从源点向每个食物连容量为 1的边
从每个饮料向汇点连容量为 1的边
然后对于每头牛，从它喜欢的食物向它连一条容量为 1的边
然后再从它向它喜欢的饮料连一条容量为 1的边
做到这一步还不够，要保证每头牛都只被计算过一次
换句话来说，要保证每头牛都只享用了一份食物和饮料
所以要将每头牛拆成两个点，然后两个点之间连一条容量为 1的边
同时食物连来的点连到左边那个点，从右边那个点连到饮料
*/
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

const int maxn=110, maxm=2*maxn*maxn;
const int INF=0x3f3f3f3f;
struct Graph
{
	int ndn, edn, last[4*maxn];
	int u[3*maxm], v[3*maxm], c[3*maxm], nxt[3*maxm];
	void init(int _n){ ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u, int _v, int _c)
	{
		u[edn]=_u; v[edn]=_v; c[edn]=_c;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};
struct Dinic
{
	Graph *G;
	int S,T,dist[4*maxn],cur[4*maxn];
	int bfs();
	int dfs(int,int);
	int solve(Graph*,int,int);
};

int N,F,D;
Graph G;
Dinic dinic;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d%d", &N, &F, &D))
	{
		G.init(N+N+F+D+2);
		int S=0, T=N+N+F+D+1;
		for(int i=1; i<=F; i++) G.adde(S,i,1), G.adde(i,S,0);
		for(int i=F+1; i<=F+D; i++) G.adde(i,T,1), G.adde(T,i,0);
		for(int i=1, id, fc, dc, x; i<=N; i++)
		{
			id=F+D+i;
			scanf("%d%d", &fc, &dc);
			for(int j=1; j<=fc; j++)
			{
				scanf("%d", &x);
				G.adde(x, id, 1); G.adde(id, x, 0);
			}
			for(int j=1; j<=dc; j++)
			{
				scanf("%d", &x);
				G.adde(id+N, F+x, 1); G.adde(F+x, id+N, 0);
			}
			G.adde(id, id+N, 1); G.adde(id+N, id, 0);
		}
		printf("%d\n", dinic.solve(&G,S,T));
	}
	return 0;
}

int Dinic::solve(Graph *_g, int _s, int _t)
{
	G=_g; S=_s; T=_t;
	int res=0;
	while(bfs())
	{
		for(int i=0; i< G->ndn; i++) cur[i] = G->last[i];
		res += dfs(S,INF);
	}
	return res;
}

int Dinic::bfs()
{
	MST(dist,-1);
	dist[S]=0;
	queue<int> que;
	que.push(S);
	
	while(que.size())
	{
		int u=que.front(); que.pop();
		for(int e=G->last[u], v; ~e; e=G->nxt[e])
		{
			v = G->v[e];
			if(dist[v]==-1 && G->c[e]>0)
			{
				dist[v] = dist[u] + 1;
				que.push(v);
			}
		}
	}
	
	return ~dist[T];
}

int Dinic::dfs(int u, int tmin)
{
	if(u==T || tmin==0) return tmin;
	int nflw=0, f;
	for(int &e=cur[u],v; ~e; e=G->nxt[e])
	{
		v=G->v[e];
		if(dist[u]+1==dist[v] && (f = dfs( v, min(tmin, G->c[e]) )) > 0)
		{
			G->c[e] -= f;
			G->c[e^1] += f;
			nflw += f;
			tmin -= f;
			if(tmin==0) break;
		}
	}
	return nflw;
}

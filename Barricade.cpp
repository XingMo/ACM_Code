/*
HDU - 5889
给定一张无向图，每条边的长度为 1
要求在 1到 N的最短路上放一些陷阱
使得 1到 N的每条最短路上至少有一个陷阱
其中在某条边上修陷阱有一个代价，求最小代价和

很显然的一个最小割
首先先用 SPFA把最短路求出来，然后依据最短路建图
然后再在新图上跑网络流即可
注意这个流量是有方向的，最短路上的反向边容量应该清零
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
#include <complex>
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

const int maxn=1e3+10, maxm=2e4+10;
struct Graph
{
	int ndn, edn, last[maxn];
	int u[maxm], v[maxm], w[maxm], nxt[maxm];
	void init(int _n){ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u, int _v, int _w)
	{
		u[edn]=_u; v[edn]=_v; w[edn]=_w;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};

struct Dinic
{
	Graph *G;
	int S, T, dist[maxn], cur[maxn];
	int bfs();
	int dfs(int,int);
	int solve(Graph*,int,int);
};

int N,M;
Graph G;
Dinic din;

int dist[maxn];
bool inq[maxn], have[maxm];
void SPFA(int,int);

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
		for(int i=0,u,v,w; i<M; i++)
		{
			scanf("%d%d%d", &u, &v, &w);
			G.adde(u,v,w); G.adde(v,u,w);
		}
		SPFA(1,N);
		int ans = din.solve(&G, 1, N);
		printf("%d\n", ans);
	}
	return 0;
}

void SPFA(int S, int T)
{
	CLR(inq); MST(dist,0x3f); CLR(have);
	queue<int> que;
	inq[S] = 1;
	dist[S] = 0;
	que.push(S);
	
	while(que.size())
	{
		int u=que.front(); que.pop();
		for(int e=G.last[u], v; ~e; e=G.nxt[e])
		{
			v = G.v[e];
			if(dist[v] > dist[u] + 1)
			{
				dist[v] = dist[u] + 1;
				if(!inq[v])
				{
					inq[v] = 1;
					que.push(v);
				}
			}
		}
		inq[u] = 0;
	}

	CLR(inq);
	while(que.size()) que.pop();
	que.push(T);
	inq[T] = 1;
	while(que.size())
	{
	 	int v=que.front(); que.pop();
	 	for(int e=G.last[v], u; ~e; e=G.nxt[e])
	 	{
	 		u = G.v[e];
	 		if(dist[u]+1==dist[v])
	 		{
	 			have[e] = have[e^1] = 1;
	 			G.w[e] = 0;
	 			if(!inq[u])
	 			{
		 			que.push(u);
		 			inq[u] = 1;
	 			}
	 		}
	 	}
	}
}

int Dinic::solve(Graph *g,int s, int t)
{
	G=g; S=s; T=t;
	int res=0;
	while(bfs()) 
	{
		for(int i=1; i<=G->ndn; i++) cur[i]=G->last[i]; // cur_init for all node (start from 1)
		res+=dfs(S,1e9);
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
		for(int e=G->last[u]; ~e; e=G->nxt[e])
		{
			int v=G->v[e];
			if(have[e] && dist[v]==-1 && G->w[e] > 0)
			{
				dist[v] = dist[u] + 1;
				que.push(v);
			}
		}
	}
	
	return ~dist[T];
}

int Dinic::dfs(int u,int tmin)
{
	if(u==T || tmin==0) return tmin;
	int nflw=0, f;
	for(int &e=cur[u]; ~e; e=G->nxt[e])
	{
		int v=G->v[e];
		if(dist[u]+1==dist[v] && (f = dfs(v, min(tmin, G->w[e]))) > 0)
		{
			G->w[e] -= f;
			G->w[e^1] += f;
			nflw += f;
			tmin -= f;
			if(tmin==0) break;
		}
	}
	return nflw;
}

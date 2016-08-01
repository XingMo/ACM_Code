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
struct Graph
{
	int ndn,edn,last[2*maxn];
	int u[maxm], v[maxm], w[maxm], c[maxm], nxt[maxm];
	void init(int _n){ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u, int _v, int _w, int _c)
	{
		u[edn]=_u; v[edn]=_v; w[edn]=_w; c[edn]=_c;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};
struct EdmondKarp
{
	Graph *G;
	int S,T, dist[2*maxn], delt[2*maxn], pre[2*maxn];
	bool inq[2*maxn];
	int spfa();
	Pii solve(Graph*,int,int);
};

int N,M;
Graph G;
EdmondKarp ek;
char Map[maxn][maxn];
vector<Pii> house, man;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		if(N==0 && M==0) break;
		CLR(Map);
		house.clear(); man.clear();
		for(int i=0; i<N; i++)
		{
			scanf(" %s", Map[i]);
			for(int j=0; j<M; j++)
			{
				if(Map[i][j]=='H') house.push_back({i,j});
				if(Map[i][j]=='m') man.push_back({i,j});
			}
		}
		int hcnt=house.size(), mcnt=man.size();
		int S=0, T=hcnt+mcnt + 1;
		G.init(T+1);
		for(int i=1; i<=mcnt; i++) G.adde(S, i, 0, 1), G.adde(i, S, 0, 0);
		for(int i=1; i<=hcnt; i++) G.adde(i+mcnt, T, 0, 1), G.adde(T, i+mcnt, 0, 0);
		for(int i=1; i<=mcnt; i++)
		{
			for(int j=1; j<=hcnt; j++)
			{
				int d = abs(man[i-1].first-house[j-1].first) + abs(man[i-1].second-house[j-1].second);
				G.adde(i, j+mcnt, d, 1), G.adde(j+mcnt, i, -d, 0);
			}
		}
//		for(int i=0; i<G.edn; i+=2) printf("%d -> %d: %d\n", G.u[i], G.v[i], G.w[i]);
		Pii ans = ek.solve(&G,S,T);
		printf("%d\n", ans.second);
	}
	return 0;
}

Pii EdmondKarp::solve(Graph *g, int s, int t)
{
	G=g; S=s; T=t;
	int res=0, cost=0;
	while(spfa())
	{
		res += delt[T];
		cost += dist[T]*delt[T];
		for(int v=T; v!=S; v = G->u[pre[v]])
		{
			G->c[pre[v]] -= delt[T];
			G->c[pre[v]^1] += delt[T];
		}
	}
	return Pii(res,cost);
}

int EdmondKarp::spfa()
{
	MST(dist,0x3f); MST(pre,-1);
	CLR(inq);
	queue<int> que;
	que.push(S);
	dist[S]=0; delt[S]=0x3f3f3f3f;
	inq[S]=1;
	
	while(que.size())
	{
		int u=que.front(); que.pop();
		for(int e=G->last[u], v; ~e; e=G->nxt[e]) if(G->c[e] > 0)
		{
			v=G->v[e];
			if(dist[v] > dist[u] + G->w[e])
			{
				dist[v] = dist[u] + G->w[e];
				delt[v] = min(delt[u], G->c[e]);
				pre[v] = e;
				if(!inq[v])
				{
					inq[v]=1;
					que.push(v);
				}
			}
		}
		inq[u]=0;
	}
	
	return dist[T] < 0x3f3f3f3f;
}

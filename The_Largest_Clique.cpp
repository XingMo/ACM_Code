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
#define Sqr(a) ((a)*(a))

const int maxn=1e3+10, maxm=5e4+10;
struct Graph
{
	int ndn, edn, last[maxn];
	int u[maxm],v[maxm],nxt[maxm];
	int nval[maxn], ind[maxn];
	void init(int n){ndn=n; edn=0; MST(last,-1); CLR(nval); CLR(ind);}
	void adde(int tu, int tv)
	{
		u[edn]=tu; v[edn]=tv;
		nxt[edn]=last[tu];
		last[tu]=edn++;
		ind[tv]++;
	}
	void pri(){for(int i=0; i<edn; i++) printf("%d->%d\n", u[i], v[i]);}
};

struct Tarjan
{
	Graph *G;
	int dfst, dfsn[maxn], low[maxn];
	int scc_cnt, scc[maxn], sccval[maxn];
	int skt, stak[maxn];
	bool ins[maxn];
	int SCC(Graph *g);
	int dfs(int);
};

int N,M;
Graph G;
Tarjan tarjan;
int dp[maxn];
bool inq[maxn];

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
		tarjan.SCC(&G);
		
		CLR(dp); CLR(inq);
		queue<int> que;
		for(int i=1; i<=G.ndn; i++) if(!G.ind[i]) {que.push(i); inq[i]=1;}
		int ans=0;
		
		while(que.size())
		{
			int u=que.front(); que.pop();
			ans=max(ans, dp[u]+G.nval[u]);
			for(int e=G.last[u]; ~e; e=G.nxt[e])
			{
				int v=G.v[e];
				if(dp[u] + G.nval[u] > dp[v])
				{
					dp[v]=dp[u]+G.nval[u];
					if(!inq[v])
					{
						inq[v]=1;
						que.push(v);
					}
				}
			}
			inq[u]=0;
		}
		
		printf("%d\n", ans);
	}
	return 0;
}

int Tarjan::SCC(Graph *g)
{
	G=g;
	dfst=0; CLR(dfsn); CLR(low);
	scc_cnt=0; CLR(scc); CLR(sccval);
	skt=0; CLR(ins);
	
	for(int i=1; i<=G->ndn; i++) if(!dfsn[i]) dfs(i);
	
	int tot=G->edn;
	G->init(scc_cnt);
	for(int i=1; i<=scc_cnt; i++) G->nval[i]=sccval[i];
	for(int i=0; i<tot; i++)
	{
		int u=G->u[i], v=G->v[i];
		if(scc[u]==scc[v]) continue;
		else G->adde(scc[u], scc[v]);
	}
	return scc_cnt;
}

int Tarjan::dfs(int u)
{
	dfsn[u] = low[u] = ++dfst;
	stak[++skt] = u;
	ins[u]=1;
	for(int e=G->last[u]; ~e; e=G->nxt[e])
	{
		int v=G->v[e];
		if(!dfsn[v])
		{
			dfs(v);
			low[u]=min(low[u],low[v]);
		}
		else if(ins[v]) low[u]=min(low[u], low[v]);
	}
	if(low[u]==dfsn[u])
	{
		int cnt=0;
		scc_cnt++;
		while(skt)
		{
			ins[ stak[skt] ] = 0;
			scc[ stak[skt] ] = scc_cnt;
			skt--;
			cnt++;
			if( stak[skt+1]==u ) break;
		}
		sccval[scc_cnt]=cnt;
	}
	return 0;
}


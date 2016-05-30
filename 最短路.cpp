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

const int maxn=1e3+10,maxm=1e5+10, INF=0x3f3f3f3f;
struct Graph
{
	int ndn, edn, last[maxn];
	int capt[maxm], flow[maxm];
	int u[maxm], v[maxm], w[maxm], nxt[maxm];
	void init(int a){ndn=a; edn=0; MST(last,-1); CLR(capt); CLR(flow);}
	void adde(int tu,int tv,int tw, int tc=0)
	{
		u[edn]=tu; v[edn]=tv; w[edn]=tw;
		capt[edn]=tc;
		nxt[edn]=last[tu];
		last[tu]=edn++;
	}
};

struct Dinic
{
	Graph &G;
	int S, T, dist[maxn], cur[maxn];
	Dinic(Graph &g):G(g){};
	int BFS();
	int DFS(int,int);
	int solve(int,int);
};

int N,M;
Graph G, dG;
Dinic dinic(dG);
vector<int> pre[maxn];
int dist[maxn];
bool inq[maxn];
int que[6*maxm];
int cnt[maxn];

int SPFA(int,int);
void construct(int);

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
		for(int i=1; i<=N; i++) pre[i].clear();
		
		for(int i=0; i<M; i++)
		{
			int u,v,w;
			scanf("%d%d%d", &u, &v, &w);
			G.adde(u,v,w);
		}
		int stp,fnp;
		scanf("%d%d", &stp, &fnp);
		int res=SPFA(stp,fnp);
//		printf("res=%d\n", res);
		construct(fnp);
		printf("%d\n", dinic.solve(stp,fnp));
	}
	return 0;
}

void construct(int T)
{
	dG.init(N);
	int head=0, tail=0;
	CLR(inq);
	que[tail++]=T;
	inq[T]=1;
	while(head<tail)
	{
		int v=que[head++];
		for(int i=0; i<(int)pre[v].size(); i++)
		{
			int e=pre[v][i], u=G.u[e];
			dG.adde(u,v,0,1);
			dG.adde(v,u,0,0);
			if(!inq[u])
			{
				inq[u]=1;
				que[tail++]=u;
			}
		}
	}
}

int SPFA(int S, int T)
{
	CLR(inq); MST(dist,0x3f);
	int head=0, tail=0;
	inq[S]=0;
	dist[S]=0;
	que[tail++]=S;
	
	while(head<tail)
	{
		int u=que[head++];
		for(int e=G.last[u]; ~e; e=G.nxt[e])
		{
			int v=G.v[e], w=G.w[e];
			if(dist[v] >= dist[u] + w)
			{
				if(dist[v] == dist[u] + w) pre[v].push_back(e);
				else
				{
					pre[v].clear();
					pre[v].push_back(e);
					dist[v] = dist[u] + w;
				}
				if(!inq[v])
				{
					inq[v]=1;
					que[tail++]=v;
				}
			}
		}
		inq[u]=0;
	}
	
	return dist[T];
}

int Dinic::solve(int ts, int tt)
{
	S=ts; T=tt;
	int res=0;
	while(BFS()) 
	{
		for(int i=1; i<=G.ndn; i++) cur[i]=G.last[i];	
		res+=DFS(S,INF);
	}
	return res;	
}

int Dinic::BFS()
{
	CLR(dist);
	queue<int> que;
	que.push(S);
	
	while(que.size())
	{
		int u=que.front(); que.pop();
		for(int e=G.last[u]; ~e; e=G.nxt[e])
		{
			int v=G.v[e];
			if(!dist[v] && G.capt[e] > G.flow[e])
			{
				dist[v] = dist[u] + 1;
				que.push(v);
			}
		}
	}
	
	return dist[T];
}

int Dinic::DFS(int u,int tmin)
{
	if(u==T || tmin==0) return tmin;
	int nflw=0, f;
	for(int &e=cur[u]; ~e; e=G.nxt[e])
	{
		int v=G.v[e];
		if(dist[u]+1==dist[v] && (f = DFS(v, min(tmin, G.capt[e]-G.flow[e]))) > 0)
		{
			G.flow[e]+=f;
			G.flow[e^1]-=f;
			nflw+=f;
			tmin-=f;
			if(tmin==0) break;
		}
	}
	return nflw;
}

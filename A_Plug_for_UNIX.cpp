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

const int maxn=510, maxm=2*maxn*maxn;
struct Graph
{
	int ndn,edn,last[maxn];
	int u[2*maxm], v[2*maxm], c[2*maxm], nxt[2*maxm];
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
	int S,T,dist[maxn],cur[maxn];
	int bfs();
	int dfs(int,int);
	int solve(Graph*,int,int);
};

map<string,int> acp;
int relat[maxn];
bool Map[maxn][maxn];
Graph G;
Dinic dinic;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	string buff;
	int N, M, K, aid;
	cin >> N;
	aid=N;
	for(int i=1; i<=N; i++)
	{
		cin.get();
		cin >> buff;
		acp.insert({buff,i});
	}
	cin >> M;
	for(int i=1,u,v; i<=M; i++)
	{
		cin.get();
		cin >> buff;
		cin.get();
		cin >> buff;
		if(acp.find(buff) == acp.end()) acp.insert({buff,++aid});
		v = acp[buff];
		relat[i] = v;
	}
	cin >> K;
	CLR(Map);
	for(int i=1,u,v; i<=K; i++)
	{
		cin.get();
		cin >> buff;
		if(acp.find(buff) == acp.end()) acp.insert({buff,++aid});
		u = acp[buff];
		cin.get();
		cin >> buff;
		if(acp.find(buff) == acp.end()) acp.insert({buff,++aid});
		v = acp[buff];
		Map[u][v] = 1;
	}
	for(int i=1; i<=aid; i++) Map[i][i] = 1;
	for(int k=1; k<=aid; k++) for(int i=1; i<=aid; i++) for(int j=1; j<=aid; j++)
		Map[i][j] |= Map[i][k]&Map[k][j];
	
	int S=0, T=N+M+1;
	G.init(N+M+2);
	for(int i=1; i<=M; i++) G.adde(S, i, 1), G.adde(i, S, 0);
	for(int i=1; i<=N; i++) G.adde(M+i, T, 1), G.adde(T, M+i, 0);
	for(int i=1; i<=M; i++)
	{
		int v=relat[i];
		for(int j=1; j<=N; j++) if(Map[v][j])
		{
			G.adde(i, j+M, 1); G.adde(j+M, i, 0);
		}
	}
	printf("%d\n", M-dinic.solve(&G,S,T));
	return 0;
}

int Dinic::solve(Graph *g, int s, int t)
{
	G=g, S=s, T=t;
	int res=0;
	while(bfs())
	{
		for(int i=0; i<G->ndn; i++) cur[i]=G->last[i];
		res += dfs(S,1e9);
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
		for(int e=G->last[u],v; ~e; e=G->nxt[e])
		{
			v = G->v[e];
			if(dist[v]==-1 && G->c[e]>0)
			{
				dist[v] = dist[u]+1;
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
		if(dist[u]+1==dist[v] && ( f=dfs(v, min(tmin,G->c[e]))) > 0)
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

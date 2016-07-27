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
//void pause(int t){int nt=clock(); while(clock()<nt+t);}

const int maxn = 300+10, maxm = 4e4+10;
const int dir[4][2]={0,1,0,-1,1,0,-1,0};
const int INF=0x3f3f3f3f;
struct Graph
{
	int ndn, edn, last[maxn];
	int u[maxm], v[maxm], flw[maxm], cap[maxm], nxt[maxm];
	void init(int _n){ ndn=_n; edn=0; MST(last,-1); CLR(flw); CLR(cap);}
	void adde(int _u, int _v, int _c)
	{
		u[edn]=_u; v[edn]=_v; cap[edn]=_c;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};

struct Dinic
{
	Graph *G;
	int S, T, dist[maxn], cur[maxn];
	int BFS();
	int DFS(int,int);
	int solve(Graph*,int,int);
};

int N,T;
char sci[15][15], cap[15][15];
int death[15][15], idsci[15][15], idcap[15][15];
int dist[15][15];
Graph G;
Dinic dinic;

bool judge(int x,int y){return x<0 || x>=N || y<0 || y>=N || !isdigit(sci[x][y]);}

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif

	int zx,zy;
	G.init(1);
	scanf("%d%d", &N, &T);
	for(int i=0; i<N; i++)
	{
		scanf(" %s", sci[i]);
		for(int j=0; j<N; j++)
		{
			if(isdigit(sci[i][j]) && sci[i][j]>='1')
			{
				idsci[i][j] = ++G.ndn;
				G.adde(0, G.ndn, sci[i][j]-'0');
				G.adde(G.ndn, 0, 0);
			}
			if(sci[i][j]=='Z'){zx=i; zy=j;}
		}
	}
	for(int i=0; i<N; i++)
	{
		scanf(" %s", cap[i]);
		for(int j=0; j<N; j++)
		{
			if(isdigit(cap[i][j]) && cap[i][j]>='1')
			{
				idcap[i][j] = ++G.ndn;
				G.adde(G.ndn, 1, cap[i][j]-'0');
				G.adde(1, G.ndn, 0);
			}
		}
	}
	queue<Pii> que;
	MST(death,0x3f);
	death[zx][zy]=0;
	que.push({zx,zy});
	while(que.size())
	{
		Pii u=que.front(); que.pop();
		int d=death[u.first][u.second]+1;
		for(int k=0; k<4; k++)
		{
			int x=u.first + dir[k][0];
			int y=u.second + dir[k][1];
			if(judge(x,y) || death[x][y]<INF) continue;
			death[x][y]=d;
			que.push({x,y});
		}
	}
	for(int i=0; i<N; i++) for(int j=0; j<N; j++) if(isdigit(sci[i][j]) && sci[i][j]>='1')
	{
		while(que.size()) que.pop();
		MST(dist,0x3f);
		dist[i][j] = 0;
		que.push({i,j});
		while(que.size())
		{
			Pii u=que.front(); que.pop();
			if(idcap[u.first][u.second])
			{
				G.adde(idsci[i][j], idcap[u.first][u.second], sci[i][j]-'0');
				G.adde(idcap[u.first][u.second], idsci[i][j], 0);
			}
			int d = dist[u.first][u.second]+1;
			if(d > T || dist[u.first][u.second] >= death[u.first][u.second]) continue;
			for(int k=0; k<4; k++)
			{
				int x = u.first + dir[k][0];
				int y = u.second + dir[k][1];
				if(judge(x,y) || dist[x][y]<INF || death[x][y] < d) continue;
				dist[x][y] = d;
				que.push({x,y});
			}
		}
	}
	printf("%d\n", dinic.solve(&G,0,1));
	return 0;
}

int Dinic::solve(Graph *g,int ts, int tt)
{
	G=g;
	S=ts; T=tt;
	int res=0;
	while(BFS()) 
	{
		for(int i=0; i<=G->ndn; i++) cur[i]=G->last[i];	
		res+=DFS(S,1e9);
	}
	return res;	
}

int Dinic::BFS()
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
			if(dist[v]==-1 && G->cap[e] > G->flw[e])
			{
				dist[v] = dist[u] + 1;
				que.push(v);
			}
		}
	}
	
	return ~dist[T];
}


int Dinic::DFS(int u,int tmin)
{
	if(u==T || tmin==0) return tmin;
	int nflw=0, f;
	for(int &e=cur[u]; ~e; e=G->nxt[e])
	{
		int v=G->v[e];
		if(dist[u]+1==dist[v] && (f = DFS(v, min(tmin, G->cap[e]-G->flw[e]))) > 0)
		{
			G->flw[e]+=f;
			G->flw[e^1]-=f;
			nflw+=f;
			tmin-=f;
			if(tmin==0) break;
		}
	}
	return nflw;
}


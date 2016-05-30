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

const int maxn=1e4+10, maxm=1e5+10, INF=0x3f3f3f3f;
struct Edge{int u,v,nxt;};

int N,M;

int last[maxn], edn;
Edge edge[maxm];

int dfst, dfsn[maxn], low[maxn];
int scc[maxn], scnt;
int stak[maxn], skt;
bool ins[maxn];

void adde(int,int);
int Tarjan(int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M) && N)
	{
		edn=0;
		MST(last,-1);
		dfst=0; CLR(dfsn); CLR(low);
		CLR(scc); scnt=0;
		skt=0; CLR(ins);
		
		for(int i=0; i<M; i++)
		{
			int u,v;
			scanf("%d%d", &u, &v);
			adde(u,v);
		}
		
		Tarjan(1);
		bool ok=1;
		for(int i=2; i<=N; i++) if(scc[i]!=scc[1]) {ok=0; break;}
		puts(ok?"Yes":"No");
	}	
	return 0;
}

void adde(int u,int v)
{
	edge[edn].u = u;
	edge[edn].v = v;
	edge[edn].nxt = last[u];
	last[u]=edn++;
}

int Tarjan(int u)
{
	dfsn[u] = ++dfst;
	low[u] = dfst;
	stak[++skt] = u;
	ins[u]=1;
	
	for(int e=last[u]; ~e; e=edge[e].nxt)
	{
		int v=edge[e].v;
		if(!dfsn[v])
		{
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if(ins[v])
		{
			low[u] = min(low[u], low[v]);
		}
	}
	
	if(low[u] == dfsn[u])
	{
		scnt++;
		while(skt)
		{
			scc[ stak[skt] ] = scnt;
			ins[ stak[skt] ] = 0;
			skt--;
			if( stak[skt + 1] == u) break;
		}
	}
	
	return 0;
}

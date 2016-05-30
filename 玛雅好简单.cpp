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

const int maxn=1e4+10, maxm=2e4+10;
struct Edge{int u,v,nxt;};

int N,M;
int edn,last[maxn];
Edge edge[maxm*2];
bool eban[maxm*2];

int dfst, dfsn[maxn], low[maxn];
int cut_res;

void adde(int,int);
int Tarjan(int);

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
		edn=0; MST(last,-1); CLR(eban);
		dfst=0; CLR(dfsn); CLR(low);
		scanf("%d%d", &N, &M);
		for(int i=0; i<M; i++)
		{
			int u,v;
			scanf("%d%d", &u, &v);
			adde(u,v); adde(v,u);
		}
		cut_res=0;
		for(int i=1; i<=N; i++) if(!dfsn[i]) Tarjan(i);
		printf("Case %d: %d\n", ck, cut_res);
	}	
	return 0;
}

void adde(int u, int v)
{
	edge[edn].u = u;
	edge[edn].v = v;
	edge[edn].nxt = last[u];
	last[u] = edn++;
}

int Tarjan(int u)
{
	dfsn[u] = low[u] = ++dfst;
	
	for(int e=last[u]; ~e; e=edge[e].nxt)
	{
		if(eban[e]) continue;
		eban[e]=1; eban[e^1]=1;
		int v=edge[e].v;
		if(!dfsn[v]) Tarjan(v);
		if(low[v] > dfsn[u]) cut_res++;
		low[u] = min(low[u], low[v]);
	}
	
	return 0;
}

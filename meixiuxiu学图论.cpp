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

const int maxn=5e5+10,maxm=2e6+10, INF=0x3f3f3f3f;
struct Graph
{
	int edn, last[maxn];
//	int u[2*maxm],
	int v[2*maxm],w[2*maxn],nxt[2*maxm];
	void init(){edn=0; MST(last,-1);}
	void adde(int tu, int tv, int tw)
	{
//		u[edn]=tu;
		v[edn]=tv;
		w[edn]=tw;
		nxt[edn]=last[tu];
		last[tu]=edn++;
	}
};
int N,M,Lim;
Graph G;
bool pban[maxn];
bool ins[maxn];
bool eban[2*maxm];

int dfs(int);

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
		G.init();
		CLR(pban); CLR(eban);
		scanf("%d%d", &N, &M);
		for(int i=0; i<M; i++)
		{
			int u,v,w;
			scanf("%d%d%d", &u, &v, &w);
			G.adde(u,v,w); G.adde(v,u,w);
		}
		int l=0, r=5010;
		while(l<r)
		{
			CLR(pban); CLR(eban);
			Lim=(l+r)>>1;
			bool ok=0;
			for(int i=1; i<=N; i++) if(!pban[i] && dfs(i)) {ok=1; break;}
			if(ok) r=Lim;
			else l=Lim+1;
		}
		if(l<=5000) printf("%d\n", l);
		else puts("No solution!");
	}	
	return 0;
}

int dfs(int u)
{
	pban[u]=1;
	for(int e=G.last[u]; ~e; e=G.nxt[e])
	{
		if(eban[e]) continue;
		eban[e]=1; eban[e^1]=1;
		int v=G.v[e];
		int w=G.w[e];
		if(w>Lim) continue;
		if(pban[v] || dfs(v)) return 1;
	}
	return 0;
}

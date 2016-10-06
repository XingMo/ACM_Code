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

const int maxn=30+10, maxm=2e3+10;
const LL INF=0x3f3f3f3f3f3f3f3f;
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

int N,M;
Graph G;
LL dist[maxn];
LL dijkstra(int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M) && N && M)
	{
		G.init(N);
		for(int i=0,u,v,w; i<M; i++)
		{
			scanf("%d%d%d", &u, &v, &w);
			G.adde(u,v,w); G.adde(v,u,w);
		}
		LL ans=0;
		for(int i=2; i<N; i++)
		{
			ans = max(ans, dijkstra(i));
		}
		if(ans==INF) puts("Inf");
		else printf("%lld\n", ans);
	}
	return 0;
}

struct mp
{
	LL d; int u;
	bool operator < (const mp &rhs) const {return d > rhs.d;}
};
LL dijkstra(int ban)
{
	MST(dist,0x3f);
	priority_queue<mp> que;
	dist[1] = 0;
	que.push({0,1});
	
	while(que.size())
	{
		int u=que.top().u;
		LL d=que.top().d; 
		que.pop();
		if(d > dist[u]) continue;
		for(int e=G.last[u], v; ~e; e=G.nxt[e]) if( (v = G.v[e]) != ban)
		{
			if(dist[u] + G.w[e] < dist[v])
			{
				dist[v] = dist[u] + G.w[e];
				que.push({dist[v],v});
			}
		}
	}
	
	return dist[N];
}

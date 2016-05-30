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

const int maxn=2*120+10, maxm=maxn*maxn;
struct Graph
{
	int ndn, edn, last[maxn];
	int u[maxm], v[maxm], nxt[maxm];
	void init(int n){ndn=n; edn=0; MST(last,-1);};
	void adde(int tu, int tv)
	{
		u[edn]=tu; v[edn]=tv;
		nxt[edn]=last[tu];
		last[tu]=edn++;
	}
};

struct Hungarian
{
	Graph &G;
	int res, match[maxn];
	bool ins[maxn];
	Hungarian(Graph &g):G(g){};
	int solve();
	int dfs(int);
};

int N,M;
Graph G;
Hungarian hug(G);

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
		G.init(2*N);
		for(int i=0; i<M; i++)
		{
			int u,v;
			scanf("%d%d", &u, &v);
			G.adde(u,v+N);
		}
		printf("%d\n", N-hug.solve());
	}
	return 0;
}

int Hungarian::solve()
{
	res=0;
	CLR(match);
	for(int i=1; i<=G.ndn; i++)
	{
		if(!match[i])
		{
			CLR(ins);
			if(dfs(i)) res++;
		}
	}
	return res;
}

int Hungarian::dfs(int u)
{
	for(int e=G.last[u]; ~e; e=G.nxt[e])
	{
		int v=G.v[e];
		if(ins[v]) continue;
		ins[v]=1;
		if(!match[v] || dfs(match[v]))
		{
			match[u]=v;
			match[v]=u;
			return 1;
		}
	}
	return 0;
}


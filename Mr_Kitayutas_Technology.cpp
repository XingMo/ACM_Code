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
#include <cassert>
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) ((a)*(a))

const int maxn=1e5+10;
struct Graph
{
	int ndn, edn, last[maxn];
	int u[2*maxn], v[2*maxn], nxt[2*maxn];
	int deg[maxn];
	void init(int _n){ ndn=_n; edn=0; MST(last,-1); CLR(deg);}
	void adde(int _u, int _v)
	{
		u[edn]=_u; v[edn]=_v;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};

int N,M;
Graph G;
bool inq[maxn];
int col[maxn], cir[maxn];

void color(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	scanf("%d%d", &N, &M);
	G.init(N);
	CLR(inq); CLR(col); CLR(cir);
	for(int i=0,u,v; i<M; i++)
	{
		scanf("%d%d", &u, &v);
		G.adde(u,v); G.adde(v,u);
		G.deg[v]++;
	}
	int nc=0;
	for(int i=1; i<=G.ndn; i++) if(!col[i]) color(i,++nc);
	int ans = G.ndn-nc;
	
	queue<int> que;
	for(int i=1; i<=G.ndn; i++) if(!G.deg[i]) que.push(i);
	while(que.size())
	{
		int u=que.front(); que.pop();
		inq[u]=1;
		for(int e=G.last[u]; ~e; e=G.nxt[e])
		{
			if(e&1) continue;
			int v=G.v[e];
			G.deg[v]--;
			if(!G.deg[v]) que.push(v);
		}
	}
	
	for(int i=1; i<=G.ndn; i++) if(!inq[i]) cir[ col[i] ]=1;
	for(int i=1; i<=nc; i++) ans += cir[i];
	
	printf("%d\n", ans);
	return 0;
}

void color(int u, int tc)
{
	col[u]=tc;
	for(int e=G.last[u]; ~e; e=G.nxt[e])
	{
		int v=G.v[e];
		if(col[v]) continue;
		color(v,tc);
	}
}

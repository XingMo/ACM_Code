/*
HDU - 5452
给定一张图以及图上的一个生成树
求图的一个最小的割集，并且这个割集中只包含生成树的一条边

考虑如果是一棵树的话，它的任意一条边都是一条割边
然后在生成树上加上非树边 (u,v)的时候，
想割去 (u,v)两点间的任意一条树边从而使联通块增加
都要额外割掉新加进来的这条边，所以给这条路径上的每条边权值都加一
然后问题就转化为了区间修改一条树上路径，然后查询单条边

所以先把树建好，跑一遍树链剖分，然后用树状数组维护一下
*/
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
#define PCUT puts("\n----------")

const int maxn=2e4+10;
struct Graph
{
	int ndn, edn, last[maxn];
	int u[2*maxn], v[2*maxn], nxt[2*maxn];
	void init(int _n){ ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u, int _v)
	{
		u[edn]=_u; v[edn]=_v;
		nxt[edn] = last[_u];
		last[_u] = edn++;
	}
};
struct BIT
{
	int bit[maxn], siz;
	void init(int _n) {siz=_n; CLR(bit);}
	void add(int p, int x) {for(int i=p; i<=siz; i+=i&-i) bit[i]+=x;}
	int sum(int p) {int res=0; for(int i=p; i>0; i-=i&-i) res += bit[i]; return res;}
	void update(int l,int r,int x) {add(l,x); add(r+1,-x);}
	int query(int p) {return sum(p);}
};

struct HLD
{
	Graph *G;
	BIT bit;
	int dfst, dfsn[maxn], dept[maxn], size[maxn], bson[maxn], fath[maxn], ntop[maxn];
	void init(Graph *g)
	{
		G=g;
		bit.init(G->ndn);
		dfst=0; dept[1] = 0; fath[1] = 0;
		CLR(dfsn); CLR(bson); CLR(ntop);
		dfs1(1);
		dfs2(1,1);
	}
	void dfs1(int);
	void dfs2(int,int);
	void update(int,int);
	int query(int);
};

int N,M;
Graph G;
HLD hld;

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
		for(int i=1, u, v; i<N; i++)
		{
			scanf("%d%d", &u, &v);
			G.adde(u,v); G.adde(v,u);
		}
		hld.init(&G);
		for(int i=0, x, y; i<M-N+1; i++)
		{
			scanf("%d%d", &x, &y);
			hld.update(x,y);
		}
		int ans=M;
		for(int i=2; i<=N; i++) ans = min(ans, hld.query(i));
		printf("Case #%d: %d\n", ck, ans+1);
	}
	return 0;
}

void HLD::dfs1(int u)
{
	size[u]=1;
	int tmax=-1;
	for(int e=G->last[u], v; ~e; e=G->nxt[e])
	{
		v=G->v[e];
		if(v==fath[u]) continue;
		dept[v] = dept[u] + 1;
		fath[v] = u;
		dfs1(v);
		if(size[v] > tmax)
		{
			tmax = size[v];
			bson[u] = v;
		}
		size[u] += size[v];
	}
}

void HLD::dfs2(int u, int top)
{
	dfsn[u] = ++dfst;
	ntop[u] = top;
	if(!bson[u]) return;
	dfs2(bson[u], top);
	for(int e=G->last[u], v; ~e; e=G->nxt[e])
	{
		v=G->v[e];
		if(v==fath[u] || v==bson[u]) continue;
		dfs2(v,v);
	}
}

void HLD::update(int x, int y)
{
	while(ntop[x] != ntop[y])
	{
		if( dept[ ntop[x] ] > dept[ ntop[y] ] ) swap(x,y);
		bit.update( dfsn[ ntop[y] ], dfsn[ y ], 1);
		y = fath[ ntop[y] ];
	}
	if( dept[x] > dept[y] ) swap(x,y);
	x = bson[x];
	bit.update( dfsn[x], dfsn[y], 1);
}

int HLD::query(int x)
{
	return bit.query( dfsn[x] );
}

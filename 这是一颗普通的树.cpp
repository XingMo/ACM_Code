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
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) ((a)*(a))

const int maxn=1e4+10, INF=0x3f3f3f3f;
struct Graph
{
	int ndn,edn,last[maxn];
	int u[2*maxn], v[2*maxn], w[2*maxn], nxt[2*maxn];
	void init(int _n){ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u, int _v, int _w)
	{
		u[edn]=_u; v[edn]=_v; w[edn]=_w;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};
struct SegmentTree
{
	struct node
	{
		int l,r,tmax,tmin,negtag;
		void pri(){printf("l:%d r:%d tmax:%d tmin:%d negtag:%d\n", l, r, tmax, tmin, negtag);}
	} segt[4*maxn];
	void build(int,int,int,int*);
	void change(int,int,int);
	void nega(int,int,int);
	int query(int,int,int);
	void pushdown(int);
	void maintain(int);
};
struct HLD
{
	Graph *G;
	int dfst, dfsn[maxn], dept[maxn], size[maxn], bson[maxn], fath[maxn], ntop[maxn];
	int pval[maxn], sque[maxn];
	SegmentTree tree;
	void init(Graph *g)
	{
		G=g;
		dfst=0;
		CLR(dfsn); CLR(dept); CLR(size); CLR(bson); CLR(fath); CLR(ntop);
		CLR(pval); CLR(sque);
		dfs1(1);
		dfs2(1,1);
		tree.build(1,1,G->ndn,sque);
	}
	void dfs1(int);
	void dfs2(int,int);
	void change(int,int);
	void nega(int,int);
	int query(int,int);
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
		for(int i=1; i<N; i++)
		{
			int u,v,w;
			scanf("%d%d%d", &u, &v, &w);
			G.adde(u,v,w); G.adde(v,u,w);
		}
		hld.init(&G);
		for(int i=0; i<M; i++)
		{
			int opt,a,b;
			scanf("%d%d%d", &opt, &a, &b);
			if(opt==1) hld.change(a,b);
			if(opt==2) hld.nega(a,b);
			if(opt==3) printf("%d\n", hld.query(a,b));
//			printf("%d\n", hld.tree.query(1,hld.dfsn[2],hld.dfsn[2]));
		}
	}
	return 0;
}

void HLD::change(int pos, int val)
{
	pos=(pos-1)*2;
	int u=G->u[pos], v=G->v[pos];
	if(dept[u]>dept[v]) swap(u,v);
	tree.change(1,dfsn[v],val);
}

void HLD::nega(int x, int y)
{
	if(x==y) return;
	while(ntop[x] != ntop[y])
	{
		if(dept[ ntop[x] ] > dept[ ntop[y] ]) swap(x,y);
//		printf("%d %d %d %d %d\n", x, y, ntop[y], dfsn[ntop[y]], dfsn[y]);
		tree.nega(1, dfsn[ntop[y]], dfsn[y]);
		y = fath[ ntop[y] ];
//		printf("res: %d\n", tree.query(1, dfsn[2], dfsn[2]));
	}
	if(x==y) return;
	if( dept[x] > dept[y] ) swap(x,y);
	x=bson[x];
	tree.nega(1, dfsn[x], dfsn[y]);
}

int HLD::query(int x, int y)
{
	if(x==y) return 0;
	int res=-INF;
	while(ntop[x] != ntop[y])
	{
		if(dept[ ntop[x] ] > dept[ ntop[y] ]) swap(x,y);
		res = max(res, tree.query(1, dfsn[ntop[y]], dfsn[y]));
		y = fath[ ntop[y] ];
	}
	if(x==y) return res;
	if( dept[x] > dept[y] ) swap(x,y);
	x=bson[x];
	res = max(res, tree.query(1, dfsn[x], dfsn[y]));
	return res;
}

void HLD::dfs1(int u)
{
	size[u]=1;
	int tmax=-1;
	for(int e=G->last[u]; ~e; e=G->nxt[e])
	{
		int v=G->v[e];
		if(v==fath[u]) continue;
		dept[v] = dept[u]+1;
		fath[v] = u;
		pval[v] = G->w[e];
		dfs1(v);
		if(size[v]>tmax)
		{
			tmax=size[v];
			bson[u]=v;
		}
		size[u] += size[v];
	}
}

void HLD::dfs2(int u,int top)
{
	dfsn[u]=++dfst;
	ntop[u]=top;
	sque[dfst]=pval[u];
	if(!bson[u]) return;
	dfs2(bson[u],top);
	for(int e=G->last[u]; ~e; e=G->nxt[e])
	{
		int v=G->v[e];
		if(dfsn[v]) continue;
		dfs2(v,v);
	}
}

void SegmentTree::build(int np, int nl, int nr, int sque[])
{
	node &now=segt[np];
	now.l=nl;
	now.r=nr;
	now.negtag=0;
	if(nl==nr)
	{
		now.tmax = now.tmin = sque[nl];
		return;
	}
	int mid=(nl+nr)>>1;
	build(np*2, nl, mid, sque);
	build(np*2+1, mid+1, nr, sque);
	now.tmax = max(segt[np*2].tmax, segt[np*2+1].tmax);
	now.tmin = min(segt[np*2].tmin, segt[np*2+1].tmin);
}

void SegmentTree::change(int np, int pos, int val)
{
	node &now=segt[np];
	if(now.l==now.r)
	{
		now.tmax = now.tmin = val;
		now.negtag=0;
		return;
	}
	int mid=(now.l+now.r)>>1;
	pushdown(np);
	if(pos<=mid)
	{
		change(np*2, pos, val);
		maintain(np*2+1);
	}
	else
	{
		change(np*2+1, pos, val);
		maintain(np*2);
	}
	maintain(np);
}

void SegmentTree::nega(int np, int ql, int qr)
{
	node &now=segt[np];
//	now.pri();
	if(ql<=now.l && now.r<=qr)
	{
		now.negtag ^= 1;
		maintain(np);
//		now.pri();
		return;
	}
	int mid=(now.l+now.r)>>1;
	pushdown(np);
	if(qr<=mid)
	{
		nega(np*2, ql, qr);
		maintain(np*2+1);
	}
	else if(ql>mid)
	{
		nega(np*2+1, ql, qr);
		maintain(np*2);
	}
	else
	{
		nega(np*2, ql, qr);
		nega(np*2+1, ql, qr);
	}
	maintain(np);
}

int SegmentTree::query(int np, int ql, int qr)
{
	node &now=segt[np];
//	now.pri();
	if(ql<=now.l && now.r<=qr) return now.tmax;
	int mid=(now.l+now.r)>>1;
	int tmax=-INF;
	pushdown(np);
	maintain(np*2);
	maintain(np*2+1);
	if(ql<=mid) tmax = max(tmax, query(np*2, ql, qr));
	if(qr>mid)  tmax = max(tmax, query(np*2+1, ql, qr));
	return tmax;
}

void SegmentTree::pushdown(int np)
{
	node &now=segt[np], &lson=segt[np*2], &rson=segt[np*2+1];
	lson.negtag ^= now.negtag;
	rson.negtag ^= now.negtag;
	now.negtag = 0;
}

void SegmentTree::maintain(int np)
{
	node &now=segt[np];
	if(now.l==now.r)
	{
		if(now.negtag)
		{
			now.tmax = now.tmin = -now.tmin;
			now.negtag = 0;
		}
	}
	else
	{
		node &lson=segt[np*2], &rson=segt[np*2+1];
		now.tmax = max(lson.tmax, rson.tmax);
		now.tmin = min(lson.tmin, rson.tmin);
		if(now.negtag)
		{
			now.tmax = -now.tmax;
			now.tmin = -now.tmin;
			swap(now.tmax, now.tmin);
		}
	}
}

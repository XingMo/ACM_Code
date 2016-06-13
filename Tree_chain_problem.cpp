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
#include <ctime>
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) ((a)*(a))

void pause(int t)
{
	int nt=time(0);
	while(time(0)<nt+t);
}
const int maxn=1e5+10, maxq=maxn;
struct Graph
{
	int ndn, edn, last[maxn];
	int u[maxn*2], v[maxn*2], nxt[maxn*2];
	void init(int tn){ ndn=tn; edn=0; MST(last,-1);};
	void adde(int tu, int tv)
	{
		u[edn]=tu; v[edn]=tv;
		nxt[edn]=last[tu];
		last[tu]=edn++;
	}
};

struct HLD
{
	Graph *G;
	int dfst;
	int dfsn[maxn], dept[maxn], size[maxn], bson[maxn], fath[maxn], ntop[maxn];
	void init(Graph *g)
	{
		G=g;
		dfst=0;
		CLR(dfsn); CLR(dept); CLR(size); CLR(bson); CLR(fath); CLR(ntop);
		dfs1(1);
		dfs2(1,1);
	}
	void dfs1(int);
	void dfs2(int,int);
	int LCA(int,int);
	int Get(int,int);
};

struct SegmentTree
{
	struct node
	{
		int l,r;
		int sum,dp;
		void pri()
		{
			printf("l:%d r:%d sum:%d dp:%d\n", l, r, sum, dp);
		}
	} segt[4*maxn];
	
	void build(int,int,int);
	void update(int,int,int,int);
	node query(int,int,int);
	void maintain(int);
};

int N,M;
Graph G;
HLD hld;
SegmentTree tree;

struct data
{
	int x,y,w;
	data(int tx, int ty, int tw):x(tx),y(ty),w(tw){}
};
vector<data> chain[maxn];
int sum[maxn], dp[maxn];

int DP(int,int);

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
			int u,v;
			scanf("%d%d", &u, &v);
			G.adde(u,v); G.adde(v,u);
		}
		hld.init(&G);
		tree.build(1,1,N);
		CLR(sum); CLR(dp);
		
		
		for(int i=1; i<=N; i++) chain[i].clear();
		for(int i=0; i<M; i++)
		{
			int x,y,w;
			scanf("%d%d%d", &x, &y, &w);
			chain[ hld.LCA(x,y) ].push_back(data(x, y, w));
		}
		
		DP(1,0);
		printf("%d\n", dp[1]);
	}
	return 0;
}

int DP(int u, int f)
{
//	printf("u=%d\n", u);
	for(int e=G.last[u]; ~e; e=G.nxt[e])
	{
		int v=G.v[e];
		if(v==f) continue;
		DP(v,u);
//		printf("u=%d\n", u);
		sum[u] += dp[v];
	}
	dp[u]=sum[u];
//	printf("%d %d %d\n", hld.dfsn[u], sum[u], dp[u]);
	tree.update(1,hld.dfsn[u],sum[u],dp[u]);
	for(int i=0; i<(int)chain[u].size(); i++)
	{
		int x=chain[u][i].x, y=chain[u][i].y, w=chain[u][i].w;
		dp[u] = max( dp[u], hld.Get(x,y)+w);
	}
	tree.update(1,hld.dfsn[u],sum[u],dp[u]);
	return 0;
}

void HLD::dfs1(int u)
{
	size[u]=1;
	int tmax=-1;
	for(int e=G->last[u]; ~e; e=G->nxt[e])
	{
		int v=G->v[e];
		if(v==fath[u]) continue;
		dept[v] = dept[u] + 1;
		fath[v] = u;
		dfs1(v);
		if(size[v]>tmax)
		{
			tmax=size[v];
			bson[u]=v;
		}
		size[u]+=size[v];
	}
}

void HLD::dfs2(int u,int top)
{
	dfsn[u]=++dfst;
	ntop[u]=top;
	if(!bson[u]) return;
	dfs2(bson[u], top);
	for(int e=G->last[u]; ~e; e=G->nxt[e])
	{
		int v=G->v[e];
		if(v==fath[u] || v==bson[u]) continue;
		dfs2(v,v);
	}
}

int HLD::LCA(int x, int y)
{
	while(ntop[x] != ntop[y])
	{
		if( dept[ ntop[x] ] > dept[ ntop[y] ] ) swap(x,y);
		y = fath[ ntop[y] ];
	}
	if( dept[x] > dept[y] ) swap(x,y);
	return x;
}

int HLD::Get(int x,int y)
{
	int res=0;
	SegmentTree::node r;
	while(ntop[x] != ntop[y])
	{
		if( dept[ ntop[x] ] > dept[ ntop[y] ] ) swap(x,y);
		r = tree.query(1, dfsn[ ntop[y] ], dfsn[y]);
		res += r.sum - r.dp;
		y=fath[ ntop[y] ];
	}
	if( dept[x] > dept[y] ) swap(x,y);
	r = tree.query(1, dfsn[x], dfsn[y]);
	res += r.sum - r.dp;
	r = tree.query(1, dfsn[x], dfsn[x]);
	res += r.dp;
	return res;
}

void SegmentTree::build(int np, int nl, int nr)
{
	node &now=segt[np];
	now.l = nl;
	now.r = nr;
	now.sum=0;
	now.dp=0;
	if(nl==nr) return;
	int mid=(nl+nr)>>1;
	build(np*2, nl, mid);
	build(np*2+1, mid+1, nr);
}

void SegmentTree::update(int np, int pos, int tsum, int tdp)
{
	node &now=segt[np];
	if(now.l==now.r)
	{
		now.sum=tsum;
		now.dp=tdp;
		return;
	}
	int mid=(now.l+now.r)>>1;
	if(pos<=mid) update(np*2, pos, tsum, tdp);
	else update(np*2+1, pos, tsum, tdp);
	maintain(np);
}

SegmentTree::node SegmentTree::query(int np, int ql, int qr)
{
	node &now=segt[np];
	if(ql<=now.l && now.r<=qr)
	{
		return now;
	}
	int mid=(now.l+now.r)>>1;
	node res;
	res.dp=res.sum=0;
	if(ql<=mid)
	{
		node tem = query(np*2, ql, qr);
		res.sum += tem.sum; res.dp += tem.dp;
	}
	if(qr>mid)
	{
		node tem = query(np*2+1, ql, qr);
		res.sum += tem.sum; res.dp += tem.dp;
	}
	return res;
}

void SegmentTree::maintain(int np)
{
	node &now=segt[np];
	if(now.l==now.r) return;
	node &lson=segt[np*2], &rson=segt[np*2+1];
	now.dp = lson.dp+rson.dp;
	now.sum = lson.sum+rson.sum;
}

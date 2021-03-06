/*
HDU - 5296
一棵树上有若干个点，每条边有一个边权
给一个初始为空的集合，每次向集合内添加一个点或者删除一个点
问每次操作结束后，将集合内所有点连起来的边权和为多少

假设集合内已经有一些点，那么再加一个点所增加的边权
将会是这个点到某一条链的距离

但是这条链不能随便挑选，否则可能会经过已经选择的边
挑选策略就是，找到集合内dfs序比当前点大和小的两个点组成的链
换句话来说，就是集合内dfs序最靠近当前点的两个点

设当前点 x，这样选链，选出的链是 (u,v)，并且设dfsn[u] < dfsn[v]
如果会经过已经选择的边，已经选择的点 y
那么，如果原树dfs是从 x->y的，那么 x就比 y的dfs序小
而 y比 u、v的dfs序都小，所以原树的dfs是从 y->x的
而这样一来，y的dfs序就比 u更靠近 x，同样不可能
所以，这样选链，x到链的路径上不会经过重复的边

删除的时候基本相同

设len(u,v)为链(u,v)的长度
树上一点 x到链 (u,v)的距离为
( len(u,x) + len(v,x) - len(u,v))/2
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
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) ((a)*(a))

const int maxn=1e5+10, maxq=maxn;
struct Graph
{
	int ndn, edn, last[maxn];
	int u[2*maxn], v[2*maxn], w[2*maxn], nxt[2*maxn];
	void init(int tn){ ndn=tn; edn=0; MST(last,-1);}
	void adde(int tu, int tv, int tw)
	{
		u[edn]=tu; v[edn]=tv; w[edn]=tw;
		nxt[edn]=last[tu];
		last[tu]=edn++;
	}
};

struct LCA
{
	Graph *G;
	int st[20][2*maxn]; // dfsn
	int dfst, stp, firp[maxn], dfsn[2][maxn], dist[maxn];
	void init(Graph*);
	int dfs(int);
	int get(int,int);
};

int N,Q;
Graph G;
LCA lca;
set<int> have;
bool intree[maxn];

int query(int);

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
		scanf("%d%d", &N, &Q);
		G.init(N);
		for(int i=1; i<N; i++)
		{
			int u,v,w;
			scanf("%d%d%d", &u, &v, &w);
			G.adde(u,v,w); G.adde(v,u,w);
		}
		lca.init(&G);
		have.clear();
		
		CLR(intree);
		int ans=0;
		printf("Case #%d:\n", ck);
		for(int i=0; i<Q; i++)
		{
			int opt, x;
			scanf("%d%d", &opt, &x);
			if(opt==1)
			{
				if(!intree[x])
				{
					ans += query(x);
					have.insert(lca.dfsn[0][x]);
					intree[x]=1;				
				}
			}
			else
			{
				if(intree[x])
				{
					have.erase(lca.dfsn[0][x]);
					ans -= query(x);
					intree[x]=0;				
				}
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}

int query(int x)
{
	int u,v,res;
	set<int>::iterator it;
	int *dist=lca.dist;
	if(!have.size()) res=0;
	else
	{
		it=have.lower_bound(lca.dfsn[0][x]);
		if(it==have.begin() || it==have.end())
		{
			u = lca.dfsn[1][*have.begin()];
			v = lca.dfsn[1][*have.rbegin()];
		}
		else
		{
			u = lca.dfsn[1][*it];
			it--;
			v = lca.dfsn[1][*it];
		}
		res = dist[x] + dist[lca.get(u,v)] - dist[lca.get(x,u)] - dist[lca.get(x,v)];
	}
	return res;
}

void LCA::init(Graph *g)
{
	G=g;
	dfst = stp = 0;
	CLR(firp); CLR(dfsn); CLR(dist);
	dfs(1);
	
	int Lim=log2(stp);
	for(int j=1; j<=Lim; j++)
	{
		int len=1<<j-1, nlim=stp-(1<<j)+1;
		for(int i=1; i<=nlim; i++)
			st[j][i] = min(st[j-1][i], st[j-1][i+len]);
	}
}

int LCA::dfs(int u)
{
	dfsn[0][u] = ++dfst;
	st[0][++stp] = dfst;
	firp[u] = stp;
	dfsn[1][dfst] = u;
	
	for(int e=G->last[u]; ~e; e=G->nxt[e])
	{
		int v=G->v[e];
		if(dfsn[0][v]) continue;
		dist[v] = dist[u] + G->w[e];
		dfs(v);
		st[0][++stp] = dfsn[0][u];
	}
	return 0;
}

int LCA::get(int x, int y)
{
	int l=firp[x], r=firp[y];
	if( r<l ) swap(l,r);
	int flr = log2( r-l+1 );
	int nlen = 1<<flr;
	return dfsn[1][ min(st[flr][l], st[flr][r-nlen+1]) ];
}

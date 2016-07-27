/*
HDU - 5409
当一条边是桥的时候，输出两边双联通分量中各一个点
要求输出的第一个点序号小于第二个点，，且第一个点尽可能大，
满足前一个条件的情况下，第二个点尽可能小

求桥没啥好说的，直接 Tarjan走起，但是输出就比较厉害了

首先如果桥边被割掉了，两边最大分别是 max0, max1
如果 max0>max1 ，那么输出 max1 max1 +1，否则输出 max0, max0 +1
这是因为 u<v ，所以只能输出较小的那个数，
而 u+1必定在另一个联通分块，否则 u+1可以更新 u
这样一来，v也尽可能地小了

然后求桥边的时候，要从第 n个点开始dfs
当一条桥边割掉以后，max0，max1里一定有一个是 n，n是最大的
那么我从 n的联通分块开始出发，
只要dfs的过程中维护一下某个节点子树上最大的节点编号，
这样就可求出另一个较小的
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

const int maxn=1e5+10, maxm=2e5+10;
struct Graph
{
	int ndn, edn, last[maxn];
	int u[maxm], v[maxm], nxt[maxm];
	void init(int _n){ ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u, int _v)
	{
		u[edn]=_u; v[edn]=_v;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};
struct Tarjan
{
	Graph *G;
	int dfst, dfsn[maxn], lowv[maxn], iscut[maxm/2];
	int pval[maxn];
	int dfs(int,int);
	void bridge();
	void solve(Graph*);
};
int N,M;
Graph G;
Tarjan tar;

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
		for(int i=0; i<M; i++)
		{
			int u,v;
			scanf("%d%d", &u, &v);
			G.adde(u,v); G.adde(v,u);
		}
		tar.solve(&G);
	}
	return 0;
}

void Tarjan::solve(Graph *g)
{
	G=g;
	bridge();
	for(int i=0; i<M ;i++)
	{
		if(!iscut[i])
		{
			printf("0 0\n");
			continue;
		}
		int u=G->u[i<<1], v=G->v[i<<1];
		if(dfsn[u] > dfsn[v]) printf("%d %d\n", pval[u], pval[u]+1);
		else printf("%d %d\n", pval[v], pval[v]+1);
	}
}

void Tarjan::bridge()
{
	dfst=0; CLR(dfsn); CLR(lowv); CLR(iscut);
	for(int i=G->ndn; i>=1; i--) if(!dfsn[i]) dfs(i,0);
}


int Tarjan::dfs(int u, int f)
{
	dfsn[u]=++dfst;
	lowv[u]=dfsn[u];
	pval[u]=u;
	for(int e=G->last[u]; ~e; e=G->nxt[e])
	{
		int v=G->v[e];
		if(v==f) continue;
		if(!dfsn[v]) pval[u] = max(pval[u], dfs(v,u));
		if(lowv[v]>dfsn[u]) iscut[e>>1]=1;
		lowv[u] = min(lowv[u], lowv[v]);
	}
	return pval[u];
}


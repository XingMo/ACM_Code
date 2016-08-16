/*
Codeforces - 231E
给定一个仙人掌图，问从 x点走到 y点有多少条路径
两条不同的路径必须每一条边都不相同

写了这个图论，相当于写了一个模拟
本来都是贴板的事，但是到仓库一看我并没有板
可能当初觉得很简单就没留板……
所以全程手写了，而且实际上我对图论并不是很熟
幸好不是在赛上，不然手速肯定被完爆

x到 y的路径，经过每个环的时候，就有两种走法
做法就是用边双联通分量对于每一个环缩成一个点，
每个大小大于 1的环权值为 2，否则就是 1
然后就变成了一棵树，预处理出根到每一点路径的前缀权值乘积
答案就是 x和y的前缀权值乘积，除两次lca(x,y)的前缀权值乘积，再乘一次 lca的权值
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
LL Pow(LL x, LL n, LL p)
{
	LL res=1;
	while(n)
	{
		if(n&1) res=res*x%p;
		x=x*x%p;
		n>>=1;
	}
	return res;
}
const int maxn=1e5+10;
const int MOD=1e9+7;
struct Graph
{
	int ndn, edn, last[maxn];
	int u[2*maxn], v[2*maxn], nxt[2*maxn];
	void init(int _n){ndn=_n; edn=0; MST(last,-1);}
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
	int dfst, dfsn[maxn], lowv[maxn], iscut[2*maxn];
	int col[maxn], nc;
	LL pval[maxn], pvalr[maxn];
	int que[2*maxn], firp[maxn], idfsn[maxn], tail;
	int st[20][2*maxn];
	
	int solve(Graph*);
	int dfs(int,int);
	int color(int);
	int precom(int,int,LL);
	void st_init();
	int LCA(int,int);
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
	
	while(~scanf("%d%d", &N, &M))
	{
		G.init(N);
		for(int i=0,u,v; i<M; i++)
		{
			scanf("%d%d", &u, &v);
			G.adde(u,v); G.adde(v,u);
		}
		tar.solve(&G);
	}
	return 0;
}

int Tarjan::solve(Graph *g)
{
	G=g;
	dfst=0; CLR(dfsn); CLR(lowv); CLR(iscut);
	dfs(1,0);
	
	nc=0; CLR(col); CLR(pval);
	for(int i=1; i<=G->ndn; i++) if(!col[i]) {nc++; pval[nc]=color(i);}
	for(int i=1; i<=nc; i++) if(pval[i]>2) pval[i]=2;
	
	int tot=G->edn;
	G->init(nc);
	for(int e=0, u, v; e<tot; e++)
	{
		u = G->u[e], v = G->v[e];
		if(col[u]!=col[v]) G->adde(col[u], col[v]); 
	}
	
	
	dfst=0; tail=0; CLR(dfsn); CLR(firp);
	precom(1,0,1);
	st_init();
	
	int K;
	scanf("%d", &K);
	for(int i=0,x,y,l; i<K; i++)
	{
		scanf("%d%d", &x, &y);
		x=col[x], y=col[y];
		l=LCA(x,y);
		int ans = pvalr[x]*pvalr[y]%MOD * Pow(SQR(pvalr[l])%MOD, MOD-2, MOD)%MOD * pval[l]%MOD;
		printf("%d\n", ans);
	}
	
}

int Tarjan::dfs(int u, int f)
{
	lowv[u] = dfsn[u] = ++dfst;
	
	for(int e=G->last[u], v; ~e; e=G->nxt[e])
	{
		v=G->v[e];
		if(v==f) continue;
		if(!dfsn[v])
		{
			lowv[u] = min(lowv[u], dfs(v,u));
			if(lowv[v] > dfsn[u]) iscut[e] = iscut[e^1] = 1;
		}
		else lowv[u] = min(lowv[u], dfsn[v]);
	}
	return lowv[u];
}
int Tarjan::color(int u)
{
	int cnt=1;
	col[u] = nc;
	for(int e=G->last[u], v; ~e; e=G->nxt[e])
	{
		v=G->v[e];
		if(col[v] || iscut[e]) continue;
		cnt+=color(v);
	}
	return cnt;
}
int Tarjan::precom(int u,int f,LL prod)
{
	dfsn[u]=++dfst;
	idfsn[dfst] = u;
	pvalr[u] = pval[u]*prod%MOD;
	que[++tail] = dfsn[u];
	firp[u] = tail;
	for(int e=G->last[u],v; ~e; e=G->nxt[e]) if((v=G->v[e])!=f)
	{
		precom(v,u,pvalr[u]);
		que[++tail] = dfsn[u];
	}
}
void Tarjan::st_init()
{
	for(int i=1; i<=tail; i++) st[0][i] = que[i];
	for(int j=1, lim, len; j<=20; j++)
	{
		len=1<<j-1; lim=tail-(1<<j)+1;
		for(int i=1; i<lim; i++)
		{
			st[j][i] = min(st[j-1][i], st[j-1][i+len]);
		}
	}
}

int Tarjan::LCA(int x, int y)
{
	x=firp[x], y=firp[y];
	if(x>y) swap(x,y);
	int flr=log2(y-x+1), len=1<<flr;
	return idfsn[ min(st[flr][x], st[flr][y-len+1]) ];
}

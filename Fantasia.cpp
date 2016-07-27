/*
HDU - 5739
给定一张无向图，每个点有个点权
一个图的权值计算为，现将同一联通分量的点权相乘
再将不同联通分量的点权相加
求图割去一个点后的权值

其中对于哪些非关节点，权值比较好计算
而对于关节点，割去之后图比较复杂
所以要用到一个叫做 Blocak Forest Data Structure的建图方式
首先求出图中的点双联通分量，对于每一个点双，新建一个点向其中所有点连边
新图就会变成一个森林，其中非关节点是叶子节点，而关节点和新建的点是内点
然后用树形统计一下每个点儿子的乘积和以及子树的乘积和
有一个trick就是有孤点的情况，孤点不会被记入点双，
所以特判一下，对于孤点直接计算答案即可
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
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define SQR(a) ((a)*(a))
#define PCUT puts("----------")

const int maxn=2e5+10, maxm=2e5+10;
const LL MOD=1e9+7;
struct Graph
{
	int ndn, edn, last[maxn<<1];
	int u[maxm<<1], v[maxm<<1], nxt[maxm<<1];
	LL pval[maxn<<1], allw[maxn<<1];
	void init(int _n){ ndn=_n; edn=0; MST(last,-1); }
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
	
	int dfst, dfsn[maxn], lowv[maxn];
	int dcc_cnt, skt, stak[maxn], iscut[maxn];
	bool ins[maxn];
	vector<int> dcc[maxn];
	int DCC();
	int dfs(int,int);
	
	int tot;
	int BlockForest();
	
	LL *ans, *cans, allw;
	LL sum[maxn<<1], pro[maxn<<1];
	bool vis[maxn];
	int solve(Graph*,LL*,LL*,LL);
	int calc(int,int);
};

int N,M;
Graph G;
Tarjan tar;
LL ans[maxn<<1], cans[maxn<<1], allw;

bool previs[maxn];
void precom(int,LL&);
int prevec[maxn], pcnt;
LL Pow(LL,LL,LL);

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
		for(int i=1; i<=N; i++) scanf("%lld", &G.pval[i]);
		for(int i=0, u, v; i<M; i++)
		{
			scanf("%d%d", &u, &v);
			G.adde(u,v); G.adde(v,u);
		}
		CLR(ans); CLR(cans); CLR(previs); allw=0;
		
		for(int i=1; i<=N; i++) if(!previs[i])
		{
			pcnt=0;
			LL getv=1;
			precom(i,getv);
			for(int j=0; j<pcnt; j++) cans[prevec[j]] = getv;
			allw = (allw+getv)%MOD;
		}
		tar.solve(&G,ans,cans,allw);
		LL res=0;
		for(int i=1; i<=N; i++) res = (res+i*ans[i]%MOD)%MOD;
		printf("%lld\n", (res+MOD)%MOD);
	}
	return 0;
}

void precom(int u,LL &getv)
{
	previs[u]=1;
	getv = getv*G.pval[u]%MOD;
	prevec[pcnt++] = u;
	for(int e=G.last[u],v; ~e; e=G.nxt[e]) 
	{
		v=G.v[e]; if(previs[v]) continue;
		precom(v,getv);
	}
}

int Tarjan::solve(Graph *g, LL _ans[], LL _cans[], LL _allw)
{
	G = g;
	ans = _ans; cans=_cans, allw = _allw;
	DCC();
	BlockForest();
	CLR(vis);
	for(int i=1; i<=dcc_cnt; i++) if(!vis[i]) calc(tot+i,-1);
	return 0;
}

int Tarjan::calc(int u, int f)
{
	if(u>tot) vis[u-tot]=1;
	sum[u]=0;
	pro[u]=G->pval[u];
	for(int e=G->last[u],v; ~e; e=G->nxt[e])
	{
		v=G->v[e];
		if(v==f) continue;
		calc(v, u);
		sum[u] = (sum[u]+pro[v])%MOD;
		pro[u] = (pro[u]*pro[v])%MOD;
	}
	if(u<=tot) ans[u] = ((allw-cans[u])%MOD + sum[u] + cans[u]*Pow(pro[u], MOD-2, MOD)%MOD) %MOD;
	return 0;
}

int Tarjan::BlockForest()
{
	tot=G->ndn;
	G->init(tot+dcc_cnt);
	for(int i=1, u; i<=dcc_cnt; i++)
	{
		u=tot+i;
		G->pval[u] = 1;
		for(int j=0; j<(int)dcc[i].size(); j++)
		{
			G->adde(u, dcc[i][j]);
			G->adde(dcc[i][j], u);
		}
		dcc[i].clear();
	}
	return tot;
}

int Tarjan::DCC()
{
	dfst=0; CLR(dfsn); CLR(lowv);
	dcc_cnt=0; skt=0; CLR(stak); CLR(ins);
	CLR(iscut);
	
	for(int i=1; i<=G->ndn; i++) if(!dfsn[i]) dfs(i,-1);

	return 0;
}

int Tarjan::dfs(int u,int f)
{
	lowv[u] = dfsn[u] = ++dfst;
	int child=0;
	for(int e=G->last[u], v; ~e; e=G->nxt[e])
	{
		v=G->v[e];
		if(v==f) continue;
		child++;
		if(!dfsn[v])
		{
			stak[++skt] = e>>1;
			dfs(v,u);
			lowv[u] = min(lowv[u], lowv[v]);
			if(lowv[v] >= dfsn[u])
			{
				iscut[u]=1;
				++dcc_cnt;
				do
				{
					int te = stak[skt]<<1;
					dcc[dcc_cnt].push_back(G->u[te]);
					dcc[dcc_cnt].push_back(G->v[te]);
				} while( (e>>1) != stak[skt--]);
				sort(dcc[dcc_cnt].begin(), dcc[dcc_cnt].end());
				dcc[dcc_cnt].erase( unique(dcc[dcc_cnt].begin(), dcc[dcc_cnt].end()), dcc[dcc_cnt].end());
			}
		}
		else if(dfsn[v] < dfsn[u])
		{
			stak[++skt] = e>>1;
			lowv[u] = min(lowv[u], dfsn[v]);
		}
	}
	if(f==-1 && child<=1) iscut[u]=0;
	if(f==-1 && child==0)
	{
		ans[u] = (allw-G->pval[u])%MOD;
	}
	return 0;
}

LL Pow(LL x, LL n, LL p)
{
	LL res=1;
	while(n)
	{
		if(n&1) res=res*x%p;
		x=x*x%p;
		n>>=1;
	}
	return res%p;
}

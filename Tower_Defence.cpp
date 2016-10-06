/*
HDU - 5886
给定一棵树，每条边都有一个权值
定义一条边的战术价值为割去这条边后
剩下的图中最长链的长度
求随机割掉一条边，战术价值的期望

题目要求乘以 N-1，所以直接把概率消掉了
所以只要求割去每条边后的最长链长度即可
这就转化为了一个树形dp
首先割去一条边 u->v 后，最长链可能在 v为根的子树中
这个简单地做一次树形dp就能得出
另外最长链还可能是在 u所在的联通块，这个就比较麻烦了
在 u联通块的最长链可能有几种情况
1. 最长链在 u之上且不经过 u
2. 最长链在 u之下且不经过 u，即最长链在 v的兄弟子树里
3. 最长链经过 u
其中最长链经过 u又分为两种情况
1. 最长链由 u之上到 u最长的一条链和 u之下到 u的最长的一条链连接而得
2. 最长链由 v的两个兄弟子树各出一条最长链在 u处连接而得
分类讨论所有情况，然后取 max即可
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

const int maxn=1e5+10;;
struct Graph
{
	int ndn, edn, last[maxn];
	int u[2*maxn], v[2*maxn], w[2*maxn], nxt[2*maxn];
	void init(int _n){ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u, int _v, int _w)
	{
		u[edn]=_u; v[edn]=_v; w[edn]=_w;
		nxt[edn]=last[_u];
		last[_u] = edn++;
	}
};

int N;
Graph G;
int dp[maxn][4], pos[maxn][4], dp2[maxn][3], pos2[maxn][3], res[maxn];
LL ans;

void add(int,int,int);
void add2(int,int,int);
int dfs0(int,int);
int dfs1(int,int,int,int);

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
		scanf("%d", &N);
		G.init(N);
		for(int i=1, u, v, w; i<N; i++)
		{
			scanf("%d%d%d", &u, &v, &w);
			G.adde(u,v,w); G.adde(v,u,w);
		}
		ans = 0;
		dfs0(1,0);
		dfs1(1,0,0,0);
		printf("%lld\n", ans);
	}
	return 0;
}

void add(int u, int v, int val)
{
	dp[u][3] = val; pos[u][3] = v;
	for(int i=2; i>=0; i--) if(dp[u][i] < dp[u][i+1])
	{
		swap(dp[u][i], dp[u][i+1]);
		swap(pos[u][i], pos[u][i+1]);
	}
}

void add2(int u, int v, int val)
{
	dp2[u][2] = val; pos2[u][2] = v;
	for(int i=1; i>=0; i--) if(dp2[u][i] < dp2[u][i+1])
	{
		swap(dp2[u][i], dp2[u][i+1]);
		swap(pos2[u][i], pos2[u][i+1]);
	}
}

int dfs0(int u, int f)
{
	MST(dp[u],-1); MST(pos[u],-1); 
	MST(dp2[u], -1); MST(pos2[u], -1);
	res[u] = 0;
	bool leaf=1;
	for(int e=G.last[u], v; ~e; e=G.nxt[e]) if((v=G.v[e])!=f)
	{
		leaf=0;
		add(u, v, dfs0(v,u)+G.w[e]);
		add2(u, v, res[v]);
		res[u] = max(res[u], res[v]);
	}
	if(leaf) add(u, u, 0);
	res[u] = max(res[u], max(dp[u][0], dp[u][0]+dp[u][1]));
	return dp[u][0];
}

int dfs1(int u, int f, int one, int two)
{
	for(int e=G.last[u], v; ~e; e=G.nxt[e]) if((v=G.v[e])!=f)
	{
		int tmax=0, tp=-1, tmax2=0, none, ntwo;
		for(int i=0; i<3 && ~dp[u][i]; i++)
		{
			if(pos[u][i] == v) continue;
			if(dp[u][i]>tmax) tmax = dp[u][i], tp=i;
		}
		none = max(tmax, one);
		ntwo = max(two, one+tmax);
		for(int i=0; i<3 && ~dp[u][i]; i++)
		{
			if(pos[u][i] == v || i==tp) continue;
			tmax2 = max(tmax2, dp[u][i]);
		}
		ntwo = max(ntwo, tmax + tmax2);
		if(pos[u][0] == v) ntwo = max(ntwo, dp2[u][1]);
		else ntwo = max(ntwo, dp2[u][0]);
		ans += max(ntwo, res[v]);
		dfs1(v, u, none+G.w[e], ntwo);
	}
	
}

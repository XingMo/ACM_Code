/*
Codeforces - 697D
给定一棵树，从1开始，按DFS的方式访问这棵树
每次从父亲节点随机访问儿子，问每个节点被访问到的时间的期望

设父亲节点的期望是 E，它有 n个儿子
其某个儿子是第 i次被访问到的，概率为 1/n
设有个兄弟在它之前被访问了，其概率为 (i-1)*(n-2)!/(n-1)!
他对期望的贡献为 (i-1)*(n-2)!/(n-1)!*size，size为它的子树的大小
这样所有兄弟的贡献和就为 (i-1)*(n-2)!/(n-1)!*S，S为兄弟子树的大小
所以排在 i位的期望即为 1/n*( (i-1)/(n-1)*S + E + 1 )
再把 i=1...n的期望加起来，即为 E + 1 + S/2

还可以换一个角度思考：
对于随机产生的一个数列，对于某个儿子，其兄弟在其前面的概率为 1/2
所以这个兄弟对期望的贡献为 size/2，所有兄弟加起来即为 S/2
所以期望即为 E + 1 + S/2
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

const int maxn=1e5+10;
const DBL eps=1e-6;
struct Graph
{
	int ndn,edn,last[maxn];
	int u[maxn], v[maxn], nxt[maxn];
	void init(int _n){ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u,int _v)
	{
		u[edn]=_u; v[edn]=_v;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};
DBL dp[maxn];
Graph G;
int size[maxn];
void dfs0(int);
void dfs1(int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int N;
	scanf("%d", &N);
	G.init(N);
	for(int i=2; i<=N; i++)
	{
		int x;
		scanf("%d", &x);
		G.adde(x,i);
	}
	CLR(dp);
	dp[1]=1;
	dfs0(1);
	dfs1(1);
	for(int i=1; i<=N; i++) printf("%.1f ", dp[i]);
	return 0;
}

void dfs0(int u)
{
	size[u]=1;
	for(int e=G.last[u]; ~e; e=G.nxt[e])
	{
		int v=G.v[e];
		dfs0(v);
		size[u]+=size[v];
	}
}

void dfs1(int u)
{
	for(int e=G.last[u]; ~e; e=G.nxt[e])
	{
		int v=G.v[e];
		dp[v] = dp[u] + 1 + (size[u]-size[v]-1)/2.0;
		dfs1(v);
	}
}

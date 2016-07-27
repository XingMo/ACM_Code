/*
HDU - 5727
有阴阳两种珠子交替地串成一个环，
其中某些阳与某些阴串在一起时，会变得黯淡
求一种合理的摆放方式，使得黯淡的阳最少
输出这个数量

首先暴力枚举所有阴的摆放方式
然后对于每一个阴的摆放方式，两个阴之间有空隙
阳可以从阴中插空放入，而对于每一个空和一个阳，
如果这个阳放入是合法的，就连一条边
最后再跑一遍二分图最大匹配，用 N减去匹配数就能得到最少黯淡数
有一个地方需要注意，就是枚举摆放方式的时候，可以先固定 1
这样枚举的复杂度就是 8!，不然会 TLE
时间复杂度 O((N-1)!*N^3)
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

const int maxn=50;
struct Graph
{
	int ndn, edn, last[2*maxn];
	int u[2*maxn*maxn], v[2*maxn*maxn], nxt[2*maxn*maxn];
	void init(int _n){ ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u, int _v)
	{
		u[edn]=_u; v[edn]=_v;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};

struct Hungarian
{
	Graph *G;
	int res, match[2*maxn];
	bool ins[2*maxn];
	int solve(Graph*);
	int dfs(int);
};

int N,M;
Graph G;
Hungarian hug;
int rule[maxn][maxn];
int permu[maxn];


int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		CLR(rule);
		for(int i=0; i<M; i++)
		{
			int x,y;
			scanf("%d%d", &x, &y);
			rule[x][y]=1;
		}
		for(int i=1; i<=N; i++) permu[i]=i;
		permu[N+1]=1;
		int ans=N;
		do
		{
			G.init(2*N);
			for(int i=1; i<=N; i++)
			{
				for(int j=1; j<=N; j++) if(!rule[j][permu[i]] && !rule[j][permu[i+1]])
				{
					G.adde(j,i+N); G.adde(i+N,j);
				}
			}
			int res=hug.solve(&G);
			ans=min(N-res, ans);
			if(ans==0) break;
		} while(next_permutation(permu+2, permu+N+1));
		printf("%d\n", ans);
	}
	return 0;
}

int Hungarian::solve(Graph *g)
{
	G=g;
	res=0;
	CLR(match);
	for(int i=1; i<=G->ndn/2; i++)
	{
		if(!match[i])
		{
			CLR(ins);
			if(dfs(i)) res++;
		}
	}
	return res;
}

int Hungarian::dfs(int u)
{
	for(int e=G->last[u]; ~e; e=G->nxt[e])
	{
		int v=G->v[e];
		if(ins[v]) continue;
		ins[v]=1;
		if(!match[v] || dfs(match[v]))
		{
			match[u]=v;
			match[v]=u;
			return 1;
		}
	}
	return 0;
}

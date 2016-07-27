/*
HDU - 5413
求问一个有向无环图内有多少个冗余边
冗余边的定义为，对于一条边 (u,v)
如果删去这条边，u依旧能到v，则此边是冗余边

这道题看起来不可做的样子，看了下题解是暴力
对于每个点记录一下有哪些点可以到达这个点
由于是有向无环图，所以可以进行一个拓扑排序来解决

求完之后，对于每个点，将其前驱按拓扑序排序
从前驱拓扑序大的开始处理，如果处理到一条边
发现其前驱在这条边之前已经可达此点，说明这是冗余边

那么问题就来了，如何求这个可达矩阵而不超时呢
关键就是使用bitset

bitset的第 i位表示第 i个点是否能到达此点
这样一来，看似时间复杂度是 O(N^2)，空间复杂度也是 O(N^2)
但实际上 bitset把一个字节当作了 8位，所以复杂度可以降一个级别
所以两个复杂度都是 1e7左右，刚好能卡过
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
#define Sqr(a) ((a)*(a))

const int maxn=2e4+10, maxm=1e5+10;
struct Graph
{
	int ndn, edn, last[maxn];
	int u[maxm], v[maxm], nxt[maxm];
	int deg[maxn];
	void init(int _n)
	{
		ndn=_n;
		edn=0;
		MST(last,-1);
		CLR(deg);
	}
	void adde(int _u, int _v)
	{
		u[edn]=_u; v[edn]=_v;
		deg[_v]++;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};

int N,M;
Graph G;
bitset<maxn> rech[maxn];
vector<int> invG[maxn];
int tim,topTime[maxn];
int que[5*maxn];

bool cmp(int x, int y){return topTime[x] > topTime[y];}

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int T;
	scanf("%d",&T);
	for(int ck=1; ck<=T; ck++)
	{
		scanf("%d%d", &N, &M);
		G.init(N);
		tim=0; CLR(topTime);
		for(int i=0; i<N; i++) invG[i].clear();
		for(int i=0; i<N; i++) {rech[i].reset(); rech[i][i]=true;}
		
		for(int i=0; i<M; i++)
		{
			int u,v;
			scanf("%d%d", &u, &v);
			G.adde(u-1,v-1);
		}
		int ans=0;
		int head=0,tail=0;
		for(int i=0; i<N; i++) if(!G.deg[i]) que[tail++]=i;
		while(head<tail)
		{
			int u=que[head++];
			topTime[u]=++tim;
			for(int e=G.last[u]; ~e; e=G.nxt[e])
			{
				int v=G.v[e];
				invG[v].push_back(u);
				G.deg[v]--;
				if(!G.deg[v]) que[tail++]=v;
			}
		}
		for(int np=0; np<tail; np++)
		{
			int u=que[np];
			sort(invG[u].begin(), invG[u].end(), cmp);
			for(int i=0; i<(int)invG[u].size(); i++)
			{
				int v=invG[u][i];
				if(rech[u][v]) ans++;
				rech[u] |= rech[v];
			}
		}
		printf("%d\n", ans);		
	}
	return 0;
}


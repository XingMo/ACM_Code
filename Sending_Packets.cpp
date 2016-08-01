/*
LightOJ - 1321
给定一张无向图，每条边都有一个通过的概率
如果无法通过，那么就要回到起点重新出发
从起点到终点的时间固定为 K，如果成功到达，
又需要额外花费 K的时间，问走 S次的最小期望时间

首先可以跑一遍SPFA求出一次通过的最大概率 p
设最小期望时间为 E，E = p*2K + (1-p)*(E+2K)
所以答案即为 2*K*S/p

要注意 S有 1e9啊！所以输出的时候要显式转化为double
否则就爆 int了
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
#define PCUT puts("----------")

const int maxn=100+10,maxm=1e4+10;
struct Graph
{
	int ndn,edn,last[maxn];
	int u[2*maxm], v[2*maxm], w[2*maxm], nxt[2*maxm];
	void init(int _n) {ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u, int _v, int _w)
	{
		u[edn]=_u; v[edn]=_v; w[edn]=_w;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};
int N, M, S, K;
Graph G;
DBL dp[maxn];
bool inq[maxn];

DBL SPFA(int,int);

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
		scanf("%d%d%d%d", &N, &M, &S, &K);
		G.init(N);
		for(int i=0,u,v,w; i<M; i++)
		{
			scanf("%d%d%d", &u, &v, &w);
			G.adde(u,v,w); G.adde(v,u,w);
		}
		DBL p = SPFA(0, N-1);
		printf("Case %d: %.7f\n", ck, (DBL)2*K*S/p);
	}
	return 0;
}

DBL SPFA(int sta, int end)
{
	queue<int> que;
	CLR(inq); CLR(dp);
	inq[0]=1;
	dp[0]=1;
	que.push(0);
	while(que.size())
	{
		int u=que.front(); que.pop();
		for(int e=G.last[u],v,w; ~e; e=G.nxt[e])
		{
			v=G.v[e]; w=G.w[e];
			if(dp[u]*w*0.01 > dp[v])
			{
				dp[v] = dp[u]*w*0.01;
				if(!inq[v])
				{
					inq[v]=1;
					que.push(v);
				}
			}
		}
		inq[u]=0;
	}
	return dp[end];
}

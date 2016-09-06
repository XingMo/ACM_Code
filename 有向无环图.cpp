/*
CSU - 1803 （湖南省赛16）
给定一个 n个点的有向无环图，
定义 count(u,v)为 u到 v的路径方案数
求 \sum_{i=1}^n \sum_{j=1}^n count(i,j)*a_i*b_j
其中 a_i与 b_j为给定的数列，并且 count(u,u)=0

先考虑 j枚举到某一个点，其对答案的贡献
首先它只与所有能到 j的点 i有关
虽然不能枚举所有这样的 i，但是注意到 count(i,j)为 i到 j的路径方案数
那么对于在 j之前的每一个 i，它能有多少种方法到 j，a_i就会被统计多少次
最后再将这个和乘以 b_j，就是点 j对答案的贡献

所以按拓扑序枚举每一个 j，并对其维护一个 a的权值和，
为其所有前继的权值加上前继的a值的和，就能求出所需当前点的权值
最后乘以 b_j，累加到答案即可，时间复杂度 O(n)
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

const int maxn=1e5+10, MOD=1e9+7;
struct Graph
{
	int ndn,edn,last[maxn],ind[maxn];
	int u[maxn], v[maxn], nxt[maxn];
	void init(int _n){ndn=_n; edn=0; MST(last,-1); CLR(ind);}
	void adde(int _u, int _v)
	{
		u[edn]=_u; v[edn]=_v;
		nxt[edn]=last[_u];
		last[_u]=edn++;
		ind[_v]++;
	}
};

int N,M,A[maxn],B[maxn],V[maxn];
Graph G;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		CLR(V);
		G.init(N);
		for(int i=1; i<=N; i++) scanf("%d%d", &A[i], &B[i]);
		for(int i=1,u,v; i<=M; i++)
		{
			scanf("%d%d", &u, &v);
			G.adde(u,v);
		}
		int ans=0;
		queue<int> que;
		for(int i=1; i<=N; i++) if(!G.ind[i]) que.push(i);
		while(que.size())
		{
			int u=que.front(); que.pop();
			ans = ((LL)ans + (LL)V[u]*B[u])%MOD;
			for(int e=G.last[u],v; ~e; e=G.nxt[e])
			{
				v=G.v[e];
				V[v] = ((LL)V[v] + (LL)V[u] + A[u]) %MOD;
				G.ind[v]--;
				if(!G.ind[v]) que.push(v);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}


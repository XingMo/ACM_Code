/*
Codeforces - 272E
有 N匹马，其中有一些马是敌对关系，要求将整个图分为两部分，
每部分里的任意一匹马在同一部分中的敌人不超过一个
其中任意一匹马的敌人不超过三个，无解输出 -1

首先分析一匹马的至多三个敌人的所有状态，发现不可能无解
直到了这点以后就可以随便搞了
首先将所有点都染成 0，然后找到其中不满足条件的丢到队列里
然后不断地更改不满足条件的颜色，再将其影响到的点丢到队列里
由于保证有解，所以很快就能构造出一组合法解
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

const int maxn=3e5+10, maxm=6e5+10;
struct Graph
{
	int ndn, edn, last[maxn];
	int u[maxm], v[maxm], nxt[maxm];
	void init(int _n) {ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u, int _v)
	{
		u[edn]=_u; v[edn]=_v;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};

int N,M;
Graph G;
int col[maxn];
bool inq[maxn];
queue<int> que;

int Cnt(int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		G.init(N);
		CLR(col); CLR(inq);
		for(int i=0,u,v; i<M; i++)
		{
			scanf("%d%d", &u, &v);
			G.adde(u,v); G.adde(v,u);
		}
		while(que.size()) que.pop();
		for(int i=1; i<=N; i++) if(!Cnt(i)) que.push(i);
		while(que.size())
		{
			int u=que.front(); que.pop();
			if(Cnt(u) != col[u]) continue;
			col[u] ^= 1;
			for(int e=G.last[u]; ~e; e=G.nxt[e]) if(!inq[G.v[e]]) que.push(G.v[e]);
		}
		for(int i=1; i<=N; i++) putchar(col[i]+'0'); puts("");
	}
	return 0;
}

int Cnt(int u)
{
	int cnt0=0, cnt1=0;
	for(int e=G.last[u],v; ~e; e=G.nxt[e]) if(col[v=G.v[e]]) cnt1++; else cnt0++;
	return cnt0>cnt1?0:1;
}

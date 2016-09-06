/*
Codeforces - 27D
给定一个环，要求添加若干条路
这些路要么在环的内部，要么在外部
问是否有一种添加方案，
使得所有新加的路除了端点以外的地方不相交

首先显然可以将环剖成一条链
然后不相交的路就转化为了线段覆盖问题
然后 O(M^2)预处理出所有可能相交的线段
然后跑二分图染色即可
判断线段相交可能写起来有点蛋疼，其他都还好
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

const int maxn=100+10, maxe=maxn*maxn*2;
struct Graph
{
	int ndn, edn, last[maxn];
	int u[maxe], v[maxe], nxt[maxe];
	void init(int _n) {ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u, int _v)
	{
		u[edn]=_u; v[edn]=_v;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};
int N,M;
Pii in[maxn];
int col[maxn];
char ans[maxn];
Graph G;

bool ins(int,int);
bool color(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		G.init(M);
		for(int i=1,l,r; i<=M; i++)
		{
			scanf("%d%d", &l, &r);
			in[i].first = min(l, r);
			in[i].second = max(l, r);
		}
		for(int i=1; i<=M; i++) for(int j=1; j<=M; j++) if(i!=j && ins(i,j))
			G.adde(i,j);
		MST(col,-1);
		bool ok=1;
		for(int i=1; i<=M; i++) if(col[i]==-1)
		{
			if(!color(i,0)) {ok=0; break;}
		}
		for(int i=0; i<M; i++) ans[i] = col[i+1]?'i':'o';
		ans[M] = 0;
		if(ok) puts(ans);
		else puts("Impossible");
	}
	return 0;
}

bool color(int u, int c)
{
	col[u] = c;
	for(int e=G.last[u],v; ~e; e=G.nxt[e])
	{
		v=G.v[e];
		if(~col[v] && col[v] != 1-c) return 0;
		if(col[v]==-1 && !color(v, 1-c)) return 0;
	}
	return 1;
}

bool ins(int x, int y)
{
	int l1,r1,l2,r2;
	l1 = in[x].first; r1 = in[x].second;
	l2 = in[y].first; r2 = in[y].second;
	int in0=0, in1=0;
	if(l1<l2 && l2<r1) in0=1;
	else if(l2<l1 || r1<l2) in0=-1;
	if(l1<r2 && r2<r1) in1=1;
	else if(r2<l1 || r1<r2)in1=-1;
	if(in0*in1==-1) return 1;
	else return 0;
}

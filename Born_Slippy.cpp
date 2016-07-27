/*
HDU - 5735
给定一棵树，要求从这个点到它祖先的链上不要求连续地选若干个点
使得序列中相邻点权的位运算和加上此点点权最大，设这个值为 f[i]
输出 \sum_{i=1}^N i*f[i]

赛上没看这题……赛后一看题解，发现是个暴力，所以果断写了一发
拿与运算举例，首先点权是固定的，所以只要求位运算和最大就好了
设 dp[i] = max(dp[j] + w_i & w_j)
比较暴力的做法是树形DP求，然后取max的时候暴力枚举所有祖先
但是这样复杂度有 2^32次方，肯定会 T

但是发现其实不需要枚举祖先，只需要把最值存下来即可
首先可以把点权拆成高 8位和低 8位
设定数组 tmax[high][low]表示前面所有高 8位为 high的祖先中，
dp[u] + low & low' 的最大值，其中low'即为取到最大的 u的底 8位

这样一来，在计算某个节点的时候，只需枚举高位 0~1<<8，配合当前节点的 low
就能求出当前节点的 dp值，有了 dp值，更新这个数组也很方便。
这样一来，复杂度就降到了 2^24次方

有几个需要注意的：
1. 根节点没有祖先，所以 dp值为 0
2. dp值以及tmax数组要开 unsign int，否则可能会溢出
3. 更新数组之前，要先将要更新的那一维备份，遍历完子树后要还原
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
typedef unsigned int uint;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define SQR(a) ((a)*(a))
#define PCUT puts("----------")

const int maxn = (1<<16)+10, maxs=(1<<8)+10;
const int AND=0, XOR=1, OR=2, MOD=1e9+7;
char _opt;
inline uint opt(uint x, uint y)
{
	if(_opt==AND) return x&y;
	if(_opt==XOR) return x^y;
	if(_opt==OR ) return x|y;
}
struct Memory
{
	uint siz, pool[2*maxn][maxs];
	void init(){siz=0;}
	uint* alloc(){return pool[siz++];}
};

struct Graph
{
	int ndn, edn, last[maxn];
	int u[maxn], v[maxn], nxt[maxn];
	int pval[maxn];
	void init(int _n){ ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u, int _v)
	{
		u[edn]=_u; v[edn]=_v;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};

int N;
Graph G;
Memory mem;
uint dp[maxn], tmax[maxs][maxs];

void solve(int);

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
		char str[10];
		scanf("%d %s", &N, str);
		if(!strcmp(str,"AND")) _opt=AND;
		if(!strcmp(str,"XOR")) _opt=XOR;
		if(!strcmp(str,"OR"))  _opt=OR;
		G.init(N); mem.init();
		CLR(dp); MST(tmax,-1);
		
		for(int i=1; i<=N; i++) scanf("%d", &G.pval[i]);
		for(int i=2,f; i<=N; i++) scanf("%d", &f), G.adde(f,i);
		solve(1);
		LL ans=0;
		for(int i=1; i<=N; i++) ans = (ans + i*((LL)dp[i]+G.pval[i]))%MOD;
		printf("%lld\n", ans);
	}
	return 0;
}

void solve(int u)
{
	int high=G.pval[u]>>8, low=G.pval[u]&255;
	uint* backup = mem.alloc();
	memcpy(backup, tmax[high], sizeof(uint)*maxs);
	for(int i=0; i<256; i++) if(tmax[high][i]==(uint)-1 || dp[u] + opt(i,low)>tmax[high][i])
		tmax[high][i] = dp[u] + opt(i,low);
	
	for(int e=G.last[u], v; ~e; e=G.nxt[e])
	{
		v=G.v[e];
		high=G.pval[v]>>8, low=G.pval[v]&255;
		for(int i=0; i<256; i++) if(~tmax[i][low]) dp[v] = max(dp[v], tmax[i][low] + (opt(i,high)<<8));
		solve(v);
	}
	
	high=G.pval[u]>>8;
	memcpy(tmax[high], backup, sizeof(uint)*maxs);
}


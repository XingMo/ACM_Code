/*
HDU - 5406
一棵树上有若干个苹果，每个苹果有一个高度值和美味值
两个人一棵树上从高到底摘苹果，摘到苹果后，可以选择给任意一个人吃，或者扔掉
但是每个人吃的苹果的美味值必须是非严格递增的
问两个人最多可以吃多少个苹果

首先按高度先排序，问题就转化为求两个 LIS，使得他们的长度和最大

有一个费用流做法，从前向后 D小的向 D大连一条流量为 1的边
每条边费用为 1，然后跑一个流量为 2的费用流，求得最大费用

但是我不会费用流，所以这是一个 DP做法（双线程DP）
dp[i][j]表示两个数列最后一个数分别是 i,j
由于具有对称性，dp[i][j] = dp[j][i]
从前向后枚举每一个苹果，
转移方程为 dp[d][1...N] = max(dp[1...d][1...N])
由于具有对称性，所以更新完 dp[i][j]，还要更新一下 dp[j][i]
这样转移是 O(N^3)的，但是可以用树状数组优化掉枚举 1...d的过程
这样一来，时间复杂度就为 O(N^2*logn)
注意树状数组不要边更新边询问，否则前面的更新会影响后面的询问
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

const int maxn=1e3+10;
struct data
{
	int h,d;
	bool operator < (const data &v) const
	{
		if(h != v.h) return h > v.h;
		else return d < v.d;
	}
};
struct Discrete
{
	int ais[maxn], siz;
	void init()
	{
		sort(ais, ais+siz);
		siz = unique(ais, ais+siz)-ais;
	}
	void add(int _n){ais[siz++]=_n;}
	int id(int _n){return lower_bound(ais, ais+siz, _n)-ais + 1;}
};
struct BIT
{
	int bit[maxn], siz;
	void init(int _n){ siz=_n; CLR(bit);}
	void add(int p, int x){ for(int i=p; i<=siz; i+=i&-i) bit[i] = max(bit[i], x);}
	int sum(int p){ int res=0; for(int i=p; i>0; i-=i&-i) res = max(bit[i], res); return res;}
};
int N;
data A[maxn];
BIT dp[maxn];
int val[maxn];
Discrete D;
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
		for(int i=0; i<=N; i++) dp[i].init(N);
		D.siz=0;
		for(int i=0; i<N; i++)
		{
			scanf("%d%d", &A[i].h, &A[i].d);
			D.add(A[i].d);
		}
		D.init();
		sort(A, A+N);
		for(int np=0; np<N; np++)
		{
			int d=D.id(A[np].d);
			for(int i=1; i<=N; i++) val[i]=dp[i].sum(d);
			for(int i=1; i<=N; i++)
			{
				dp[i].add(d, val[i]+1);
				dp[d].add(i, val[i]+1);
			}
		}
		int ans=0;
		for(int i=1; i<=N; i++) ans=max(ans, dp[i].sum(N));
		printf("%d\n", ans);
	}
	return 0;
}



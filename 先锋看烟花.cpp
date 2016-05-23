/*
SCU - 4513
一条路上有 N个房子，一共有 M个烟花
在 t_i时刻，第 a_i个房子会放一个价值为 b_i的烟花
对先锋会产生 b_i-abs(a_i-cur)的幸福度，幸福度可以为负数
先锋每个单位时间最多可以移动 D的距离
问所有烟花放完之后，先锋的幸福度最大为多少

首先朴素的想法是暴力模拟这个过程
用 dp[i][j]表示第 i秒，处于 j位置的先锋能获得的最大幸福度
在没有烟花的时刻，先锋可以左右移动 D的距离
所以向左右走2*D，以最优答案来更新周围的值

经过模拟可以发现，在没有烟花的时候
某点的答案会其实就等于某段区间内的最大值
并且这段区间随着时间地增长会变大

所以对放烟花的时间排序，在放烟花的时刻，扫一遍数组更新答案
在没放烟花的空闲时刻，算出到下一个烟花绽放时刻之前，
从任意一点出发，先锋能移动的最大范围
用稀疏表求出此范围内的最优答案，然后再暴力扫一遍数组更新答案

总的复杂度 O(NMlog(N))
如果使用单调队列维护最大值，还可以优化到 O(NM)
*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <cctype>
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) (a*a)

const int maxn=15e4+10;
const LL INF=0x3f3f3f3f3f3f3f3fLL;
struct SparseTable
{
	LL **spas,tlog;
	SparseTable(LL*,int);
	~SparseTable();
	LL query(int,int);
};
int N,M,D;
LL res[maxn];
LL dp[maxn];
LL ai[500],bi[500],ti[500];

void pause(const char *str)
{
	fflush(stdin);
	puts(str);
	getchar();
}

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
		scanf("%d%d%d", &N, &M, &D);
		for(int i=1; i<=M; i++) 
		{
			scanf("%lld%lld%lld", &ai[i], &bi[i], &ti[i]);
			ai[i]--;
		}
		LL ans=-INF;
		CLR(res);
		SparseTable *st=new SparseTable(res,N);
		int np=1;
		while(np<=M)
		{
			LL nt=ti[np];
			LL dist=(LL)(ti[np]-ti[np-1])*D;		
			for(int j=0; j<N; j++)
			{
				LL l=max((LL)0,(LL)j-dist), r=min((LL)N-1,(LL)j+dist);
				res[j]=st->query(l,r);
			}
			while(ti[np]==nt&&np<=M)
			{
				for(int j=0; j<N; j++) res[j]+=bi[np]-abs(ai[np]-j);
				np++;
			}
			st->~SparseTable();
			st=new SparseTable(res,N);
		}
		st->~SparseTable();
		for(int i=0; i<N; i++) ans=max(ans, res[i]);
		printf("%lld\n", ans);
	}
	return 0;
}

SparseTable::SparseTable(LL arry[],int len)
{
	tlog=log2(len);
	spas=new LL*[tlog+2];
	for(int i=0; i<=tlog; i++) spas[i]=new LL[len-(1<<i)+1];
	for(int i=0; i<len; i++) spas[0][i]=arry[i];

	for(int j=1; j<=tlog; j++)
	{
		int tlen=1<<j-1,nlim=len-(1<<j)+1;
		for(int i=0; i<nlim; i++)
		{
			spas[j][i]=max(spas[j-1][i],spas[j-1][i+tlen]);
		}
	}
}

SparseTable::~SparseTable()
{
	for(int i=0; i<=tlog; i++) delete[] spas[i];
	delete[] spas;
}

LL SparseTable::query(int l, int r)
{
	int flr=log2(r-l+1);
	int nlen=1<<flr;
	return max(spas[flr][l],spas[flr][r-nlen+1]);
}


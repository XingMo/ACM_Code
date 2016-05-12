/*
HDU - 3507
给定若干个词，按顺序打印一篇文章
如果其中有些词是连续打印的
要付出 \sigma_{i=1}^{k}{C_i^2} + M 的代价
求付出的最小代价是多少

斜率优化第一题。
很容易得出递推式
dp[i] = min(dp[j] + (psum[i]-psum[j])^2)
然后这个递推转移是 O(N^2)的，所以要用到所谓到斜率优化
设存在 k<j<i使得 dp[k]+(psum[i]-psum[k])^2 >= dp[j]+(psum[i]-psum[j])^2
那么显然我们可以抛弃所有这样的 k，就直接从 dp[j]转移就好了
整理上式，分离 j 和 k，可以得到
{(dp[j]+psum[j]^2)-(dp[k]+psum[k]^2)} / {2*(psum[j]-psum[k])} <= psum[i]
其中把 dp[j]+psum[j]^2看作 y_j，把 psum[j]看作 x_j，则上式转化为有几何意义的斜率
而其中 psum[i]是单调递增的，所以斜率也是单调递增的
所以斜率优化实际上是在沿着平面上一个下凹的凸包进行的
用一个单调队列维护一下最大斜率，问题就解决了
时间复杂度 O(N)
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
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) (a*a)

const int maxn=5e5+10;
int N,M;
int inpt[maxn];
int psum[maxn];
int dp[maxn];
int que[maxn];

int Up(int,int);
int Down(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		for(int i=1; i<=N; i++)
		{
			scanf("%d", &inpt[i]);
			psum[i]=psum[i-1]+inpt[i];
		}
		int qhead=0,qtail=1;
		que[0]=0;
		for(int i=1; i<=N; i++)
		{
			while(qhead+1<qtail && Up(que[qhead+1], que[qhead]) <= psum[i]*Down(que[qhead+1], que[qhead]))
				qhead++;
			int j=que[qhead];
			dp[i]=dp[j] + Sqr((psum[i]-psum[j])) + M;
			while(qhead+1<qtail && 
			Up(i, que[qtail-1])*Down(que[qtail-1], que[qtail-2]) <= Up(que[qtail-1], que[qtail-2])*Down(i, que[qtail-1]))
				qtail--;
			que[qtail++]=i;
		}
		printf("%d\n", dp[N]);
	}
	return 0;
}

int Up(int j, int k)
{
	return dp[j]+Sqr(psum[j])-dp[k]-Sqr(psum[k]);
}

int Down(int j, int k)
{
	return 2*(psum[j]-psum[k]);
}

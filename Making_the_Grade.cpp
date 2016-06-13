/*
POJ - 3666
给定一个初始序列，增减其中某些项
使得最终序列非严格递增或非严格递减
求增减量和最小为多少

这题 A最多有 1e9，第一反应要先离散化之
这样一来，A最多就只有 2000了
然后就可以 DP了
设 dp[i][j]为前 i个数非严格递增，第 i个数修改为 j的最小代价
转移方程为 dp[i][j] = min(dp[i-1][0..j])
由于只会从 i-1转移，所以可以滚动数组
其次要求 0..j中的最小值，而第 j项并不重要
所以 dp计算完之后修改为前缀最小即可
这样就可以求出使序列非严格递增的最小代价
非严格递减的只需把整个序列翻转，再求一次即可
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

const int maxn=2e3+10;
int N;
int A[maxn],D[maxn];
LL dp[2][maxn];

LL solve();

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		for(int i=0; i<N; i++)
		{
			scanf("%d", &A[i]);
			D[i]=A[i];
		}
		sort(D, D+N);
		LL ans=solve();
		reverse(A, A+N);
		ans = min(ans, solve());
		printf("%lld\n", ans);
	}
	return 0;
}

LL solve()
{
	CLR(dp);
	for(int i=0; i<N; i++)
	{
		dp[0][i] = abs(A[0]-D[i]);
		if(i>0) dp[0][i] = min(dp[0][i], dp[0][i-1]);
	}
	for(int i=1; i<N; i++)
	{
		int cur=i&1, las=(i-1)&1;
		for(int j=0; j<N; j++)
		{
			dp[cur][j] = dp[las][j] + abs(A[i]-D[j]);
			if(j>0) dp[cur][j] = min(dp[cur][j], dp[cur][j-1]);
		}
	}
	LL ans=dp[(N-1)&1][0];
	for(int i=1; i<N; i++) ans = min(ans, dp[(N-1)&1][i]);
	return ans;
}

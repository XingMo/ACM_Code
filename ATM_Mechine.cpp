/*
HDU - 5781
一个人去取钱，它不知道卡里有多少钱
但知道钱的上限是多少
每次他都要取一定的钱，如果能取到，他马上就得到钱
如果取的钱超过了余额，他就会被警告
求在最优策略下，取的钱上限是 K，警告次数不超过 W
取钱次数期望最小是多少

好题！
首先最优策略啥的，大概就是二分之类的
但又不一定是二分，但可由此推出，被警告的次数不会超过 logK
所以 W = min(logK, W)，这样一来 W就缩小了
设 dp[w][k]为当前警告次数剩余 w，钱上限为 k的最小期望
然后枚举当前取的钱数进行转移，取结果中最小的那一个，即为最优
与 UESTC - 1051 Eggs broken 有异曲同工之处
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

const int maxn=2e3+10;
const DBL eps=1e-8;
int K,W;
DBL dp[15][maxn];

DBL DP(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	MST(dp,0xc0);
	while(~scanf("%d%d", &K, &W))
	{
		W = min(14,W);
		printf("%7f\n", DP(W,K));
	}
	return 0;
}

DBL DP(int w, int k)
{
	if(w<0) return 1e9;
	if(k==0) return dp[w][k] = 0.0;
	if(dp[w][k] > eps) return dp[w][k];
	dp[w][k] = 1e9;
	for(int i=1; i<=k; i++)
	{
		dp[w][k] = min(dp[w][k], (DBL)(k-i+1)/(k+1)*DP(w,k-i) + (DBL)i/(k+1)*DP(w-1,i-1) + 1);
	}
	return dp[w][k];
}

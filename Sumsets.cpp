/*
PKU - 2229
将一个数分为若干个 2的次幂之和，问有几种方案

dp[i][0] 表示组成 i的没有 1的方案数
dp[i][1] 表示组成 i的有一个 1的方案数
dp[i][2] 表示组成 i的有 1的方案数

当 i为奇数时：
dp[i][0]=0，因为至少需要 1个 1才能组成奇数
dp[i][1]=dp[i-1][0]，i-1无 1的构成情况，再加上一个 1得到 i
dp[i][2]=dp[i-1][0]+dp[i-1][2]，前一个数的所有情况，加上一个 1得到 i
当 i为偶数时：
dp[i][0]=dp[i/2][0]+dp[i/2][1]，i/2的所有方案，乘以 2得到 i，均不含 1
dp[i][1]=0，因为 i为偶数，所以不可能有单独的一个 1
dp[i][2]=dp[i-1][0]+dp[i-1][2]，前一个数的所有情况，加上一个 1得到 i

最后答案为 dp[N][0]+dp[N][2]
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
#define Sqr(a) ((a)*(a))

const LL MOD=1e9;
const int maxn=1e6+10;
int N;
LL dp[maxn][3];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		CLR(dp);
		dp[1][0]=0;
		dp[1][1] = dp[1][2] = 1;
		for(int i=2; i<=N; i++)
		{
			if(i&1)
			{
				dp[i][0] = 0;
				dp[i][1] = dp[i-1][0];
				dp[i][2] = dp[i-1][0]+dp[i-1][2];
			}
			else
			{
				dp[i][0] = dp[i/2][0]+dp[i/2][2];
				dp[i][1] = 0;
				dp[i][2] = dp[i-1][0]+dp[i-1][2];
			}
			dp[i][0]%=MOD;
			dp[i][1]%=MOD;
			dp[i][2]%=MOD;
		}
		printf("%lld\n", (dp[N][0]+dp[N][2])%MOD);
	}	
	return 0;
}


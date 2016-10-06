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

const int MOD=1e9+7;
int N,A,B;
int dp[2][610];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d%d", &N, &A, &B))
	{
		CLR(dp);
		dp[0][0] = 1, dp[0][A+1] = 1;
		for(int i=1; i<=N; i++)
		{
			int cur=i&1, las=(i-1)&1;
			CLR(dp[cur]);
			for(int j=1; j<=A; j++)
			{
				dp[cur][j] = (dp[cur][j] + dp[las][j-1])%MOD;
				dp[cur][A+1] = (dp[cur][A+1] + dp[cur][j])%MOD;
			}
			for(int j=1; j<=B; j++)
			{
				dp[cur][A+1+j] = (dp[cur][A+1+j] + dp[las][A+1+j-1]) %MOD;
				dp[cur][0] = (dp[cur][0] + dp[cur][A+1+j])%MOD;
			}
		}
		printf("%d\n", (dp[N&1][0] + dp[N&1][A+1])%MOD);
	}
	return 0;
}


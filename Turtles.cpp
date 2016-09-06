/*
Codeforces - 348E
网格不相交路径计数
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

const int maxn=3e3+10, MOD=1e9+7;
int N, M, dp[2][maxn][maxn];
char Map[maxn][maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		CLR(dp);
		dp[0][1][2]=1;
		dp[1][2][1]=1;
		for(int i=1; i<=N; i++) scanf("%s", Map[i]+1);
		for(int i=1; i<=N; i++)
		{
			for(int j=1; j<=M; j++)
			{
				dp[0][i][j] += (dp[0][i-1][j] + dp[0][i][j-1]) %MOD;
				dp[1][i][j] += (dp[1][i-1][j] + dp[1][i][j-1]) %MOD;
				if(Map[i][j]=='#') dp[0][i][j] = dp[1][i][j] = 0;
			}
		}
		printf("%d\n", int((((LL)dp[0][N-1][M]*dp[1][N][M-1]%MOD - (LL)dp[0][N][M-1]*dp[1][N-1][M])%MOD + MOD)%MOD));
	}
	return 0;
}


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
#include <cassert>
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

int N, dp[2][310][310];
int Map[310][310];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		CLR(Map);
		for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) scanf("%d", &Map[i][j]);
		MST(dp,0xc0);
		dp[1][1][1] = Map[1][1];
		for(int i=2; i<2*N; i++)
		{
			int cur=i&1, las=(i-1)&1;
			MST(dp[cur],0xc0);
			int r1,c1,r2,c2;
			for(r1=1; r1<=N; r1++)
			{
				c1 = i-(r1-1);
				if(c1>N) continue;
				for(r2=1; r2<=N; r2++)
				{
					c2 = i-(r2-1);
					if(c2>N) continue;
					dp[cur][r1][r2] = max(dp[cur][r1][r2], dp[las][r1][r2]);
					dp[cur][r1][r2] = max(dp[cur][r1][r2], dp[las][r1][r2-1]);
					dp[cur][r1][r2] = max(dp[cur][r1][r2], dp[las][r1-1][r2]);
					dp[cur][r1][r2] = max(dp[cur][r1][r2], dp[las][r1-1][r2-1]);
					dp[cur][r1][r2] += Map[r1][c1] + Map[r2][c2];
					if(r1==r2) dp[cur][r1][r2] -= Map[r1][c1];
				}
			}
		}
		printf("%d\n", dp[(2*N-1)&1][N][N]);
	}
	return 0;
}


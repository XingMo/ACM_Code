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
int N,M;
int inpt[maxn];
int dp[2][2][50];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		for(int i=1; i<=N; i++) scanf("%d", &inpt[i]);
		MST(dp,-1);
		dp[0][0][0]=0;
		for(int i=1; i<=N; i++)
		{
			int cur=i&1, las=(i-1)&1;
			MST(dp[cur],-1);
			for(int j=0; j<=M; j++)
			{
				dp[cur][0][j] = max(dp[cur][0][j], dp[las][0][j]);
				if(j<M) dp[cur][0][j+1] = max(dp[cur][0][j+1], dp[las][1][j]);
				
				dp[cur][1][j] = max(dp[cur][1][j], dp[las][1][j]);
				if(j<M) dp[cur][1][j+1] = max(dp[cur][1][j+1], dp[las][0][j]);
			}
			for(int j=0; j<=M; j++)
			{
				if(~dp[cur][0][j] && inpt[i]==1) dp[cur][0][j]++;
				if(~dp[cur][1][j] && inpt[i]==2) dp[cur][1][j]++;
			}
		}
		int ans=0;
		for(int i=0; i<=M; i++) ans=max(ans, max(dp[N&1][0][i], dp[N&1][1][i]));
		printf("%d\n", ans);
	}
	return 0;
}


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

const int maxv=1e5+10;
int N,K;
int W[110],M[110];
int dp[2][maxv];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif

	while(~scanf("%d%d", &N, &K)&&N)
	{
		MST(dp,-1);
		dp[0][0]=0;
		for(int i=1; i<=N; i++) scanf("%d", &W[i]);
		for(int i=1; i<=N; i++) scanf("%d", &M[i]);
		for(int i=1; i<=N; i++)
		{
			int cur=i&1,las=(i-1)&1;
			MST(dp[cur],-1);
			for(int j=0; j<maxv; j++) if(~dp[las][j]) dp[cur][j]=M[i];
			
			for(int j=0; j<maxv-W[i]; j++)
			{
				if(dp[cur][j]>0)
				{
					dp[cur][j+W[i]]=max(dp[cur][j+W[i]], dp[cur][j]-1);
				}
			}
		}
		int ans=0;
		for(int i=1; i<=K; i++) if(~dp[N&1][i]) ans++;
		printf("%d\n", ans);
	}
	return 0;
}


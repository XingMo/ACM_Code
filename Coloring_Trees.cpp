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

const int maxn=100+10;
const LL INF=0x3f3f3f3f3f3f3f3f;
int N,M,K;
int in[maxn];
int C[maxn][maxn];
LL dp[2][maxn][maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d%d", &N, &M, &K))
	{
		for(int i=1; i<=N; i++) scanf("%d", &in[i]);
		for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) scanf("%d", &C[i][j]);
		MST(dp,0x3f);
		if(!in[1]) for(int i=1; i<=M; i++) dp[1][i][1] = C[1][i];
		else dp[1][in[1]][1] = 0;
		for(int i=2; i<=N; i++)
		{
			int cur=i&1, las=(i-1)&1;
			MST(dp[cur],0x3f);
			for(int j=1; j<=M; j++)
			{
				for(int k=1; k<=K; k++) if(dp[las][j][k]<INF)
				{
					if(!in[i])
					{
						dp[cur][j][k] = min(dp[cur][j][k], dp[las][j][k] + C[i][j]);
						if(k<K)
						{
							for(int nj=1; nj<=M; nj++) if(j!=nj)
							{
								dp[cur][nj][k+1] = min(dp[cur][nj][k+1], dp[las][j][k] + C[i][nj]);
							}
						}
					}
					else
					{
						if(j==in[i]) dp[cur][in[i]][k] = min(dp[cur][in[i]][k], dp[las][j][k]);
						if(k<K && j!=in[i]) dp[cur][in[i]][k+1] = min(dp[cur][in[i]][k+1], dp[las][j][k]);
					}
				}
			}
		}
		LL ans=INF;
		if(in[N]) ans = dp[N&1][in[N]][K];
		else
		{
			for(int i=1; i<=M; i++) ans = min(ans, dp[N&1][i][K]);
		}
//		cout << dp[N&1][in[N]][3] << "\n";
		if(ans < INF) cout << ans << "\n";
		else puts("-1");
	}
	return 0;
}


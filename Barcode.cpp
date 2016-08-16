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
#define PCUT puts("\n----------")

const int maxn=1e3+10, INF=0x3f3f3f3f;
char buff[maxn];
int N,M,X,Y,dp[2][maxn];
int cnt[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d%d%d", &N, &M, &X, &Y))
	{
		CLR(cnt);
		for(int i=0; i<N; i++)
		{
			scanf(" %s", buff+1);
			for(int j=1; j<=M; j++) if(buff[j]=='#') cnt[j] ++;
		}
		for(int i=1; i<=M; i++) cnt[i] += cnt[i-1];
		MST(dp,0x3f);
		dp[0][0] = dp[1][0] = 0;
		
 		for(int i=X; i<=M; i++)
 		{
 			for(int j=X; j<=Y && i-j>=0; j++)
 			{
 				dp[0][i] = min(dp[0][i], dp[1][i-j] + cnt[i]-cnt[i-j]);
 				dp[1][i] = min(dp[1][i], dp[0][i-j] + N*j - (cnt[i]-cnt[i-j]));
 			}
 		}
 		printf("%d\n", min(dp[0][M], dp[1][M]));
	}
	return 0;
}

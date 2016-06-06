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

int N,M,fmask;
int P[25];
int pref[25][25];
int dp[2][1<<20];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif

	while(~scanf("%d%d", &N, &M))
	{
		for(int i=1; i<=N; i++)
		{
			scanf("%d", &P[i]);
			for(int j=0; j<P[i]; j++)
			{
				scanf("%d", &pref[i][j]);
				pref[i][j]--;
			}
			sort(pref[i], pref[i]+P[i]);
			P[i]=unique(pref[i],pref[i]+P[i])-pref[i];
		}
		CLR(dp);
		dp[0][0]=1;
		for(int i=1; i<=N; i++)
		{
			int cur=i&1, las=(i-1)&1;
			CLR(dp[cur]);
			for(int m=0; m<1<<M; m++)
			{
				if(!dp[las][m]) continue;
				for(int k=0; k<P[i]; k++)
				{
					if(m&(1<<pref[i][k])) continue;
					dp[cur][m|(1<<pref[i][k])] += dp[las][m];
				}
			}
		}
		int ans=0;
		for(int i=0; i<1<<M; i++) ans+=dp[N&1][i];
		printf("%d\n", ans);
	}
	return 0;
}


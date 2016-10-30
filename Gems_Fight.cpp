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

const int INF = 0x3f3f3f3f;
int G,B,S,fmask;
int bag[25][10];
int cnt[10];
int dp[1<<21][2];
int cook[1<<21][9], lefts[1<<21][9];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d%d", &G, &B, &S))
	{
		if(G==0 && B==0 && S==0) break;
		CLR(bag); CLR(cnt); CLR(dp); CLR(cook); CLR(lefts);
		fmask = (1<<B)-1;
		for(int i=0,n,x; i<B; i++)
		{
			scanf("%d", &n);
			for(int j=0; j<n; j++)
			{
				scanf("%d", &x);
				bag[i][x] ++;
				cnt[x] ++;
			}
		}
		for(int m=0; m<=fmask; m++)
		{
			for(int i=0; i<B; i++) if((m>>i)&1) for(int j=1; j<=G; j++)
				cook[m][j] += bag[i][j];
			for(int i=1; i<=G; i++) lefts[m][i] = cook[m][i] % S;
		}
		
		for(int m=fmask-1; m>=0; m--)
		{
			for(int stat=0; stat<2; stat++)
			{
				for(int i=0; i<B; i++) if(!( (m>>i)&1 ))
				{
					int cost0 = 0, cost1 = 0, nxt = m|(1<<i);
					for(int j=1; j<=G; j++) cost0 += (lefts[m][j] + bag[i][j]) / S;
					if(cost0) dp[m][stat] = max(dp[m][stat], dp[nxt][stat] + cost0);
					else
					{
						for(int j=1; j<=G; j++) cost1 += (cook[fmask&(~nxt)][j] + lefts[nxt][j])/S;
						dp[m][stat] = max(dp[m][stat], cost1-dp[nxt][stat^1]);
					}
				}
			}
		}
//		puts("done");
		int tot = 0;
		for(int i=1; i<=G; i++) tot += cnt[i]/S;
		printf("%d\n", 2*dp[0][0]-tot);
	}
	return 0;
}

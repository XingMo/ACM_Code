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

const int maxn=1e3+10;
const DBL eps=1e-7;
int R,C;
DBL inpt[maxn][maxn][3];
DBL dp[maxn][maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &R, &C))
	{
		for(int i=1; i<=R; i++) for(int j=1; j<=C; j++) for(int k=0; k<3; k++)
		{
			scanf("%lf", &inpt[i][j][k]);
		}
		CLR(dp);
		for(int i=R; i>0; i--)
		{
			for(int j=C; j>0; j--)
			{
				if(i==R&&j==C) continue;
				DBL *prob=inpt[i][j];
				if(1.0-prob[0]<eps) dp[i][j]=1e9;
				else dp[i][j] = ( dp[i][j+1]*prob[1] + dp[i+1][j]*prob[2] + 2 )/( 1.0-prob[0] );
			}
		}
		printf("%.3f\n", dp[1][1]);
	}
	return 0;
}


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
#define Sqr(a) ((a)*(a))

const int maxn=1e3+10;
int N,S;
DBL dp[maxn][maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &S))
	{
		dp[N][S]=0.0;
		for(int i=N; i>=0; i--)
		{
			for(int j=S; j>=0; j--)
			{
				if(i==N && j==S) continue;
				DBL p1=(DBL)i/N, p2=(DBL)j/S;
				dp[i][j] = (1-p1)*p2*dp[i+1][j] + p1*(1-p2)*dp[i][j+1] + (1-p1)*(1-p2)*dp[i+1][j+1] + 1;
				dp[i][j] /= 1-p1*p2;
			}
		}
		printf("%.5f\n", dp[0][0]);
	}
	return 0;
}


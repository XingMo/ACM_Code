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
#define PCUT puts("----------")

const int maxn=1e5+10;
DBL dp[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	dp[1]=0;
	for(int i=2; i<maxn; i++)
	{
		int Lim=sqrt(i), cnt=2;
		dp[i] = 0;
		for(int j=2; j<=Lim; j++) if(i%j==0)
		{
			cnt+=2;
			dp[i] += dp[j] + dp[i/j];
		}
		if(Lim*Lim==i) {cnt--; dp[i] -= dp[Lim];}
		dp[i] = (dp[i]+cnt)/(DBL)(cnt-1);
	}
	
	int T;
	scanf("%d", &T);
	for(int ck=1, N; ck<=T; ck++)
	{
		scanf("%d", &N);
		printf("Case %d: %.7f\n", ck, dp[N]);
	}
	return 0;
}


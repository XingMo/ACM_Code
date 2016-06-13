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

const int offset=1e5, maxc=2*offset+10, NINF=0x80808080;
int N;
int dp[2][maxc];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		MST(dp,0x80);
		dp[0][offset]=0;
		for(int i=1; i<=N; i++)
		{
			int ns,nf;
			scanf("%d%d", &ns, &nf);
			
			int cur=i&1, las=(i-1)&1;
			MST(dp[cur],0x80);
			for(int s=-offset; s<=offset; s++)
			{
				dp[cur][s+offset] = max(dp[cur][s+offset], dp[las][s+offset]);
				if(dp[las][s+offset]<=NINF) continue;
				dp[cur][s+ns+offset] = max(dp[cur][s+ns+offset], dp[las][s+offset]+nf);
			}
		}
		int ans=0;
		for(int s=0; s<=offset; s++)
		{
			int f=dp[N&1][s+offset];
			if(f>=0) ans = max(ans, s+f);
		}
		
		printf("%d\n", ans);
	}
	return 0;
}


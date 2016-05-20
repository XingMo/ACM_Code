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

const int maxn=2e3+10, maxc=3e3+10, INF=0x3f3f3f3f;
int N;
int inpt[2][maxn];
int dp[2][2][maxc];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		scanf("%d", &N);
		for(int i=1; i<=N; i++) scanf("%d%d", &inpt[0][i], &inpt[1][i]);
		MST(dp,0x3f);
		dp[0][0][0]=dp[0][1][0]=0;
		for(int i=1; i<=N; i++)
		{
			int cur=i&1,las=(i-1)&1;
			MST(dp[cur],0x3f);
			for(int k=0; k<2; k++)
			{
				for(int j=0; j<maxc; j++)
				{
					if(dp[las][k][j]>=INF) continue;
					int H[2];
					H[k]=dp[las][k][j], H[k^1]=dp[las][k][j]-j;
					//add to the higher
					dp[cur][k][inpt[k][i]]=min(dp[cur][k][inpt[k][i]], H[k]+inpt[k][i]);
					//add to the lower
					int nh=max(H[k^1]+inpt[k^1][i], H[k]), nl=min(H[k^1]+inpt[k^1][i], H[k]);
					int dif=abs(nh-nl);
					int nk=(H[k^1]+inpt[k^1][i])>H[k]?(k^1):k;
					dp[cur][nk][dif]=min(dp[cur][nk][dif], nh);
				}
			}
		}
		int ans=INF;
		for(int k=0; k<2; k++)
		{
			for(int j=0; j<maxc; j++) ans=min(ans, dp[N&1][k][j]);
		}
		printf("%d\n", ans);
	}
	return 0;
}


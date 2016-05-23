/*
SCU - 4512
有若干个积木，你可以选择将他放在 A塔，放在 B塔，或者不放
求在两塔高度相等的情况下，所能达到的最大高度

朴素的想法是 dp[i][H1][H2]表示使用前 i个积木
A塔高度为 H1，B塔高度为 H2，dp存的是能否到达这个状态的一个 bool值
首先这样状态爆炸，所以依旧要合理调整状态位置
我们可以把最高塔的高度移到 dp存的最优值里，
然后状态里表示一下两塔的高度差，因为根据高度差能算出次高塔的高度

这样一来状态表示就变为了二维，
即dp[i][d]表示使用前 i个积木，两塔高度差为 d，较高塔的高度最高为多少
最后答案即为 dp[N][0]
*/
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

const int maxv=5e5+10;
int N;
int inpt[100];
int dp[2][maxv];

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
		for(int i=1; i<=N; i++) scanf("%d", &inpt[i]);
		MST(dp,-1);
		dp[0][0]=0;
		for(int i=1; i<=N; i++)
		{
			int cur=i&1,las=(i-1)&1;
			for(int j=0; j<maxv; j++) dp[cur][j]=dp[las][j];
			for(int j=0; j<maxv; j++)
			{
				if(dp[las][j]==-1) continue;
				int H=dp[las][j], L=dp[las][j]-j;
				if(L+inpt[i]<maxv)
				{
					int tD=abs(L+inpt[i]-H);
					int tH=max(L+inpt[i],H);
					dp[cur][tD]=max(dp[cur][tD], tH);
				}
				if(H+inpt[i]-L<maxv)
				{
					dp[cur][H+inpt[i]-L]=max(dp[cur][H+inpt[i]-L], H+inpt[i]);
				}
			}
		}
		if(dp[N&1][0]) printf("%d\n", dp[N&1][0]);
		else puts("GG");
	}
	return 0;
}


/*
SCU - 4515
有 N个大小不同的数字，第 i种数字为 a_i，每种有 m_i个
求问能否从中选出若干个数字，使他们的和为 K

背包九讲 2.0的例题，用多重背包的二进制能过
因为 K<1e5，所以其实最后用到的物品数量不会超过 1e5
所以 m_i = min(m_i, K/a_i)，所以用二进制优化能过

背包九讲上的做法如下：
dp[i][j] 表示前 i个物品，组成背包容量为 j时，
所剩下的最多第 i个物品的数量，不能到达的状态设为 -1
然后检查能否转移到 dp[N][K]即可
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

const int maxk=1e5+10;
int N,K;
int W[110],M[110];
int dp[2][maxk];

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
		scanf("%d%d", &N, &K);
		MST(dp,-1);
		dp[0][0]=0;
		for(int i=1; i<=N; i++) scanf("%d", &W[i]);
		for(int i=1; i<=N; i++) scanf("%d", &M[i]);
		for(int i=1; i<=N; i++)
		{
			int cur=i&1,las=(i-1)&1;
			MST(dp[cur],-1);
			for(int j=0; j<maxk; j++) if(~dp[las][j]) dp[cur][j]=M[i];
			
			for(int j=0; j<maxk-W[i]; j++)
			{
				if(dp[cur][j]>0)
				{
					dp[cur][j+W[i]]=max(dp[cur][j+W[i]], dp[cur][j]-1);
				}
			}
		}
		if(~dp[N&1][K]) printf("yes");
		else printf("no");
		if(ck<T) puts("");
	}
	return 0;
}


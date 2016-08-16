/*
HDU - 5800
有 n个物品，f(i,j,k,l,m)为选定 i，j，不选 k，l，总权值为 m的方案数
求 \sum_{i=1}^{n}\sum_{j=1}^{n}\sum_{k=1}^{n}\sum_{l=1}^{n}\sum_{m=1}^{s} f(i,j,k,m)

不得不说我的两个队友太劲了，一个在最后20分钟想出正解
一个在最后5分钟写了9个涉及了将近20个状态的转移方程，
然后 debug成功并且 ac绝杀了

问题转化一下就为选择物品的个数在 [2,n-2]这个区间
总权值为 m方案计数，设 dp[i][s][j][k]表示
已经考虑了前 i个物品，选择的总价值和为 s
其中有 j个是选了的并且是枚举的必选 (i,j)
有 k个是不选的并且是枚举的必不选的 (k,l)
然后就是一个普通的背包DP
最后把 1...S的方案数全加起来，然后还要乘 4
因为这个转移的时候没有考虑 (i,j)和 (k,l)的选择顺序
*/
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

const int maxn=1e3+10, MOD=1e9+7;
int N,S;
LL dp[2][maxn][3][3];

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
		scanf("%d%d", &N, &S);
		CLR(dp);
		dp[0][0][0][0]=1;
		for(int i=0, w; i<N; i++)
		{
			scanf("%d", &w);
			int cur=i&1, nxt=(i+1)&1;
			CLR(dp[nxt]);
			for(int s=0; s<=S; s++)
			{
				for(int j=0; j<3; j++)
				{
					for(int k=0; k<3; k++) if(dp[cur][s][j][k])
					{
						LL now = dp[cur][s][j][k];
						if(s+w<=S)
						{
							dp[nxt][s+w][j][k] = (dp[nxt][s+w][j][k] + now)%MOD;
							if(j<=1) dp[nxt][s+w][j+1][k] = (dp[nxt][s+w][j+1][k] + now)%MOD;
						}
						dp[nxt][s][j][k] = (dp[nxt][s][j][k] + now)%MOD;
						if(k<=1) dp[nxt][s][j][k+1] = (dp[nxt][s][j][k+1] + now)%MOD;
					}
				}
			}
		}
		LL ans=0;
		for(int i=1; i<=S; i++) ans = (ans + dp[N&1][i][2][2])%MOD;
		printf("%lld\n", ans*4%MOD);
	}
	return 0;
}


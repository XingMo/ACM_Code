/*
PKU - 3046
有 T组蚂蚁，每组有 Ni只，同组蚂蚁没有区别
问从中选出一定数量的选法有多少种

计数DP
dp[i][j]表示考虑到第 i组蚂蚁，size大小为 j的选法
其中 i可以滚动数组优化掉，就变成了 dp[2][j]

然后对于每组蚂蚁，枚举只数 k，更新答案
dp[cur][j] += dp[las][j-k] 其中cur为当前状态，las为前一层状态
但是这样做会 T，所以我们不必逐个更新，可以使用差分的技巧
比如要将 j到 j+num[i]都加上某个值，只需在 j处加，在 j+num[i]+1处减
最后扫一遍更新即可

时间复杂度 O(AT)
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
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) ((a)*(a))

const int maxt=1e3+10, maxc=1e5+10, MOD=1e6;
int T,A,S,B;
int dp[2][maxc];
int num[maxt];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d%d%d", &T, &A, &S, &B))
	{
		CLR(dp); CLR(num);
		for(int i=1; i<=A; i++)
		{
			int x;
			scanf("%d", &x);
			num[x]++;
		}
		dp[0][0]=1;
		int sum=0;
		for(int i=1; i<=T; i++)
		{
			int cur=i&1, las=(i-1)&1;
			CLR(dp[cur]);
			for(int j=0; j<=sum; j++)
			{
				int r=j+num[i]+1;
				dp[cur][j] += dp[las][j];
				dp[cur][r] -= dp[las][j];
			}
			int cnt=0;
			for(int j=0; j<=sum+num[i]+1; j++)
			{
				cnt = (cnt+dp[cur][j])%MOD;
				dp[cur][j]=cnt;
			}
			sum+=num[i];
		}
		int ans=0;
		for(int i=S; i<=B; i++) ans = (ans+dp[T&1][i]) %MOD;
		printf("%d\n", (ans+MOD)%MOD);
	}
	return 0;
}


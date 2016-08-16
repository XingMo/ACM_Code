/*
HDU - 5819
棋盘上有 N个骑士，他们要么向左走，要么向右走
他们相遇时会发生决斗，每个人都有 1/2的概率获胜
胜者继续前进，败者直接退出游戏，骑士走到棋盘边缘会回头
问第 N个骑士获胜的概率

看了题解的状态，感觉太神了……
首先第一个骑士肯定向右，第 N个肯定向左
第 N个骑士获胜的条件，即为打败所有左边向右走的骑士
设 dp[i][j]为前 i个骑士有 j个向右走的概率

如果第 i个骑士向右走，那么 dp[i][j] = dp[i-1][j-1]

如果第 i个骑士向左走，那么 dp[i][j] = \sum_{k=j}^{i-1} dp[i-1][k]*(1/2)^{k-j+1}
即原本有 k个骑士向左走，第 i个骑士阻挠了 k-j个，并且最后失败的概率
这个转移方程还需要优化一下，由于是个类似等比数列的形式
所以 dp[i][j] = (dp[i][j+1] + dp[i-1][j])/2
还有一种情况是，第 i个骑士打败了左边所有的骑士，最后改变方向向右走
dp[i][1] += \sum_{k=1}^{i-1} dp[i-1][k]*(1/2)^k

最后的答案即为 dp[N][1]/2，表示最后只剩两个骑士决斗，第 N个骑士获胜的概率
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

const int maxn=1e3+10, inv2=500000004, MOD=1e9+7;
int N;
int A[maxn];
LL dp[2][maxn];

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
		for(int i=1; i<=N; i++) scanf("%d", &A[i]);
		A[N]=0;
		CLR(dp);
		dp[1][1] = 1;
		for(int i=2, cur, las; i<=N; i++)
		{
			cur=i&1, las=(i-1)&1;
			CLR(dp[cur]);
			if(A[i]) for(int j=2; j<=i; j++) dp[cur][j] = dp[las][j-1];
			else
			{
				for(int j=i-1; j>=1; j--)
				{
					dp[cur][j] = (dp[cur][j+1] + dp[las][j])%MOD *inv2%MOD;
				}
				LL prod = inv2;
				for(int j=1; j<=i-1; j++)
				{
					dp[cur][1] = (dp[cur][1] + dp[las][j]*prod%MOD)%MOD;
					prod = prod*inv2%MOD;
				}
			}
		}
		LL ans = dp[N&1][1]*inv2%MOD;
		printf("Case #%d: %lld\n", ck, ans);
	}
	return 0;
}


/*
SCU - 4511
给两个机器安排 N个任务，要求满足
1. 任务必须全部被安排到任一机器上
2. 同一时间一台机器只能运行一个任务
3. 任务 j (j<i)必须在任务 i之前被安排
4. 在一台机器上运行的任务不能被打断

第 i个任务在两台机器上的用时分别为 a_i，b_i
要求所有任务的总用时最小


这题我想了三天三夜，还是没搞明白这题怎么做
直到第四天早上起来，再读一遍题目，才发现我少读了一个条件
第三个条件尤为重要：任务 j (j<i)必须在任务 i之前被安排

例如之前 A已经被安排了任务 1,用时 2; 任务 3,用时 2
B之前已经被安排了任务 2，用时 1
那么现在我要给 B安排任务 4,只能从 2时刻开始安排
我在高数课上把条件三反复咀嚼了一百遍以上，然后回去以后十分钟就秒了这题

所以实际上，任何两个任务被安排的时间差不会超过最大任务时间
所以这题的状态其实和经典的双子塔的 dp状态差不多
设 dp[i][k][j]为前 i个任务，用时最多的机器是 k，两者用时差为 j
dp里面存的是最少用时
有了这些状态，我们可以知道 A、B的最小用时，
即下一个任务在两边该从什么时刻开始安排
然后就可以进行转移了
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


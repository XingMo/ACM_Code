/*
Codeforces - 673E
有 N个关卡，可以分为 K块，每个关卡都有个权值 t_i
每次选择最早没有通关的关卡块，设这个关卡包含了[i,j]的游戏
选到最早没有通关的关卡是k, 选到 k的概率是 P = t_k / {\sum_{x=i}^j x}
选到一个关卡一定能通关，花费一小时
求合理分块的情况下，通关所有关卡块的期望时间最小是多少

几个月前做过一次这道题，当时比较弱，不会推期望公式
很显然地能得到一个dp转移方程，设 dp[k][i]为前 i位分成 k块之后的最小期望
dp[k][i] = min(dp[k-1][j] + E(j+1,i))
其中 E(j+1,i)为 [j+1,i]这一块的通关期望

先研究 E(l,r)的表达式，显然我们有
E(l,i-1) = p*E(l,i) + (1-p)*E(l,i-1) + 1
其中 p为开启新的关卡的概率， p = t_i / {\sum_{x=l}^i x}
所以 E(l,i-1) = E(l,i) + 1/p，这样一来就可以得到
E(l,r) = \sum_{i=l}^r {\sum_{j=l}^i{t_j} / t_i}
为了能 O(1)得到 E(l,r)，我们对这个式子变形一下，并预处理出一些前缀和
S[i]表示 t_i的前缀和， A[i]表示 S[i]/t_i的前缀和，B[i]表示 1/t_i的前缀和
E(l,r) = \sum_{i=l}^r {S[i]-S[l-1]}/t_i
=\sum_{i=l}^r {S[i]/t_i} - S[l-1]*\sum_{i=l}^r {1/t_i}
=A[r]-A[l-1] - S[l-1]*(B[r]-B[l-1])
所以 dp[k][i] = min(dp[k-1][j] + A[i] - A[j] - S[j]*(B[i]-B[j]))
至此我们得到了完整的转移方程，时间复杂度为 O(N^2*K)

但是这个复杂度显然不能通过 N<=2e5的数据，所以考虑优化（斜率优化）
斜率优化本质上就是一个利用单调队列维护下凸壳的过程，
一些形如 dp[i] = min(dp[j] + W(j,i))的方程都可能用得上这个优化

设下标 k<j，并且 dp[k] + E(k+1,i) > dp[j] + E(j+1,i)，那么显然我们选择从 j转移
展开这个式子，能得到 
dp[k] + A[i] - A[k] - S[k]*(B[i]-B[k]) > dp[j] + A[i] - A[j] - S[j]*(B[i]-B[j])
化简成如下形式
{(dp[j]-A[j]+S[j]*B[j]) - (dp[k]-A[k]+S[k]*B[k])} / {S[j] - S[k]} < B[i]
左边就变成了一个斜率的形式，而右边的 B[i]是单调递增的
也就是说所有斜率小于 B[i]的 k都能被优化掉，而优化掉之后剩下能转移的点就形成了一个下凸壳
利用单调队列维护这个凸壳，每个点最多只会进队出队一次，这样一来时间复杂度就是 O(NK)
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
#include <complex>
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

const int maxn=2e5+10;
int N,K,T[maxn];
DBL A[maxn],B[maxn],S[maxn],dp[2][maxn];
int que[2*maxn];
DBL Y(int,int,int), X(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &K))
	{
		for(int i=1; i<=N; i++)
		{
			scanf("%d", &T[i]);
			S[i] = S[i-1] + T[i];
			A[i] = A[i-1] + S[i]/T[i];
			B[i] = B[i-1] + 1.0/T[i];
			dp[1][i] = A[i];
		}
//		for(int i=1; i<=N; i++) printf("%.4f\n", A[i]);
		for(int k=2,cur,las,head,tail; k<=K; k++)
		{
			head=0,tail=0;
			cur = k&1, las = (k-1)&1;
			que[tail++] = 0;
			CLR(dp[cur]);
			for(int i=1; i<=N; i++)
			{
				while(tail-head>1 && Y(las,que[head],que[head+1]) < X(que[head],que[head+1])*B[i]) head++;
				int p = que[head];
				dp[cur][i] = dp[las][p] + A[i] - A[p] - S[p]*(B[i]-B[p]);
				while(tail-head>1 && 
					Y(las,que[tail-1],i)*X(que[tail-2],que[tail-1]) - Y(las,que[tail-2],que[tail-1])*X(que[tail-1],i) <= 0) tail--;
				que[tail++] = i;
			}
		}
		printf("%.6f\n", dp[K&1][N]);
	}
	return 0;
}

DBL Y(int cur, int k, int j)
{
	return (dp[cur][j]-A[j]+S[j]*B[j])-(dp[cur][k]-A[k]+S[k]*B[k]);
}

DBL X(int k, int j)
{
	return S[j]-S[k];
}

/*
SCU - 4516
有 N个关卡，可以分为 K块，每个关卡都有个权值 t_i
每次选择最早没有通关的关卡块，设这个关卡包含了[i,j]的游戏
选到最早没有通关的关卡是k, 选到 k的概率是 P = t_k / sigma_{x=i}^j x
选到一个关卡一定能通关，花费一小时
求合理分块的情况下，通关所有关卡块的期望时间最小是多少

原题是 CodeForces - 643C Levels and Regions ，做法是斜率优化DP。
概率公式的推导过程一脸懵逼，反正我看了题解才会做的 0.0
http://m.blog.csdn.net/article/details?id=51346853
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

const int maxn=5e5+10;
int N,K;
DBL psum[maxn],qsum[maxn],E[maxn];
DBL dp[60][maxn];
int que[maxn*2];

DBL Up(int,int,int);
DBL Down(int,int);

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
		for(int i=1; i<=N; i++)
		{
			DBL x;
			scanf("%lf", &x);
			psum[i]=psum[i-1]+x;
			qsum[i]=qsum[i-1]+1/x;
			E[i]=E[i-1]+psum[i]/x;
			dp[1][i]=E[i];
		}
		for(int k=2; k<=K; k++)
		{
			int head=0,tail=1;
			que[0]=1;
			CLR(dp[k]);
			for(int i=1; i<=N; i++)
			{
				while(head+1<tail && 
					Up(k-1, que[head], que[head+1]) <= qsum[i]*Down(que[head], que[head+1]))
					head++;
			
				int j=que[head];
				dp[k][i]=dp[k-1][j-1]+E[i]-E[j-1]-psum[j-1]*(qsum[i]-qsum[j-1]);
			
				while(head+1<tail &&
					Up(k-1, que[tail-1], i)*Down(que[tail-2], que[tail-1]) <= Up(k-1, que[tail-2], que[tail-1])*Down(que[tail-1], i))
					tail--;
				que[tail++]=i;
			}
		}
		printf("%.4f\n", dp[K][N]);
	}
	return 0;
}

DBL Up(int flr, int k, int j)
{
	return dp[flr][j-1]-E[j-1]+psum[j-1]*qsum[j-1]-(dp[flr][k-1]-E[k-1]+psum[k-1]*qsum[k-1]);
}

DBL Down(int k, int j)
{
	return psum[j-1]-psum[k-1];
}

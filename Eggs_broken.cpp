/*
CDOJ - 1051
有 N层楼，K颗蛋。其中从 0楼扔蛋，蛋不会碎，从 N楼扔蛋，蛋必碎。
问找到最小的 x，从 x扔蛋，蛋会碎，从 i<x扔蛋，蛋不会碎
找到 x的最小期望步数是多少

首先，如果蛋没有碎的话，可以捡起来重复利用
枚举扔蛋的位置 i，当前未确定的层数有 n层
由于 x是均匀分布的，那么蛋在第 i层碎掉的可能性就为 i/n
所以设 dp[n][k]为未确定层数有 n层，剩余 k颗蛋，试出 x的最小期望
dp[n][k] = min( dp[i][k-1]*(i/n) + dp[n-i][k]*(1-i/n) ) + 1
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

const int maxn=1e3+10;
int N,K;
DBL dp[maxn][20];
DBL DP(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &K))
	{
		CLR(dp);
		printf("%.5f\n", DP(N,K));
	}
	return 0;
}

DBL DP(int n, int k)
{
	if(dp[n][k]>0) return dp[n][k];
	if(n==1) return dp[n][k]=0;
	if(k==0) return dp[n][k]=1e9;
	
	dp[n][k] = 1e9;
	for(int i=1; i<n; i++)
	{
		DBL prob = (DBL) i/n;
		dp[n][k] = min(dp[n][k], DP(i, k-1)*prob + DP(n-i, k)*(1-prob) );
	}
	dp[n][k] += 1.0;
	return dp[n][k];
}


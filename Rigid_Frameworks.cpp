/*
HDU - 5729
给定一个 N*M的矩形格子，问在一个格子里只添加一条斜线，
将整个图形变成一个刚性的图形的方案数有多少种

根据 Project Euler 434，问题可以转化为
一个左边有 N个点，右边有 M个点的二分图的联通方案计数
首先对于一个 N*M的格子图，每个格子要么不加，
要么向左加一条斜线，要么向右加一条斜线，所以总方案数 2^(N*M)
接下来扣去其中不合法的方案数

设 dp[n][m]为左边 n个点，右边 m个点的方案数
对于左边的某一个点（不妨设为 1号点），
如果它不与图中其他所有点同在一个联通分量，那么就是不合法的
设从左边选 i个点，右边选 j个点与 1在同一个联通分量
剩下的 n-1-i与 m-j个点随意连接
方案数为 C(n-1, i)*C(m, j)*dp[i+1][j]*3^((n-1-i)*(m-j))
所以枚举 i和 j减去即可
dp_{n,m} = 3^{n*m} - \sum_{i=0,j=0}^{i<=n-1, j<=m} C_{n-1}^{i}*C_{m}^{j}*dp_{i+1.j}*3^{(n-1-i)*(m-j)}

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
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define SQR(a) ((a)*(a))
#define PCUT puts("----------")

const int MOD=1e9+7;
int N,M;
LL dp[20][20];
LL pow3[110];
LL C[20][20];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	pow3[0]=1;
	for(int i=1; i<=100; i++) pow3[i] = pow3[i-1]*3%MOD;
	for(int i=0; i<=10; i++)
	{
		C[i][0]=1;
		for(int j=1; j<=i; j++) C[i][j] = (C[i-1][j] + C[i-1][j-1])%MOD;
	}
	
	for(int n=0; n<=10; n++) for(int m=0; m<=10; m++)
	{
		dp[n][m] = pow3[n*m];
		for(int i=0; i<=n-1; i++)
		{
			for(int j=0; j<=m; j++)
			{
				if(i==n-1 && j==m) break;
				dp[n][m] = (dp[n][m] - C[n-1][i]*C[m][j]%MOD * pow3[(n-1-i)*(m-j)]%MOD * dp[i+1][j] )%MOD;
			}
		}
		dp[n][m] = (dp[n][m]+MOD)%MOD;
	}
	
	while(~scanf("%d%d", &N, &M)) printf("%lld\n", dp[N][M]);
	return 0;
}


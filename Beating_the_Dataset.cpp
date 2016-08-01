/*
LightOJ - 1274
题目等价于，给定一个开头为 1的 01串，
求其中相邻两个字符不相等的期望对数

一开始煞笔了，其实 YES和 NO的个数是可以直接算出来的
算出来之后，设 dp[i][j][k]为第 i位，j表示当前是 YES(1)或 NO(0)
k表示 i位及以前一共有多少个 YES，然后倒着就推出来了
下一位出现 0或 1的概率可以用剩下除以后面的位数得到
如果下一位与当前位不同，期望加 1，否则不加
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
#define PCUT puts("----------")

const int maxn=5e3+10;
int N,S;
DBL dp[2][2][maxn];

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
		int A=S-2*N, B=3*N-S;
		CLR(dp);
		for(int i=N-1; i>=1; i--)
		{
			int cur=i&1, nxt=(i+1)&1;
			CLR(dp[cur]);
			for(int j=max(0, i-B); j<=i && j<=A; j++)
			{
				DBL pa = (DBL)(A-j)/(N-i), pb = (DBL)(B-(i-j))/(N-i);
				dp[cur][0][j] = pa*(dp[nxt][1][j+1] + 1) + pb*dp[nxt][0][j];
				dp[cur][1][j] = pa*dp[nxt][1][j+1] + pb*(dp[nxt][0][j] + 1);
			}
		}
		DBL ans = A*dp[1][1][1]/N + B*(dp[1][0][0]+1)/N;
		printf("Case %d: %.7f\n", ck, ans);
	}
	return 0;
}


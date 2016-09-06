/*
Codeforces - 543C
给定 N个长度皆为 M的字符串，其中 1<=N,M<=20
将第 i个字符串的第 j为修改成其他字符需要代价 a_{ij}
要求用最少的代价，使得每个字符串都至少有一位是独一无二的

很显然的一个状压DP
首先状压一下哪些字符串已经是独一无二的
由于字符串数量小于可用字母数量，所以总是能自由修改字符
考虑转移，要想把一个字符串的某一位修改，使得它满足条件
那么直接的想法是修改这一位，但是有可能这一位代价很大，
而修改这一位与其相同的所有字符串的代价加起来也没它大
所以还有一种选择是修改所有这一位与其相同的字符串
然后保留代价最大的那个不改就行了
而这个可以 O(N^2*M)预处理出来
而 DP的复杂度也只有 O(2^N*M)

接下来就是实现问题了
由于修改的先后顺序是无所谓的，可以总是选择编号最小的那个字符串修改就行了
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

int N,M,fmask;
char str[25][25];
int same[25][25], cost[25][25], scost[25][25];
int dp[1<<20];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		fmask=(1<<N)-1;
		for(int i=0; i<N; i++) scanf("%s", str[i]);
		for(int i=0; i<N; i++) for(int j=0; j<M; j++) scanf("%d", &cost[i][j]);
		
		for(int i=0; i<N; i++) for(int j=0; j<M; j++)
		{
			same[i][j] = 1<<i;
			scost[i][j] = cost[i][j];
			int tmax=cost[i][j];
			for(int k=0; k<N; k++) if(k != i && str[i][j]==str[k][j])
			{
				same[i][j] |= 1<<k;
				scost[i][j] += cost[k][j];
				tmax = max(tmax, cost[k][j]);
			}
			scost[i][j] -= tmax;
		}
		
		MST(dp,0x3f);
		dp[0]=0;
		for(int m=1,fir; m<=fmask; m++)
		{
			for(int i=0; i<N; i++) if((m>>i)&1) {fir=i; break;}
			for(int i=0; i<M; i++)
			{
				dp[m] = min(dp[m], dp[m^(1<<fir)] + cost[fir][i]);
				dp[m] = min(dp[m], dp[m^(m&same[fir][i])] + scost[fir][i]);
			}
		}
		printf("%d\n", dp[fmask]);
	}
	return 0;
}


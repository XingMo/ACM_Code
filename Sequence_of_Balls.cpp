/*
Codeforces - 67C
给定两个字符串 A和 B，要求用四种操作将 A转化为 B
其中可以在 A的任意位置添加、删除或替换任意字符
或者可以交换相邻的两个字符，其中交换两次的代价大于等于添加一次再删除一次

由最后一个条件可得，将一个字符连续交换两次及以上是不划算的
因为你可以把它删掉，再在另一位置加入
设 dp[i][j]表示 A字符串 i位以前，B字符串 j位以前都已经匹配所得的最小代价
添加、删除、替换的转移很显然
添加时从 dp[i][j-1] + t_i ，删除从 dp[i-1][j] + t_d
替换从 dp[i-1][j-1] + t_r
而交换操作只能交换相邻的两个字符，看起来很鸡肋，但也不是完全没用
交换 A串中不相邻的两个字符时，可以先删除掉中间所有字符，
再交换，在添加上 B串中相应两个字符中间的字符
这样操作不仅匹配了两个字符，所以有可能也会得到最优解
所以对于每个字符，预处理一下字符串中距离当前位置的位置
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

const int maxn=4e3+10, INF=0x3f3f3f3f;
int N,M,T[4];
char A[maxn], B[maxn];
int nearA[26][maxn], nearB[26][maxn];
int dp[maxn][maxn];


int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	for(int i=0; i<4; i++) scanf("%d", &T[i]);
	scanf(" %s %s", A+1, B+1);
	N=strlen(A+1);
	M=strlen(B+1);
	MST(nearA,-1); MST(nearB,-1);
	for(int i=1; i<=N; i++)
	{
		for(int j=0; j<26; j++) nearA[j][i] = nearA[j][i-1];
		nearA[A[i]-'a'][i] = i;
	}
	for(int i=1; i<=M; i++)
	{
		for(int j=0; j<26; j++) nearB[j][i] = nearB[j][i-1];
		nearB[B[i]-'a'][i] = i;
	}
	
	dp[0][0]=0;
	for(int i=1; i<=N; i++) dp[i][0] = i*T[1];
	for(int i=1; i<=M; i++) dp[0][i] = i*T[0];
	
	for(int i=1; i<=N; i++)
	{
		for(int j=1; j<=M; j++)
		{
			dp[i][j] = min(dp[i][j-1]+T[0], dp[i-1][j]+T[1]);
			if(A[i]==B[j]) dp[i][j] = min(dp[i][j], dp[i-1][j-1]);
			else dp[i][j] = min(dp[i][j], dp[i-1][j-1]+T[2]);
			int na = nearA[B[j]-'a'][i-1], nb = nearB[A[i]-'a'][j-1];
			if(~na && ~nb)
			{
				dp[i][j] = min(dp[i][j], (i-na-1)*T[1]+(j-nb-1)*T[0]+T[3] + dp[na-1][nb-1]);
			}
		}
	}
	printf("%d\n", dp[N][M]);
	return 0;
}


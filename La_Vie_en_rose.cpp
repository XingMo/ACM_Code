/*
HDU - 5745
给定两个字符串 A，B
每次可以将B串中相邻的两个字符位置交换
每个字符只能改变一次位置
问通过这样的方式，B 能在 A串的哪些位置成为 A的子串
其中 |A|<=1e5，|B|<=5e3

据说 kmp是不行的，据说暴力匹配跑得比谁都快
正解复杂度还是很科学的
首先得出一个 dp式子，dp[i][j][k]表示 A匹配到 i，B匹配到 j
而 k表示 B_j的交换情况，0为不动，1与前面交换，2与后面交换
转移方程为：
dp[i][j][0] = dp[i-1][j-1][0] | dp[i-1][j-1][1] (A_i==B_j)
dp[i][j][1] = dp[i-1][j-1][2] (A_i==B_{j-1})
dp[i][j][2] = dp[i-1][j-1][0] | dp[i-1][j-1][1] (A_i==B_{j+1})

然后二重循环求得dp，但是dp存的是一个bool值，所以可以用 bitset优化
滚动第二维，用bitset表示第一维，预处理出 26个字母在 A中的分布情况
利用各种位运算，就能做到 O(N*M/w)的复杂度，正好能卡过
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

const int maxn=1e5+10, maxm=5e3+10;
int N,M;
char A[maxn], B[maxm];
bitset<maxn> vec[26];
bitset<maxn> dp[2][3];
bool ans[maxn];

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
		scanf("%d%d %s %s", &N, &M, A+1, B+1);
		for(char x='a'; x<='z'; x++)
		{
			int np=x-'a';
			vec[np].reset();
			for(int i=1; i<=N; i++) 
			{
				if(A[i]==x) vec[np][i-1]=1;
			
			}
		}
		dp[0][0].set(); dp[0][1].reset(); dp[0][2].reset();
		for(int i=1; i<=M; i++)
		{
			int cur=i&1, las=(i-1)&1;
			dp[cur][0].reset(); dp[cur][1].reset(); dp[cur][2].reset();
			
			int now=B[i]-'a', pre=B[i-1]-'a', suf=B[i+1]-'a';
			
			dp[cur][0] |= ((dp[las][0]&vec[now]) | (dp[las][1]&vec[now]))<<1;
			if(i>1) dp[cur][1] |= (dp[las][2]&vec[pre])<<1;
			if(i<M) dp[cur][2] |= ((dp[las][0]&vec[suf]) | (dp[las][1]&vec[suf]))<<1;
		}
		CLR(ans);
		for(int i=1; i<=N; i++) if(dp[M&1][0][i] | dp[M&1][1][i]) ans[i-M+1]=1;
		for(int i=1; i<=N; i++) putchar(ans[i]+'0');
		puts("");
	}
	return 0;
}


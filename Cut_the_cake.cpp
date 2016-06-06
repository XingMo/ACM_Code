/*
HDU - 4328
给定一块矩形，每个格子都是蓝色或者红色
从中切下一块矩形，使得切下的矩形内
每一个格子都是同色或者红蓝相间
求满足条件的矩阵的最大周长

第一道悬链法的题目
利用悬链法可以求不包含障碍点的极大矩阵
从而得出不包含障碍点的最大矩阵
具体可以看王知昆的论文《浅谈用极大化思想解决最大子矩形问题》
预处理出悬链底端能向左，向右，向上走的最大距离
最后答案即为 ans = max( 2*( H + L+R-1 ) )
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
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) ((a)*(a))

const int maxn=1e3+10;
int N,M;
char Map[maxn][maxn];
int L[3][maxn][maxn], R[3][maxn][maxn];
int H[3][maxn][maxn];


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
		CLR(L); CLR(R); CLR(H);
		CLR(Map);
		int ans=4;
		scanf("%d%d", &N, &M);
		for(int i=1; i<=N; i++)
		{
			scanf(" %s", Map[i]+1);
			for(int j=1; j<=M; j++)
			{
				L[0][i][j] = L[0][i][j-1] + 1;
				if( Map[i][j] != 'R' ) L[0][i][j] = 0;
				
				L[1][i][j] = L[1][i][j-1] + 1;
				if( Map[i][j] != 'B' ) L[1][i][j] = 0;
				
				L[2][i][j] = L[2][i][j-1] + 1;
				if( Map[i][j] == Map[i][j-1]) L[2][i][j] = 1;
			}
			for(int j=M; j>=1; j--)
			{
				R[0][i][j] = R[0][i][j+1] + 1;
				if( Map[i][j] != 'R' ) R[0][i][j] = 0;
				
				R[1][i][j] = R[1][i][j+1] + 1;
				if( Map[i][j] != 'B' ) R[1][i][j] = 0;
				
				R[2][i][j] = R[2][i][j+1] + 1;
				if( Map[i][j] == Map[i][j+1]) R[2][i][j] = 1; 
			}
			for(int j=1; j<=M; j++)
			{
				H[0][i][j] = H[0][i-1][j] + 1;
				H[1][i][j] = H[1][i-1][j] + 1;
				H[2][i][j] = H[2][i-1][j] + 1;
				
				if( Map[i][j] != 'R' ) H[0][i][j] = 0;
				if( Map[i][j] != 'B' ) H[1][i][j] = 0;
				if( Map[i-1][j] == Map[i][j]) H[2][i][j] = 1;
				
				if( Map[i-1][j] == 'R' ) L[0][i][j] = min( L[0][i][j], L[0][i-1][j]);
				if( Map[i-1][j] == 'B' ) L[1][i][j] = min( L[1][i][j], L[1][i-1][j]);
				if( i>1 && Map[i-1][j] != Map[i][j] ) L[2][i][j] = min( L[2][i][j], L[2][i-1][j]);
				
				if( Map[i-1][j] == 'R' ) R[0][i][j] = min( R[0][i][j], R[0][i-1][j]);
				if( Map[i-1][j] == 'B' ) R[1][i][j] = min( R[1][i][j], R[1][i-1][j]);
				if( i>1 && Map[i-1][j] != Map[i][j] ) R[2][i][j] = min( R[2][i][j], R[2][i-1][j]);
				
				ans = max(ans, 2*(H[0][i][j] + L[0][i][j]+R[0][i][j]-1 ));
				ans = max(ans, 2*(H[1][i][j] + L[1][i][j]+R[1][i][j]-1 ));
				ans = max(ans, 2*(H[2][i][j] + L[2][i][j]+R[2][i][j]-1 ));
				
//				printf("i:%d j:%d H:%d L:%d R:%d\n", i, j, H[1][i][j], L[1][i][j], R[1][i][j]);
			}
		}
		
		printf("Case #%d: %d\n", ck, ans);
	}
	return 0;
}


/*
PKU - 2836
选择若干个矩阵，每个矩阵至少覆盖两个点
问覆盖 N个点所需的矩阵面积和最小是多少

状态压缩DP
首先预处理出矩阵能覆盖哪些点，以及矩阵的面积
然后枚举当前要选择的两点，转移方程为
dp[mask] = min(dp[mask], DP(mask|stat[i][j])+sqre[i][j])

注意几个坑点：
1. 如果两点在平行坐标轴的一条直线上，它依旧是有面积的
2. 可以重复覆盖，递推下一个状态应用或而不是异或
3. 枚举两个点，一个必须是还未覆盖的，另一个可以是已覆盖，也可是未覆盖的
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

const int INF=0x3f3f3f3f;
int N,fmask;
int pos[20][2];

int stat[20][20];
int sqre[20][20];
int dp[1<<16];
int DP(int);
int GetM(int,int);
int GetS(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N) && N)
	{
		fmask=(1<<N)-1;
		MST(dp,0x3f); CLR(stat); CLR(sqre);
		for(int i=0; i<N; i++) scanf("%d%d", &pos[i][0], &pos[i][1]);
		for(int i=0; i<N; i++)
		{
			for(int j=0; j<N; j++)
			{
				if(i==j) continue;
				stat[i][j]=GetM(i,j);
				sqre[i][j]=GetS(i,j);
			}
		}
		printf("%d\n", DP(0));
	}
	return 0;
}

int DP(int mask)
{
	if(mask==fmask) return 0;
	if(dp[mask]<INF) return dp[mask];
	for(int i=0; i<N; i++)
	{
		if(mask&(1<<i)) continue;
		for(int j=0; j<N; j++)
		{
			if(i==j) continue;
			if(sqre[i][j]) dp[mask]=min(dp[mask], DP(mask|stat[i][j])+sqre[i][j]);
		}
	}
	return dp[mask];
}

int GetM(int a, int b)
{
	int x1=min(pos[a][0], pos[b][0]);
	int y1=min(pos[a][1], pos[b][1]);
	int x2=max(pos[a][0], pos[b][0]);
	int y2=max(pos[a][1], pos[b][1]);
	int res=0;
	for(int i=0; i<N; i++)
	{
		int x=pos[i][0], y=pos[i][1];
		if(x>=x1 && x<=x2 && y>=y1 && y<=y2) res|=1<<i;
	}
	return res;
}

int GetS(int a, int b)
{
	int dx=max(1, abs(pos[a][0]-pos[b][0]));
	int dy=max(1, abs(pos[a][1]-pos[b][1]));
	return abs(dx*dy);
}

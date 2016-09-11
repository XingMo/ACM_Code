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

const int maxn=100+10;
const int dir[4][2]={1,0,-1,0,0,1,0,-1};
int R,C;
int Map[maxn][maxn];

int check(int,int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	#ifndef LOCAL
	freopen("lucky.in", "r", stdin);
	freopen("lucky.out", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &R, &C))
	{
		int cnt=0;
		for(int i=1; i<=R; i++) for(int j=1; j<=C; j++) scanf("%d", &Map[i][j]);
		for(int i=1; i<=R; i++) for(int j=1; j<=C; j++) for(int k=0; k<4; k++)
			cnt += check(i,j,k);
		printf("%d\n", cnt);
	}
	return 0;
}

int check(int x, int y, int d)
{
	int ox=x+dir[d][0], oy=y+dir[d][1];
	for(; ox>=1 && ox<=R && oy>=1 && oy<=C; ox+=dir[d][0], oy+=dir[d][1])
	{
		if(Map[ox][oy]>=Map[x][y]) return 0;
	}
	return 1;
}

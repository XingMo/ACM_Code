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

const int dir[8][2]={1,0,-1,0,0,1,0,-1,1,1,1,-1,-1,1,-1,-1};
int N,M;
char Map[110][110];

void Go(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		for(int i=1; i<=N; i++) scanf(" %s", Map[i]+1);
		int ans=0;
		for(int i=1; i<=N; i++)
		{
			for(int j=1; j<=M; j++)
			{
				if(Map[i][j]=='.') continue;
				ans++;
				Go(i,j);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

void Go(int x, int y)
{
	Map[x][y]='.';
	for(int k=0; k<8; k++)
	{
		int nx=x+dir[k][0];
		int ny=y+dir[k][1];
		if(nx<1||ny<1||nx>N||ny>M||Map[nx][ny]=='.') continue;
		Go(nx,ny);
	}
}

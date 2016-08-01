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

int N,M,ans;
int Map[1010][1010];

void go(int,int,int,int);
int res[1010][1010];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int range=30;
	CLR(res);
	for(N=2; N<=range; N++) for(M=N; M<=range; M++)
	{
//	N=5, M=7;
		CLR(Map);
		ans=0;
		for(int i=1; i<=N; i++)
		{
			for(int j=1; j<=M; j++) if(!Map[i][j])
			{
				ans++;
				go(i,j,1,1);
//				for(int i=1; i<=5; i++,puts("")) for(int j=1; j<=7; j++) printf("%d", Map[i][j]);
//				PCUT;
			}
		}
	
		res[N][M] = ans;
//		printf("(%d, %d) = %d\n", N, M, ans);
	}
	int resar=30;
	for(int i=1; i<=resar; i++) printf("%3d", i-1); puts("");
	for(int i=2; i<=resar; i++, puts(""))
	{
		printf("%3d", i-1);
		for(int j=2; j<=resar; j++)
		{
			printf("%3d", res[i][j]);
		}
	}
	return 0;
}

void go(int x,int y, int dx, int dy)
{
	int ag=0;
	while(ag<10000)
	{
		if(Map[x][y]) ag++;
		Map[x][y] = ans;
		if(x+dx>N || x+dx<1) dx=-dx;
		if(y+dy>M || y+dy<1) dy=-dy;
		x += dx;
		y += dy;
	}
}

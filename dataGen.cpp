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
#include <ctime>
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) (a*a)

int lrand(int opt, int MOD)
{
	int l=0, r=-1,h;
	while(l>=r)
	{
		l=rand()%MOD;
		r=rand()%MOD;
	}
	h=rand()%MOD;
	if(opt) printf("%d %d %d %d\n", l, h, r, h);
	else printf("%d %d %d %d\n", h, l, h, r);
}

int prand(int MOD)
{
	int x=rand()%MOD, y=rand()%MOD;
	printf("%d %d\n", x, y);
}

int main()
{
	freopen("in.txt", "w", stdout);
	
	srand(time(0));
	int T=1;
//	printf("%d", T);
	for(int ck=1; ck<=T; ck++)
	{
		int N=5, M=2, MOD=10;
		printf("%d %d\n", N, M);
		for(int i=0; i<N; i++)
		{
			lrand(rand()%2, MOD);
		}
		for(int i=0; i<M; i++)
		{
			prand(MOD);
		}
	}
	return 0;
}


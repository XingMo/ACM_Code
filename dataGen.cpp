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

const int maxn=1e5+10;
int inpt[maxn];

int main()
{
	freopen("in.txt", "w", stdout);
	
	srand(time(0));
	int T=1;
	printf("%d\n", T);
	for(int ck=1; ck<=T; ck++)
	{
		int N=10000, M=20000, MOD=100;
		printf("%d %d\n", N, M);
		for(int i=2; i<=N; i++)
		{
			int u=rand()%(i-1)+1;
			printf("%d %d %d\n", u, i, rand()%MOD+1);
		}
		for(int i=0; i<M; i++)
		{
			int opt=rand()%3+1,a,b;
			if(opt==1)
			{
				printf("%d %d %d\n", opt, rand()%(N-1)+1, rand()%MOD);
			}
			else
			{
				a=0,b=0;
				while(a==b)
				{
					a=rand()%N+1;
					b=rand()%N+1;
				}
				printf("%d %d %d\n", opt, a, b);
			}
		}
	}
	return 0;
}


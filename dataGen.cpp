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

const int maxn=2e5+10;
int inpt[maxn];
bool ban[maxn];

void swapii(int&,int&);

int main()
{
	freopen("in.txt", "w", stdout);
	
	srand(time(0));
	int T=1;
//	printf("%d", T);
	for(int ck=1; ck<=T; ck++)
	{
		CLR(ban);
		int N=20,M=10;
		printf("%d %d\n", N, M);
		for(int i=1; i<=N; i++) inpt[i]=i;
		for(int i=1; i<=5*N; i++)
		{
			int x=0,y=0;
			while(x==y)
			{
				x=rand()%N+1, y=rand()%N+1;
			}
			swapii(inpt[x], inpt[y]);
		}
		
		for(int i=1; i<=N; i++) printf("%d\n", inpt[i]);
		ban[0]=1;
		for(int i=1; i<=M; i++)
		{
			int x=0;
			while(ban[x]) x=rand()%N+1;
			printf("%d\n", inpt[x]);
			ban[x]=1;
		}
	}
	return 0;
}

void swapii(int &x, int &y)
{
	x^=y;
	y^=x;
	x^=y;
}

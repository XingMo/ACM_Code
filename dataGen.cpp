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

int main()
{
	freopen("in.txt", "w", stdout);
	
	srand(time(0));
	int T=1;
	printf("%d\n", T);
	for(int ck=1; ck<=T; ck++)
	{
		int N=1e5, M=1e5;
		int col=500;
		printf("%d %d\n", N, M);
		for(int i=1; i<=N; i++) printf("%d ", rand()%col); puts("");
		for(int i=1; i<=N; i++)
		{
			int l=0, r=-1;
			while(l>=r)
			{
				l=rand()%N;
				r=rand()%N;
			}
			int opt=rand()%2+1, val=rand()%col;
			printf("%d %d %d %d\n", opt, l, r, val);
		}
	}
	return 0;
}


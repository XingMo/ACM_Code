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
//	printf("%d\n", T);
	for(int ck=1; ck<=T; ck++)
	{
		int N=10, MOD=10;
		printf("%d\n", N);
		for(int i=1; i<=N; i++) printf("%d ", rand()%N+1);
		puts("");
	}
	return 0;
}


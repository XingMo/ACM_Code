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
		const int maxn=5e4;
		printf("%d %d\n", maxn, maxn-1);
		int ex=1;
		for(int i=2; i<=maxn; i++) printf("1 %d %d %d\n", i, ex++, rand()%maxn);
	}
	return 0;
}


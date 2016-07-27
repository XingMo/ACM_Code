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

int R,C,N;
char Map[200][200];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		scanf("%d%d%d", &R, &C, &N);
		for(int i=1; i<=R; i++) for(int j=1; j<=C; j++) Map[i][j]='.';
		for(int i=1; i<=N; i++)
		{
			int r0,r1,c0,c1;
			char chr;
			scanf("%d%d%d%d %c", &r0, &c0, &r1, &c1, &chr);
			for(int i=r0; i<=r1; i++) for(int j=c0; j<=c1; j++) Map[i][j]=chr;
		}
		for(int i=1; i<=R; i++) {for(int j=1; j<=C; j++) putchar(Map[i][j]); puts("");}
	}
	return 0;
}


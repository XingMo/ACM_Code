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

char col[7]={'R','O','Y','G','B','I','V'};
char str[150];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int N, np=0;
	scanf("%d", &N);
	for(int i=0; i<7; i++) putchar(col[i%7]);
	N-=7;
	for(int i=0; i<N; i++)
	{
		putchar(col[np+3]);
		np = (np+1)%4;
	}
	return 0;
}


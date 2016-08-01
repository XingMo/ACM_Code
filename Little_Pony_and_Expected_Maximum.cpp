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

DBL Pow(DBL,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int N,M;
	while(~scanf("%d%d", &M, &N))
	{
		DBL ans=0;
		for(int i=1; i<=M; i++)
		{
			DBL pk=(DBL)(i-1)/M;
			ans += (DBL)i*( Pow(1.0/M + pk, N) - Pow(pk, N));
		}
		printf("%.6f\n", ans);
	}
	return 0;
}

DBL Pow(DBL x, int n)
{
	DBL res=1.0;
	while(n)
	{
		if(n&1) res = x*res;
		x=x*x;
		n>>=1;
	}
	return res;
}

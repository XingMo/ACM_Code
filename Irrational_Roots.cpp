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
#include <complex>
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define SQR(a) ((a)*(a))
#define PCUT puts("\n----------")

int N;
LL C[10];

LL fun(int x, int flr)
{
	LL res = 0;
	for(int i=0; i<=N-flr; i++)
	{
		LL now = C[i];
		if(flr) for(int j=0; j<flr; j++) now *= N-i-j;
		for(int j=1; j<=N-i-flr; j++) now *= x;
		res += now;
	}
	if(!res) return 1+fun(x, flr+1);
	else return 0;
}

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		C[0] = 1;
		for(int i=1; i<=N; i++) cin >> C[i];
		int tot = N;
		for(int i=-10; i<=10; i++)
		{
			tot -= fun(i,0);
		}
		printf("%d\n", tot);
	}
	return 0;
}


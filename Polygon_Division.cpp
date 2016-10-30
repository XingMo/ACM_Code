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

const int maxn=5e3+10;
ULL F[maxn], Cat[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	F[0] = F[1] = F[2] = F[3] = 1;
	F[4] = 3;
	Cat[0] = Cat[1] = Cat[2] = Cat[3] = 1;
	Cat[4] = 2;
	for(int n=5; n<=5000; n++)
	{
		for(int i=1; i<=n-2; i++) F[n] += F[i+1]*F[n-i];
		Cat[n] = F[n];
		for(int i=2; i<=n-2; i++) F[n] += Cat[n-i+1]*F[i];
	}
	int N;
	while(~scanf("%d", &N)) printf("%llu\n", F[N]);
	return 0;
}


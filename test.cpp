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

int F[110], G[110];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	
	for(int i=1; i<=100; i++)
	{
		for(int j=0; j<i; j++)
		{
			for(int k=0; k<i; k++) if((j*k)%i != 0) F[i]++;
		}
	}
//	for(int i=1; i<=100; i++) printf("%d: %d\n", i, F[i]);
	for(int i=1; i<=100; i++)
	{
		int lim = sqrt(i);
		for(int j=1; j<lim; j++) if(i%j == 0)
		{
			G[i] += F[j] + F[i/j];
		}
		if(lim*lim==i) G[i] += F[lim];
		else if(i%lim == 0) G[i] += F[lim] + F[i/lim];
	}
	for(int i=1; i<=100; i++) printf("%d: %d\n", i, G[i]);
	return 0;
}


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

const int maxn=1826+10;
int N, day[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		CLR(day);
		for(int i=1,l,r; i<=N; i++)
		{
			scanf("%d%d", &l, &r);
			for(int j=l; j<=r; j++) day[j] = 1;
		}
		for(int i=1; i<maxn; i++) day[i] += day[i-1];
		bool ok=1;
		for(int i=180; i<maxn; i++)
		{
			if(day[i]-day[i-180] > 90) {ok=0; break;}
		}
		puts(ok?"Yes":"No");
	}
	return 0;
}


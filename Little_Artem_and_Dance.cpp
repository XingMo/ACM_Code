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

const int maxn=1e6+10;
int N,Q;
int ans[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &Q))
	{
		LL p0=0, p1=1;
		for(int q=0, opt, x; q<Q; q++)
		{
			scanf("%d", &opt);
			if(opt==1)
			{
				scanf("%d", &x);
				p0 += x;
				p1 += x;
			}
			if(opt==2)
			{
				if(p0&1) p0--;
				else p0++;
				if(p1&1) p1--;
				else p1++;
			}
//			printf("P0:%lld P1:%lld\n", p0+1, p1+1);
		}
		for(int i=0,id; i<N; i++)
		{
			if(i&1) id = int(((p1+i-1)%N+N)%N)+1;
			else id = int(((p0+i)%N+N)%N)+1;
			ans[id] = i+1;
		}
		for(int i=1; i<=N; i++) printf("%d ", ans[i]);
		puts("");
	}
	return 0;
}


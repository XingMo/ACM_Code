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
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) ((a)*(a))

const int maxn=1e5+10;
int N;
struct data
{
	int t,d;
	bool operator < (const data &v) const {return t*v.d < v.t*d;}
} inpt[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		for(int i=0; i<N; i++) scanf("%d%d", &inpt[i].t, &inpt[i].d);
		sort(inpt, inpt+N);
		LL nt=0, ans=0;
		for(int i=0; i<N; i++)
		{
			ans+=nt*inpt[i].d;
			nt+=2*inpt[i].t;
		}
		printf("%lld\n", ans);
	}
	return 0;
}


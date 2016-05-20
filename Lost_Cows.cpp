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
#define Sqr(a) (a*a)

const int maxn=8e3+10;
struct data{int v,t;};
int N;
data inpt[maxn];
int ans[maxn];

bool dacmp(const data& u, const data& v)
{
	if(u.v!=v.v) return u.v < v.v;
	return u.t > v.t;
}

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		inpt[0].t=0; inpt[0].v=0;
		for(int i=1; i<N; i++)
		{
			inpt[i].t=i;
			scanf("%d", &inpt[i].v);
		}
		sort(inpt, inpt+N, dacmp);
		for(int i=0; i<N; i++)
		{
			ans[inpt[i].t]=i+1;
		}
		for(int i=0; i<N; i++) printf("%d\n", ans[i]);
	}
	return 0;
}


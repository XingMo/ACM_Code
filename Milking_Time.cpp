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

const int maxn=1e6+10, maxm=1e3+10;
int N,M,R;
struct data
{
	int l,r,w;
	bool operator < (const data &v) const {return r<v.r;}
} inpt[maxm];
int dp[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d%d", &N, &M, &R))
	{
		for(int i=0; i<M; i++) scanf("%d%d%d", &inpt[i].l, &inpt[i].r, &inpt[i].w);
		sort(inpt, inpt+M);
		
		CLR(dp);
		int np=0;
		for(int nt=1; nt<=N; nt++)
		{
			dp[nt]=dp[nt-1];
			while(np<M && inpt[np].r<=nt)
			{
				int l=inpt[np].l-R;
				if(l<=0) dp[nt] = max(dp[nt], inpt[np].w);
				else dp[nt] = max(dp[nt], inpt[np].w+dp[l]);
				np++;
			}
		}
		
		printf("%d\n", dp[N]);
	}
	return 0;
}


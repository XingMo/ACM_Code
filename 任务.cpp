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

const int maxn=2e3+10,maxc=2e3*3e3+10;
int N;
int dp[maxc];
int W[maxn],V[maxn];
int sumw,sumv;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		scanf("%d", &N);
		sumw=0; sumv=0;
		for(int i=1; i<=N; i++)
		{
			scanf("%d%d", &W[i], &V[i]);
			sumw+=W[i];
			sumv+=V[i];
		}
		MST(dp,0x3f);
		dp[0]=sumv;
		for(int i=1; i<=N; i++)
		{
			for(int j=maxc; j>=W[i]; j--)
			{
				dp[j]=min(dp[j], dp[j-W[i]]-V[i]);
			}
		}
		int ans;
		for(int i=0; i<maxc; i++) if(dp[i]<=i) {ans=i;break;}
		printf("%d\n", ans);
	}
	return 0;
}

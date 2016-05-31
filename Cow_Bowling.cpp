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

const int maxn=350+10;
int N;
int inpt[maxn];
int dp[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		CLR(inpt); CLR(dp);
		for(int i=0; i<N; i++)
		{
			for(int j=0; j<=i; j++) scanf("%d", &inpt[j]);
			for(int j=i; j>0; j--) dp[j]=max(dp[j], dp[j-1])+inpt[j];
			dp[0]+=inpt[0];
		}
		int ans=0;
		for(int i=0; i<N; i++) ans=max(ans, dp[i]);
		printf("%d\n", ans);
	}
	return 0;
}


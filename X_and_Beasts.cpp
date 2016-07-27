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

int N;
int inpt[110];
int dp[110];

int cal(int);

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
		MST(dp,-1);
		int ans=0;
		for(int i=0; i<N; i++)
		{
			scanf("%d", &inpt[i]);
			int now=cal(inpt[i]);
			dp[i]=now;
			for(int j=0; j<i; j++)
			{
				if(inpt[j]<inpt[i]) dp[i]=max(dp[i], dp[j]+now);
			}
			ans=max(dp[i], ans);
		}
		printf("%d\n", ans);
	}
	return 0;
}

int cal(int x)
{
	int cnt=0;
	while((x&1)==0)
	{
		cnt++;
		x>>=1;
	}
	return cnt;
}

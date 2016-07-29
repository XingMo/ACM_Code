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
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define SQR(a) ((a)*(a))
#define PCUT puts("----------")

const int maxn=100+10;
int N;
int A[maxn];
DBL dp[maxn];

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
		for(int i=1; i<=N; i++) scanf("%d", &A[i]);
		dp[N] = A[N];
		for(int i=N-1; i>=1; i--)
		{
			dp[i] = 0;
			int cnt=min(N-i, 6);
			for(int j=1; j<=cnt; j++) dp[i] += dp[i+j];
			dp[i] = dp[i]/cnt + A[i];
		}
		printf("Case %d: %.7f\n", ck, dp[1]);
	}
	return 0;
}


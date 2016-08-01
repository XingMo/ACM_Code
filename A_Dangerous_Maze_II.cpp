/*
Unaccepted
*/
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

DBL A[110];
DBL dp[110];

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
		int N,K;
		scanf("%d%d", &N, &K);
		int cnt=0;
		DBL sum=0;
		for(int i=1,x; i<=N; i++)
		{
			scanf("%d", &x);
			A[i] = x;
			sum += abs(x);
			if(x>0) cnt++;
		}
		printf("Case %d: ", ck);
		if(!cnt) {puts("-1"); continue;}
		K = min(N-cnt, K);
		dp[K] = sum / cnt;
		for(int i=K-1; i>=0; i--)
		{
			dp[i] = (sum + dp[i+1]*(N-cnt-i))/(N-i);
		}
		printf("%.7f\n", dp[0]);
	}
	return 0;
}


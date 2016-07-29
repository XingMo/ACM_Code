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

const int maxc = 1e4+10;
const DBL eps = 1e-6;
int N;
DBL P;
DBL dp[maxc];

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
		scanf("%lf%d", &P, &N);
		CLR(dp);
		dp[0]=1;
		for(int i=0; i<N; i++)
		{
			int m; DBL p;
			scanf("%d%lf", &m, &p);
			for(int j=maxc-1; j>=m; j--) dp[j] = max(dp[j], dp[j-m]*(1-p));
		}
		for(int i=maxc-1; i>=0; i--) if((1-dp[i]) < P || abs((1-dp[i])-P)<eps)
		{
			printf("Case %d: %d\n", ck, i);
			break;
		}
	}
	return 0;
}


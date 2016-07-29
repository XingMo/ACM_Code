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

const int maxn=1e5+10;
const int MOD=1000000007;
char str[maxn], patn[maxn];
int fail[maxn];
int dp[maxn];

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
		scanf(" %s %s", str+1, patn+1);
		int slen = strlen(str+1), plen = strlen(patn+1);
		fail[1] = fail[2] = 1;
		for(int i=2; i<=plen; i++)
		{
			int p = fail[i];
			while(p!=1 && patn[p] != patn[i]) p = fail[p];
			fail[i+1] = patn[i]==patn[p]?p+1:1;
		}
		
		CLR(dp);
		dp[0]=1;
		int np=1;
		for(int i=1; i<=slen; i++)
		{
			dp[i] = dp[i-1];
			while(np!=1 && str[i] != patn[np]) np = fail[np];
			if(str[i]==patn[np]) np++;
			if(np>plen)
			{
				dp[i] = (dp[i]+dp[i-plen])%MOD;
				np = fail[np];
			}
		}
		printf("Case #%d: %d\n", ck, dp[slen]);
	}
	return 0;
}


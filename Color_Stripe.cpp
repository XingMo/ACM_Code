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
#define PCUT puts("\n----------")

const int maxn=5e5+10;
char str[maxn];
int N,K;
int dp[maxn][26];
int tr[maxn][26];
char buff[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d %s", &N, &K, str))
	{
		for(int i=0; i<K; i++) dp[0][i]=1;
		dp[0][str[0]-'A'] = 0;
		for(int i=1; i<N; i++)
		{
			for(int j=0; j<K; j++)
			{
				dp[i][j] = N+10;
				for(int k=0; k<K; k++) if(j!=k)
				{
					if(dp[i][j] > dp[i-1][k])
					{
						dp[i][j] = dp[i-1][k];
						tr[i][j] = k;
					}
				}
				if(j!=str[i]-'A') dp[i][j]++;
			}
		}
		int ans = N+10, st=0;
		for(int i=0; i<K; i++) if(ans > dp[N-1][i])
		{
			ans = dp[N-1][i];
			st = i;
		}
		buff[N] = 0;
		for(int i=N-1; i>=0; i--)
		{
			buff[i] = st+'A';
			st = tr[i][st];
		}
		printf("%d\n%s\n", ans, buff);
	}
	return 0;
}


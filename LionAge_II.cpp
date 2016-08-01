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

const int NINF=0xc0c0c0c0;
int K;
char str[110];
int dp[2][26][110];
int bonus[26][26];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%s%d", str, &K))
	{
		CLR(bonus); 
		int N;
		scanf("%d", &N);
		for(int i=0; i<N; i++)
		{
			char a,b; int c;
			scanf(" %c %c%d", &a, &b, &c);
			bonus[a-'a'][b-'a'] = c;
		}
		int len = strlen(str);
		MST(dp,0xc0);
		dp[0][str[0]-'a'][K] = 0;
		if(K) for(int i=0; i<26; i++) if(i!=str[0]-'a') dp[0][i][K-1] = 0; 
		for(int i=1; i<len; i++)
		{
			int cur=i&1, las=(i-1)&1;
			MST(dp[cur],0xc0);
			for(int t=K; t>=0; t--)
			{
				for(int j=0; j<26; j++) if(dp[las][j][t] != NINF)
				{
					dp[cur][str[i]-'a'][t] = max(dp[cur][str[i]-'a'][t], dp[las][j][t] + bonus[j][str[i]-'a']);
					if(t<=0) continue;
					for(int k=0; k<26; k++) if(k!=str[i]-'a')
					{
						int cost = dp[las][j][t] + bonus[j][k];
						if( dp[cur][k][t-1] < cost)
						{
							dp[cur][k][t-1] = cost;
						}
					}
				}
			}
		}
		int ans = -1e9;
		for(int i=0; i<26; i++) for(int j=0; j<=K; j++) ans = max(ans, dp[(len-1)&1][i][j]);
		cout << ans << endl;
	}
	return 0;
}


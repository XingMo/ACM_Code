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

const int INF=0x3f3f3f3f;
int dp[1010][1010];
int tr[1010][1010];
int tdp[1010][2];
int tpo[1010][2];
int res[1010];
char str[1010];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int N;
	scanf("%d %s", &N, str+2);
	for(int i=1; i<=N; i++) {dp[1][i]=i; tdp[i][0]=1, tpo[i][0]=1; tdp[i][1]=i, tpo[i][1]=i;}
	for(int i=2; i<=N; i++)
	{
		MST(dp[i],0x3f);
		if(str[i]=='=') 
		{
			for(int j=1; j<=N; j++)
			{
				dp[i][j] = dp[i-1][j] + j;
				tr[i][j] = j;
			}
		}
		else
		{
			for(int j=1; j<=N; j++)
			{
				if(str[i]=='L' && j<N) 
				{
					dp[i][j] = tdp[j+1][1] + j;
					tr[i][j] = tpo[j+1][1];
				}
				if(str[i]=='R' && j>1) 
				{
					dp[i][j] = tdp[j-1][0] + j;
					tr[i][j] = tpo[j-1][0];
				}
			}
		}
		tdp[1][0] = dp[i][1], tpo[1][0] = 1;
		tdp[N][1] = dp[i][N], tpo[N][1] = N;
		for(int j=2; j<=N; j++)
		{
			tdp[j][0] = dp[i][j], tpo[j][0] = j;
			if(tdp[j-1][0] <= tdp[j][0])
			{
				tdp[j][0] = tdp[j-1][0];
				tpo[j][0] = tpo[j-1][0];
			}
		}
		for(int j=N-1; j>=1; j--)
		{
			tdp[j][1] = dp[i][j], tpo[j][1] = j;
			if(tdp[j+1][1] <= tdp[j][1])
			{
				tdp[j][1] = tdp[j+1][1];
				tpo[j][1] = tpo[j+1][1];
			}
		}
//		printf("%dth: %c\n", i, str[i]);
//		for(int j=1; j<=N; j++) printf("%d ", tdp[j][0]); puts("");
//		for(int j=1; j<=N; j++) printf("%d ", tpo[j][0]); puts("");
//		for(int j=1; j<=N; j++) printf("%d ", dp[i][j]); puts("");
	}
	int tmax=INF, p=1;
	for(int i=1; i<=N; i++) if(dp[N][i]<tmax) { tmax=dp[N][i], p=i;}
//	cout << tmax << endl;
	for(int i=1; i<=N; i++)
	{
		res[i] = p;
		p = tr[N-i+1][p];
	}
	for(int i=N; i>=1; i--) printf("%d ", res[i]);
	puts("");
	return 0;
}


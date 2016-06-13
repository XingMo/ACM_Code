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

const int maxn=400+10, maxh=40000+10;
struct data
{
	int h,a,c;
	bool operator < (const data &v) const {return a < v.a;}
};
int N;
data inpt[maxn];
int dp[2][maxh];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		for(int i=1; i<=N; i++) scanf("%d%d%d", &inpt[i].h, &inpt[i].a, &inpt[i].c);
		sort(inpt+1, inpt+1+N);
		
		MST(dp,-1);
		dp[0][0]=0;
		for(int i=1; i<=N; i++)
		{
			int cur=i&1, las=(i-1)&1;
			MST(dp[cur],-1);
			for(int h=0; h<=inpt[i].a; h++)
			{
				if(~dp[las][h]) dp[cur][h] = inpt[i].c;
				else if( h>=inpt[i].h && dp[cur][h-inpt[i].h]>0 ) 
					dp[cur][h] = dp[cur][h-inpt[i].h]-1;
			}
		}
		for(int i=maxh-1; i>=0; i--)
		{
			if(~dp[N&1][i])
			{
				printf("%d\n", i);
				break;
			}
		}
	}
	return 0;
}


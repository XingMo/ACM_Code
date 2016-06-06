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

const int MOD=1e8;
int N,M,fmask;
int Map[20];
int dp[20][1<<12];

bool judge(int,int);
bool judge2(int);
void bpri(int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		fmask=(1<<M)-1;
		CLR(Map); CLR(dp);
		for(int i=1; i<=N; i++)
		{
			for(int j=0; j<M; j++)
			{
				int x;
				scanf("%d", &x);
				Map[i]<<=1;
				Map[i]|=x;
			}
		}
		for(int i=0; i<=fmask; i++) if(judge2(i) && judge(Map[1],i)) dp[1][i]=1;
		
		for(int i=2; i<=N; i++)
		{
			for(int j=0; j<=fmask; j++)
			{
				if(!dp[i-1][j]) continue;
				for(int k=0; k<=fmask; k++)
				{
					if(!judge2(k)) continue;
					if( !judge(~j,k) || !judge(Map[i],k) ) continue;
					dp[i][k]=(dp[i][k]+dp[i-1][j])%MOD;
				}
			}
		}
		
		int ans=0;
		for(int i=0; i<=fmask; i++) ans=(ans+dp[N][i])%MOD;
		printf("%d\n", ans);
	}
	return 0;
}

bool judge(int x, int y)
{
	for(int i=0; i<M; i++)
	{
		int ns=1<<i;
		if( (y&ns) && !(x&ns)) return 0;
	}
	return 1;
}

bool judge2(int x)
{
	int ns=3;
	for(int i=1; i<M; i++)
	{
		if((x&ns) == ns) return 0;
		ns<<=1;
	}
	return 1;
}

void bpri(int x)
{
	int stak[20];
	for(int i=0; i<M; i++)
	{
		if(x&(1<<i)) stak[i]=1;
		else stak[i]=0;
	}
	for(int i=M-1; i>=0; i--) putchar(stak[i]+'0');
	puts("");
}

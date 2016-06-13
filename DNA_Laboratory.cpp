/*
POJ - 1795
求出一个最短的字符串，使其包含所有给定的 N个字符串
并输出字典序最小的那一个

首先把字符串中相互包含的去掉
要注意特判两个字符串相等的情况
然后预处理出两个字符串相接最短需要增加的长度
然后状压DP，dp[i][mask]表示
当前末尾字符串是 i，已用字符串集合为 mask
然后输出的时候尽量先输出字典序最小的即可
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
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) ((a)*(a))

const int INF=0x3f3f3f3f;
int N, fmask;

int tlen[20];
char inpt[20][110];
int cost[20][20];
int dp[20][1<<16];

int ans;
string res;

void init();
void output(int,int,int);
int DP(int,int);

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
		for(int i=1; i<=N; i++) scanf(" %s", inpt[i]);
		init();
		
		ans=DP(0,0);
//		printf("%d\n", ans);
		res="";
		
		printf("Scenario #%d:\n", ck);
		output(0,0,0);
		cout << res;
		puts("\n");
	}
	return 0;
}

int DP(int u, int mask)
{
	if(mask==fmask) return dp[u][mask]=0;
	if(~dp[u][mask]) return dp[u][mask];
//	printf("%d %d\n", u, mask);
	dp[u][mask]=INF;
	for(int v=1; v<=N; v++)
	{
		if(mask&(1<<v-1)) continue;
		dp[u][mask] = min(dp[u][mask], DP(v,mask|(1<<v-1))+cost[u][v]);
	}
	return dp[u][mask];
}

void output(int np, int u, int m)
{
	if(m==fmask) return;
	
	string nstr="zzzzz";
	int tv=0;
	for(int v=1; v<=N; v++)
	{
		if( (m&(1<<v-1)) ||  (dp[u][m] != dp[v][m|(1<<v-1)] + cost[u][v])) continue;
		string temp="";
		for(int j=0; j<cost[u][v]; j++) temp += inpt[v][ tlen[v]-cost[u][v] + j];
		if(temp < nstr) {tv=v; nstr=temp;}
	}
	res+=nstr;
	output(np+cost[u][tv], tv, m|(1<<tv-1));
	return;
}

void init()
{
	bool ban[20]={0};
	for(int i=1; i<=N; i++)
	{
		if(ban[i]) continue;
		for(int j=1; j<=N; j++)
		{
			if(i==j) continue;
			if(strstr(inpt[i], inpt[j]) != NULL) ban[j]=1;
		}
	}
	int np=0;
	for(int i=1; i<=N; i++)
	{
		if(!ban[i])
		{
			np++;
			tlen[np]=strlen(inpt[i]);
			for(int j=0; j<tlen[np]; j++) inpt[np][j]=inpt[i][j];
		}
	}
	N=np;
	
	CLR(cost); MST(dp,-1);
	fmask=(1<<N)-1;

	for(int i=1; i<=N; i++) cost[0][i] = tlen[i];
	for(int i=1; i<=N; i++)
	{
		for(int j=1; j<=N; j++)
		{
			if(i==j) continue;
			cost[i][j]=tlen[j];
			for(int k=0; k<tlen[i]; k++)
			{
				int nlen=min( tlen[i]-k, tlen[j] );
				if(!strncmp( inpt[i]+k, inpt[j], nlen)) { cost[i][j] = tlen[j]-nlen; break;}
			}
		}
	}
}

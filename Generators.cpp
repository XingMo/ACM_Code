/*
Codeforces - Gym100851G
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
#include <complex>
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

const int maxn=1e4+10;
int N,K;
int tmax[2][maxn];
int pos[2][maxn];
int outp[maxn];
bool vis[1010];
void gen(int,int,int,int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	#ifndef LOCAL
	freopen("generators.in", "r", stdin);
	freopen("generators.out", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &K))
	{
		MST(tmax,-1); CLR(pos);
		for(int i=0,x,a,b,c; i<N; i++)
		{
			scanf("%d%d%d%d", &x, &a, &b, &c);
			gen(i,x,a,b,c);
		}
		int ans=0;
		for(int i=0; i<N; i++)
		{
			ans += tmax[0][i];
			outp[i] = pos[0][i];
		}
		if(ans%K==0)
		{
			int tem=-1, tp=0;
			for(int i=0; i<N; i++) if(~tmax[1][i])
			{
				if(ans-tmax[0][i]+tmax[1][i] > tem)
				{
					tem = ans-tmax[0][i]+tmax[1][i];
					tp = i;
				}
			}
			ans = tem;
			outp[tp] = pos[1][tp];
		}
		if(ans==-1) puts("-1");
		else
		{
			printf("%d\n", ans);
			for(int i=0; i<N; i++) printf("%d ", outp[i]);
			puts("");
		}
	}
	return 0;
}

void gen(int np, int x, int a, int b, int c)
{
	CLR(vis);
	vis[x]=1;
	tmax[0][np] = x; pos[0][np] = 0;
	int tp=0;
	for(int now=(a*x+b)%c; !vis[now]; now=(a*now+b)%c)
	{
		tp++;
		vis[now]=1;
		if(now > tmax[0][np]) tmax[0][np] = now, pos[0][np] = tp;
	}
	if(x%K != tmax[0][np]%K) tmax[1][np] = x, pos[1][np] = 0;
	CLR(vis);
	tp=0;
	for(int now=(a*x+b)%c; !vis[now]; now=(a*now+b)%c)
	{
		tp++;
		vis[now]=1;
		if((now%K != tmax[0][np]%K) && now > tmax[1][np])
		{
			tmax[1][np] = now, pos[1][np] = tp;
		}
	}
}

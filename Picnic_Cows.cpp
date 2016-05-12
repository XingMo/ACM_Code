#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
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
#define Sqr(a) (a*a)

const int maxn=4e5+10;
const LL INF=0x3f3f3f3f3f3f3f3f;
int N,M;
LL inpt[maxn];
LL psum[maxn];
LL que[maxn];
LL dp[maxn];

LL Up(int,int);
LL Down(int,int);
LL Dp(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		for(int i=1; i<=N; i++) scanf("%lld", &inpt[i]);
		sort(inpt+1,inpt+1+N);
		for(int i=1; i<=N; i++) psum[i]=psum[i-1]+inpt[i];
		int qhead=0,qtail=1;
		que[0]=0;
		CLR(dp);
		for(int i=1; i<=N; i++)
		{
			//尽可能使斜率最大化
			while(qhead+1<qtail && Up(que[qhead], que[qhead+1]) <= i*Down(que[qhead], que[qhead+1]))
				qhead++;
			dp[i]=Dp(i,que[qhead]);
			int j=i-M+1;
			if(j<M) continue;
			//去掉上凸点
			while(qhead+1<qtail && 
				Up(que[qtail-1], j)*Down(que[qtail-2], que[qtail-1]) <= Up(que[qtail-2], que[qtail-1])*Down(que[qtail-1], j))
				qtail--;
			que[qtail++]=j;
		}
		printf("%lld\n", dp[N]);
	}
	return 0;
}

LL Up(int k, int j)
{
	return dp[j]-psum[j]+inpt[j+1]*j-(dp[k]-psum[k]+inpt[k+1]*k);
}

LL Down(int k, int j)
{
	return inpt[j+1]-inpt[k+1];
}

LL Dp(int i, int j)
{
	return dp[j]+psum[i]-psum[j]-inpt[j+1]*(i-j);
}

/*
SCU - 4509
使用若干条线段，覆盖坐标轴上的 N个点
定义两点的距离为 dist(i,j)，则覆盖 [i,j]的代价为
cost(i,j) = W + dist(i,j)^2

斜率优化入门题，与 HDU - Print Article一致

*/
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

const int maxn=2e5+10;
int N,W;
LL inpt[maxn];
LL dp[maxn];
int que[maxn];

LL Up(int,int);
LL Down(int,int);

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
		scanf("%d%d", &N, &W);
		for(int i=1; i<=N; i++) scanf("%lld", &inpt[i]);
		sort(inpt+1,inpt+1+N);
		N=unique(inpt+1,inpt+1+N)-(inpt+1);
		dp[0]=0; dp[1]=W;
		int head=0,tail=1;
		que[0]=1;
		for(int i=2; i<=N; i++)
		{
			while(head+1<tail && 
				Up(que[head], que[head+1]) <= inpt[i]*Down(que[head], que[head+1]))
				head++;
			dp[i]=dp[i-1]+W;
			dp[i]=min(dp[i], dp[que[head]-1]+Sqr((inpt[i]-inpt[que[head]]))+W);
			while(head+1<tail && 
				Up(que[tail-1], i)*Down(que[tail-2], que[tail-1]) <= Up(que[tail-2], que[tail-1])*Down(que[tail-1], i))
				tail--;
			que[tail++]=i;
		}
		printf("%lld\n", dp[N]);
	}
	return 0;
}

LL Up(int k, int j)
{
	return dp[j-1]+Sqr(inpt[j])-(dp[k-1]+Sqr(inpt[k]));
}

LL Down(int k, int j)
{
	return 2*(inpt[j]-inpt[k]);
}

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

const int maxn=2e5+10, MOD=1e9+7;
int N;
int A[maxn];
int pow2[maxn];
int vis[maxn], sk[maxn];

int Go(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	pow2[0]=1;
	for(int i=1; i<maxn; i++) pow2[i]=(pow2[i-1]<<1)%MOD;
	while(~scanf("%d", &N))
	{
		CLR(vis);
		for(int i=1; i<=N; i++) scanf("%d", &A[i]);
		int ans=1,tot=N,time=0;
		for(int i=1; i<=N; i++) if(!vis[i])
		{
			int res = Go(i,++time);
			if(~res)
			{
				ans = (LL)ans*(pow2[res]-2)%MOD;
				tot -= res;
			}
		}
		ans = (LL)ans*pow2[tot]%MOD;
		printf("%d\n", (ans+MOD)%MOD);
	}
	return 0;
}

int Go(int np, int time)
{
	int top=0;
	while(!vis[np])
	{
		vis[np] = time;
		sk[top++] = np;
		np = A[np];
	}
	if(vis[np]==time)
	{
		int cnt=0;
		while(sk[top-1] != np)
		{
			top --;
			cnt ++;
		}
		return cnt+1;
	}
	else return -1;
}

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

const int maxn=400;
int N,M;
int inpt[maxn];
int dp[5][41][41][41];
int mcnt[5];

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
		int mtot=0;
		MST(dp,-1);
		CLR(mcnt);
		scanf("%d%d", &N, &M);
		for(int i=1; i<=N; i++) scanf("%d", &inpt[i]);
		for(int i=1; i<=M; i++) 
		{
			int x;
			scanf("%d", &x);
			mcnt[x]++;
			mtot++;
		}
		dp[1][0][0][0]=0;
		for(int i=1; i<N; i++)
		{
			for(int m2=0; m2<=mcnt[2]; m2++)
			{
				for(int m3=0; m3<=mcnt[3]; m3++)
				{
					for(int m4=0; m4<=mcnt[4]; m4++)
					{
						if(dp[i%5][m2][m3][m4]==-1) continue;
//						if(2*m2+3*m3+4*m4+1>i) break;
						int m1=i-2*m2-3*m3-4*m4-1;
						if(m1<0 || m1>mcnt[1]) continue;
						int now=dp[i%5][m2][m3][m4]+inpt[i];
						bool nt1=0,nt2=0,nt3=0,nt4=0;
						if(m1<mcnt[1]) dp[(i+1)%5][m2][m3][m4]  =max(dp[(i+1)%5][m2][m3][m4],   now), nt1=1;
						if(m2<mcnt[2]) dp[(i+2)%5][m2+1][m3][m4]=max(dp[(i+2)%5][m2+1][m3][m4], now), nt2=1;
						if(m3<mcnt[3]) dp[(i+3)%5][m2][m3+1][m4]=max(dp[(i+3)%5][m2][m3+1][m4], now), nt3=1;
						if(m4<mcnt[4]) dp[(i+4)%5][m2][m3][m4+1]=max(dp[(i+4)%5][m2][m3][m4+1], now), nt4=1;
//						printf("%d %d %d %d %d %d\n", i, m1, m2, m3, m4, now);
//						if(nt1) puts("dp-1");
//						if(nt2) puts("dp-2");
//						if(nt3) puts("dp-3");
					}
				}
			}
			MST(dp[i%5], -1);
		}
		printf("%d\n", inpt[N]+dp[N%5][mcnt[2]][mcnt[3]][mcnt[4]]);
	}
	return 0;
}


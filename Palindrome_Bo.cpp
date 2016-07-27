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

const int maxn = 5e3+10;
const int MOD = 1e9+7;
struct Discrete
{
	int ais[maxn],siz;
	void init(){ sort(ais,ais+siz); siz=unique(ais,ais+siz)-ais;}
	void add(int _n){ais[siz++]=_n;}
	int id(int _n){return lower_bound(ais,ais+siz,_n)-ais+1;}
};
int N;
int A[maxn];
Discrete D;
Pii dp[maxn][maxn];
int pre[maxn], nxt[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		CLR(dp);
		D.siz=0;
		for(int i=1; i<=N; i++)
		{
			scanf("%d", &A[i]);
			D.add(A[i]);
		}
		D.init();
		for(int i=1; i<=N; i++) A[i] = D.id( A[i] );
		
		MST(nxt, -1);
		for(int i=N; i>=1; i--)
		{
			MST(pre,-1);
			dp[i][i].first = 1;
			dp[i][i].second = 1;
			pre[ A[i] ] = i;
			
			Pii tem(0,1);
			for(int j=i+1; j<=N; j++)
			{
				if( A[i]==A[j] )
				{
					dp[i][j] = tem;
					dp[i][j].first += 2;
				}
				if( A[j]<=A[i] && dp[ nxt[A[j]] ][ j ].first >= tem.first)
				{
					if( dp[ nxt[A[j]] ][ j ].first > tem.first )
					{
						tem = dp[ nxt[A[j]] ][ j ];
					}
					else //去重
					{
						tem.second = (tem.second + dp[ nxt[A[j]] ][ j ].second)%MOD;
						if( ~pre[A[j]] && dp[ nxt[A[j]] ][ pre[A[j]] ].first == tem.first) 
							tem.second = (tem.second-dp[ nxt[A[j]] ][ pre[A[j]] ].second)%MOD;
					}
				}
				pre[ A[j] ] = j;
			}
			nxt[ A[i] ] = i;
		}
		Pii ans(0,0);
		for(int i=1; i<=D.siz; i++) if(dp[nxt[i]][pre[i]].first >= ans.first)
		{
			if(dp[nxt[i]][pre[i]].first > ans.first) ans = dp[nxt[i]][pre[i]];
			else ans.second = (ans.second + dp[nxt[i]][pre[i]].second) %MOD;
		}
		printf("%d %d\n", (ans.first+MOD)%MOD, (ans.second+MOD)%MOD);
	}
	return 0;
}


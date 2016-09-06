/*
Codeforces - 103D
给定一个长度为 N的序列，有 P个询问
每次询问从下标 a开始，每次下标 +b，这样所有数的和

先离线询问，对询问按 b从小到大排序
然后当 b比较小的时候 dp处理，当 b比较大的时候暴力算
取这个临界值为 sqrt(N)，这样就能以 O(P*sqrt(N))得解
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

const int maxn=3e5+10;
struct qur
{
	int a,b,id;
	bool operator < (const qur &rhs) const {return b < rhs.b;}
};
int N,P;
LL A[maxn], dp[maxn], ans[maxn];
qur Q[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		int bsiz = sqrt(N), nsiz=-1;
		for(int i=1; i<=N; i++) scanf("%lld", &A[i]);
		scanf("%d", &P);
		for(int i=0; i<P; i++)
		{
			Q[i].id = i;
			scanf("%d%d", &Q[i].a, &Q[i].b);
		}
		sort(Q, Q+P);
		for(int i=0; i<P; i++)
		{
			if(Q[i].b <= bsiz)
			{
				if(Q[i].b != nsiz)
				{
					nsiz = Q[i].b;
					for(int j=N; j>=1; j--)
					{
						dp[j] = A[j];
						if(j+nsiz<=N) dp[j] += dp[j+nsiz];
					}
				}
				ans[Q[i].id] = dp[Q[i].a];
			}
			else
			{
				LL &sum = ans[Q[i].id];
				sum = 0;
				for(int j=Q[i].a; j<=N; j+=Q[i].b) sum += A[j]; 
			}
		}
		for(int i=0; i<P; i++) printf("%lld\n", ans[i]);
	}
	return 0;
}


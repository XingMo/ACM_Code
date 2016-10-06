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

const int maxn=1e5+10;
int N,M;
int S[maxn], P[maxn];
LL tmin[maxn];

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
		CLR(tmin);
		scanf("%d%d", &N, &M);
		for(int i=1; i<=N; i++) scanf("%d%d", &S[i], &P[i]);
		tmin[N] = (LL)S[N]*P[N];
		for(int i=N-1; i>=1; i--) tmin[i] = min((LL)S[i]*P[i], tmin[i+1]);
		for(int m=1,x; m<=M; m++)
		{
			scanf("%d", &x);
			if(x>=S[N]) {printf("%lld\n", (LL)x*P[N]); continue;}
			int p = lower_bound(S+1, S+1+N, x) - S;
			if(S[p] != x) p--;
			printf("%lld\n", min(tmin[p+1], (LL)x*P[p]));
		}
	}
	return 0;
}


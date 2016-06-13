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

const int maxn=1e5+10;
int N,K;
int inpt[maxn];
LL ans;

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
		scanf("%d%d", &N, &K);
		for(int i=0; i<N; i++) scanf("%d", &inpt[i]);
		ans=0;
		for(int i=0; i<N; i++)
		{
			if(inpt[i]%(K*K)) continue;
			int d=inpt[i]/K;
			for(int j=i-1; j>=0; j--)
			{
				if(inpt[j]!=d) continue;
				for(int k=j-1; k>=0; k--)
				{
					if(inpt[k]==d/K) ans++;
				}
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}


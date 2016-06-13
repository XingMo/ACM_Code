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

const int maxn=4e4+10;
int N;
int inpt[maxn];
int L[maxn];

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
		for(int i=1; i<=N; i++) scanf("%d", &inpt[i]);
		
		MST(L,0x3f);
		L[0]=0;
		int ans=0;
		for(int i=1; i<=N; i++)
		{
			int now=upper_bound(L, L+i, inpt[i])-L;
			ans=max(ans, now);
			L[now] = min(L[now], inpt[i]);
		}
		printf("%d\n", ans);
	}	
	return 0;
}


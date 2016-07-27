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

int check(int);

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
		int l=1, r=inpt[N-1]-inpt[0]+1;
		while(l<r)
		{
			int mid=(l+r)>>1;
			if(check(mid)) r=mid;
			else l=mid+1; 
		}
		printf("%d\n", l);
	}
	return 0;
}

int check(int len)
{
	int np=0, cnt=0;
	while(np<N)
	{
		cnt++;
		if(cnt>K) return 0;
		int nxp=inpt[np]+len-1;
		if(nxp>=inpt[N-1]) np=N;
		else np = upper_bound(inpt, inpt+N, nxp)-inpt;
	}
	return 1;
}

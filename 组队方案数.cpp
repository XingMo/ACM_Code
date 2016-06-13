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
struct Discrete
{
	int siz, arry[maxn];
	void add(int n){arry[siz++]=n;}
	void init()
	{
		sort(arry, arry+siz);
		siz = unique(arry, arry+siz)-arry;
	}
	int id(int n)
	{
		int p=lower_bound(arry, arry+siz, n)-arry;
		if(p==siz || arry[p]!=n) return -1;
		return p;
	}
};
int N,K;
int inpt[maxn];
LL dp[maxn][3];
Discrete D;

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
		D.siz=0;
		scanf("%d%d", &N, &K);
		for(int i=0; i<N; i++)
		{
			scanf("%d", &inpt[i]);
			D.add(inpt[i]);
		}
		D.init();
		CLR(dp);
		for(int i=0; i<N; i++)
		{
			int id=D.id(inpt[i]);
			int id1=D.id(inpt[i]/K);
			if(id1!=-1 && inpt[i]%K==0) dp[id][2] += dp[id1][1];
			if(id1!=-1 && inpt[i]%K==0) dp[id][1] += dp[id1][0];
			dp[id][0]++;
		}
		LL ans=0;
		for(int i=0; i<D.siz; i++) ans += dp[i][2];
		printf("%lld\n", ans);
	}
	return 0;
}


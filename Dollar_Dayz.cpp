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

const int maxc=1e3+10;
const int per=1e4, perl=4, maxl=200;
struct bign
{
	int n[maxl];
	bign(){CLR(n);}
	int getlen()
	{
		int len=maxl;
		while(len && !n[--len]);
		return len+1;
	}
	bign operator = (int v)
	{
		CLR(n);
		n[0]=v;
		for(int i=0; i<4; i++) {n[i+1] = n[i]/per; n[i]%=per;}
	}
	bign operator + (const bign &v) const
	{
		bign temp;
		for(int i=0; i<maxl-1; i++)
		{
			temp.n[i] += n[i]+v.n[i];
			temp.n[i+1] += temp.n[i]/per;
			temp.n[i] %= per;
		}
		return temp;
	}
	void pri(const char *a="\n")
	{
		int len=getlen();
		printf("%d", n[len-1]);
		for(int i=len-2; i>=0; i--)
		{
			int cnt=0, tem=n[i];
			while(tem) {cnt++; tem/=10;}
			cnt=perl-cnt;
			for(int j=0; j<cnt; j++) putchar('0');
			if(n[i]) printf("%d", n[i]);
		}
		printf("%s", a);
	}
};
int N,K;
bign dp[maxc];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &K))
	{
		CLR(dp);
		dp[0]=1;
		for(int i=1; i<=K; i++)
		{
			for(int j=i; j<=N; j++)
			{
				dp[j]=dp[j]+dp[j-i];
			}
		}
		dp[N].pri();
	}
	return 0;
}


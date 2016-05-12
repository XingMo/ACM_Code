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

const int maxn=1e5+10;
int N,K;
int inpt[maxn];
LL psum[maxn];
int stak[maxn];

int readi(int&);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &K))
	{
		for(int i=1; i<=N; i++)
		{
			readi(inpt[i]);
//			scanf("%d", &inpt[i]);
			psum[i]=psum[i-1]+inpt[i];
		}
//		DBL ans=0.0;
//		int ansl,ansr;
//		for(int i=K; i<=N; i++)
//		{
//			for(int j=0; j<i-K+1; j++)
//			{
//				DBL temp=(DBL)(psum[i]-psum[j])/(i-j);
//				if(temp>ans)
//				{
//					ans=temp;
//					ansl=j+1, ansr=i;
//				}
//			}
//		}
		int sktop=0;
		LL ans=0;
		for(int i=K; i<=N; i++)
		{
			stak[sktop++]=i-K;
			while(sktop>1)
			{
				int j=stak[sktop-1], k=stak[sktop-2];
				if((psum[j]-psum[k])*(i-k) >= (psum[i]-psum[k])*(j-k)) sktop--;
				else break;
			}
			LL temp=1000*(psum[i]-psum[stak[sktop-1]])/(i-stak[sktop-1]);
			if(temp>ans)
			{
				ans=temp;
//				ansl=stak[sktop-1]+1; ansr=i;
			}
		}
//		printf("%lld\n", ans);
		cout << ans << '\n';
//		printf("%d %d\n", ansl, ansr);
	}
	return 0;
}

int readi(int &x)
{
	char c;
	while(!isdigit(c=getchar()));
	x=c-'0';
	while(isdigit(c=getchar())) x=x*10+c-'0';
}


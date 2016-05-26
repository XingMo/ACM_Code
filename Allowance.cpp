/*
POJ - 3040
FJ手中有若干面值的货币，小面值的货币能被大面值的整除
每周他要给奶牛发不少于 C的工资，问最多能发几周

首先大于 C的面值都先发掉
然后优先发剩下的大面额的货币，当超过时
将最后一个大面额的用尽可能小的货币代替
*/
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

const int INF=0x3f3f3f3f;
struct data
{
	int v,b;
	bool operator < (const data &y) const {return v < y.v;}
} inpt[30];
int N,C;
int have[30];

inline void pause(){fflush(stdin); getchar();}

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &C))
	{
		for(int i=0; i<N; i++) scanf("%d%d", &inpt[i].v, &inpt[i].b);
		sort(inpt, inpt+N);
		
		LL ans=0;
		while(N && inpt[N-1].v >= C) ans += inpt[--N].b;

		while(1)
		{
			for(int i=0; i<N; i++) have[i]=inpt[i].b;
			int left=C;
			for(int i=N-1; i>=0; i--)
			{
				int cnt = left/inpt[i].v;
				if(have[i] < cnt) continue;
				have[i] -= cnt;
				left -= cnt*inpt[i].v;
			}
			
			for(int i=0; i<N; i++)
			{
				int cnt = left/inpt[i].v;
				if(left%inpt[i].v) cnt++;
				if(have[i] < cnt) cnt = have[i];
				have[i] -= cnt;
				left -= cnt*inpt[i].v;
				if(left <= 0) break;
			}

			if(left > 0) break;

			int tims=INF;
			for(int i=0; i<N; i++) if(have[i] < inpt[i].b) tims = min(tims, inpt[i].b/(inpt[i].b - have[i]));
			
			ans+=tims;
			for(int i=0; i<N; i++) if(have[i] < inpt[i].b) inpt[i].b -= (inpt[i].b - have[i])*tims;
		}
		
		printf("%lld\n", ans);
	}
	return 0;
}


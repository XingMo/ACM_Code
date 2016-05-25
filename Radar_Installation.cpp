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
#define Sqr(a) ((a)*(a))

const DBL eps=1e-8;
const int maxn=1e3+10;
struct data
{
	DBL l,r;
	bool operator < (const data &v) const {return r < v.r;}
};
int N,D;
data sque[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int ck=0;
	while(~scanf("%d%d", &N, &D) && N)
	{
		if(ck) puts("");
		printf("Case %d: ", ++ck);
		int ans=0;
		for(int i=0; i<N; i++) 
		{
			int x,y;
			scanf("%d%d", &x, &y);
			if(y > D) ans=-1;
			else
			{
				DBL dx = sqrt(Sqr(D)-Sqr(y));
				sque[i].l = x-dx;
				sque[i].r = x+dx;
			}
		}
		if(ans==-1) {printf("-1");continue;}
		sort(sque, sque+N);
		
		int np=0;
		while(np<N)
		{
			DBL now=sque[np].r;
			while(np<N && (sque[np].l<now || abs(sque[np].l-now) < eps) ) np++;
			ans++;
		}
		printf("%d", ans);
	}		
	return 0;
}


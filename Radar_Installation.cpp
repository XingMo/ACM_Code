/*
POJ - 1328
给定若干个 x轴上方的点，要求最少的圆，使得每个点都被圆覆盖
其中圆心在 x轴上，半径为 D

有一个很直接的贪心思路，就是先考虑最左边未覆盖的点
在覆盖它的情况下，尽量把圆向左移。
这个做法是错误的，因为圆并不是矩形，例如以下数据
---
2 3
0 0
1 3
---
1
---

正确的做法是预处理出覆盖每个点的圆心的范围
然后问题就转化为若干个区间，
选择最少的点使每个区间内都至少有一个点

贪心策略是对区间右端点排序，然后尽量选择右端点
因为这样使得其右边的区间尽可能地包括这个点
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


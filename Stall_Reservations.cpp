/*
POJ - 3190
给定若干个区间，问至少要分成几组
使得同组的区间互不重叠

典型的区间贪心问题
贪心的策略就是对左端点排序，然后依次选择安排
记录一下每个隔间最右端点的位置，然后用最小堆维护一下
当前区间尽可能地放到最右点最小的组里
如果这组依旧放不进去，就没有隔间能放得进去了
所以就要为其申请一个新的隔间
否则就把它安排到这个隔间里，并且更新此隔间最右端点
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

const int maxn=5e4+10, INF=0x3f3f3f3f;
struct intv
{
	int id,l,r;
	intv(int a=0,int b=0, int c=0):id(a),l(b),r(c){};
	bool operator < (const intv &v) const {return l < v.l;}
};
int N,ncnt;
int ans[maxn];
intv inpt[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		ncnt=0;
		for(int i=0; i<N; i++) 
		{
			scanf("%d%d", &inpt[i].l, &inpt[i].r);
			inpt[i].id=i;
		}
		sort(inpt, inpt+N);
		priority_queue<intv> pq;
		pq.push(intv(0,-INF,-INF));
		for(int i=0; i<N; i++)
		{
			intv now=pq.top();
			int end = -now.l;
			//能安排
			if(inpt[i].l > end)
			{
				pq.pop();
				now.l = -inpt[i].r;
				pq.push(now);
				ans[ inpt[i].id ]=now.id;
			}
			//申请新隔间
			else
			{
				ncnt++;
				now.id = ncnt;
				now.l = -inpt[i].r;
				pq.push(now);
				ans[ inpt[i].id ]=ncnt;
			}
		}
		printf("%d\n", ncnt);
		for(int i=0; i<N; i++) printf("%d\n", ans[i]);
	}
	return 0;
}


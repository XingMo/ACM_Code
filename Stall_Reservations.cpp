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
			if(inpt[i].l > end)
			{
				pq.pop();
				now.l = -inpt[i].r;
				pq.push(now);
				ans[ inpt[i].id ]=now.id;
			}
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


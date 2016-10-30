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
#include <stack>
#include <queue>
#include <bitset>
#include <string>
#include <complex>
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define SQR(a) ((a)*(a))
#define PCUT puts("\n----------")

const int maxn = 1e5+10;
const DBL eps = 1e-8;
int sgn(DBL x){return x>eps?1:(x<-eps?-1:0);}

struct Vector
{
	LL x,y;
	Vector(LL _x=0, LL _y=0):x(_x),y(_y){}
	Vector operator - (const Vector &rhs) const {return Vector(x-rhs.x, y-rhs.y);}
	LL operator ^ (const Vector &rhs) const {return x*rhs.y - y*rhs.x;}
	bool operator < (const Vector &rhs) const
	{
		if(x != rhs.x) return x < rhs.x;
		return y < rhs.y;
	}
	int read(){return scanf("%lld%lld", &x, &y);}
};
typedef Vector Point;

int N;
Point in[maxn];
LL ans[2][maxn];
Point stk[2][maxn];

int work(LL*);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		CLR(ans);
		for(int i=1; i<=N; i++) in[i].read();
		sort(in+1, in+1+N);
		int tot;
		work(ans[0]); //PCUT;
		reverse(in+1, in+1+N);
		for(int i=1; i<=N; i++) in[i].x = -in[i].x;
		tot = work(ans[1]); //PCUT;
		reverse(ans[1]+1, ans[1]+1+tot);
		
//		for(int i=1; i<=tot; i++) printf("%lld ", ans[0][i]); puts("");
//		for(int i=1; i<=tot; i++) printf("%lld ", ans[1][i]); puts("");
		
		LL res = ans[0][1] + ans[1][2];
		for(int i=1; i<=tot; i++) res = min(res, ans[0][i] + ans[1][i+1]);
		printf("%lld\n", (res+1)/2);
	}
	return 0;
}

int work(LL arr[])
{
	int top[2] = {0};
	LL cur = 0;
	int np = 1;
	for(int i=1; i<=N; i++)
	{
		while(top[0] > 1 && ((in[i]-stk[0][top[0]-2])^(stk[0][top[0]-1]-stk[0][top[0]-2])) <= 0)
		{
			top[0] --;
			cur -= stk[0][top[0]]^stk[0][top[0]-1];
		}
		if(top[0]) cur += in[i]^stk[0][top[0]-1];
		stk[0][top[0]++] = in[i];
//		printf("%d %lld\n", top[0], cur);

		while(top[1] > 1 && ((in[i]-stk[1][top[1]-2])^(stk[1][top[1]-1]-stk[1][top[1]-2])) >= 0)
		{
			top[1] --;
			cur += stk[1][top[1]]^stk[1][top[1]-1];
		}
		if(top[1]) cur -= in[i]^stk[1][top[1]-1];
		stk[1][top[1]++] = in[i];
//		printf("%d %lld\n", top[1], cur);
		if(i<N && in[i+1].x==in[i].x) continue;
		arr[np++] = cur;
	}
	return np-1;
}

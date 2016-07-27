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
struct data{LL x,y; int id;};
int N;
data inpt[maxn];
LL ans[maxn];
bool cmpx(data a, data b){return a.x<b.x;}
bool cmpy(data a, data b){return a.y<b.y;}

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
		scanf("%d", &N);
		LL lm, rm, um, dm;
		CLR(ans);
		for(int i=0; i<N; i++)
		{
			scanf("%lld%lld", &inpt[i].x, &inpt[i].y);
			inpt[i].id=i;
			if(i==0) lm=rm=inpt[i].y, um=dm=inpt[i].x;
			else
			{
				lm = min(lm, inpt[i].y);
				rm = max(rm, inpt[i].y);
				um = min(um, inpt[i].x);
				dm = max(dm, inpt[i].x);
			}
		}
		LL tot=0;
		sort(inpt, inpt+N, cmpx);
		for(int i=0; i<N; i++)
		{
			ans[inpt[i].id] += i*(inpt[i].x-um)-tot;
			tot += inpt[i].x-um;
		}
		tot=0;
		reverse(inpt, inpt+N);
		for(int i=0; i<N; i++)
		{
			ans[inpt[i].id] += i*(dm-inpt[i].x)-tot;
			tot += dm-inpt[i].x;
		}
		tot=0;
		sort(inpt, inpt+N, cmpy);
		for(int i=0; i<N; i++)
		{
			ans[inpt[i].id] += i*(inpt[i].y-lm)-tot;
			tot += inpt[i].y-lm;
		}
		tot=0;
		reverse(inpt, inpt+N);
		for(int i=0; i<N; i++)
		{
			ans[inpt[i].id] += i*(rm-inpt[i].y)-tot;
			tot += rm-inpt[i].y;
		}
		LL res=ans[0];
		for(int i=1; i<N; i++) res = min(res, ans[i]);
		cout << res << '\n';
	}
	return 0;
}


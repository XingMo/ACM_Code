/*
POJ - 2376
给定一个区间，要求用最少的区间将其覆盖

典型的区间贪心问题
首先将区间按左端点排序，然后考虑覆盖区间最左未覆盖位置
选择能覆盖此点，且右端点最靠右的区间覆盖它
要注意特判是否有合法解，如果途中无法覆盖某点，
或者所有区间都用完了也不能覆盖完即无解
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

const int maxn=3e4+10;
struct data
{
	int l,r;
	bool operator < (const data &v) const {return l < v.l;}
};
int N,T;
data inpt[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &T))
	{
		for(int i=0; i<N; i++) scanf("%d%d", &inpt[i].l, &inpt[i].r);
		sort(inpt, inpt+N);
		int nt=1, np=0, ans=0;
		while(np<N && nt<=T)
		{
			int tmax=-1;
			while(np<N && inpt[np].l<=nt)
			{
				tmax=max(tmax, inpt[np].r);
				np++;
			}
			if(tmax < nt) {ans=-1;break;}
			nt=tmax+1;
			ans++;
		}
		if(nt <= T) ans=-1; // !!!
		printf("%d\n", ans);
	}
	return 0;
}


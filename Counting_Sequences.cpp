/*
HDU - 3450
给定一个长度为 N的序列，
问有多少种长度大等于 2的非连续子序列
使得子序列中相邻两项的差不超过 D

先离散化一下数据
然后用 bit维护一下以数字 i为结尾的子序列的个数
由于长度为 1的不能算入，所以另开一个bit记录长度为 1的
*/
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

const int MOD=9901;
const int maxn=1e5+10;
struct Discrete
{
	LL ais[3*maxn], siz;
	void init()
	{
		sort(ais, ais+siz);
		siz = unique(ais, ais+siz)-ais;
	}
	void add(LL _n){ ais[siz++]=_n;}
	int id(LL _n){ return lower_bound(ais,ais+siz,_n)-ais+1;}
};
struct BIT
{
	int bit[3*maxn], siz;
	void init(int _n){ siz=_n; CLR(bit);}
	void add(int p, int x){ for(int i=p; i<=siz; i+=i&-i) bit[i]=(bit[i]+x)%MOD;}
	int sum(int p){ int res=0; for(int i=p; i>0; i-=i&-i) res = (res+bit[i])%MOD; return res;}
};
int N,D;
LL inpt[maxn];
Discrete ds;
BIT bit0, bit1;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &D))
	{
		ds.siz=0;
		for(int i=0; i<N; i++)
		{
			scanf("%lld", &inpt[i]);
			ds.add(inpt[i]);
			ds.add(inpt[i]+D);
			ds.add(inpt[i]-D-1);
		}
		ds.init();
		bit0.init(ds.siz);
		bit1.init(ds.siz);
		int ans=0;
		for(int i=0; i<N; i++)
		{
			int now = bit1.sum(ds.id(inpt[i]+D)) - bit1.sum(ds.id(inpt[i]-D-1));
			now += bit0.sum(ds.id(inpt[i]+D)) - bit0.sum(ds.id(inpt[i]-D-1));			
			ans = (ans+now)%MOD;
			bit1.add(ds.id(inpt[i]), now);
			bit0.add(ds.id(inpt[i]), 1);
		}
		ans = (ans+MOD)%MOD;
		printf("%d\n", ans);
	}
	return 0;
}


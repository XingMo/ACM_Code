/*
SPOJ - 3267
给定一个序列，询问区间内有多少个不同的数

刚开始题目读错了，以为求的是区间内有多少个不重复出现的数
导致我想了半天不懂别人怎么树状数组离线的

实际上只要保证区间内每个数只被统计过一次就好了
先将询问离线，对区间右端点排序
然后用权值树状数组来标记一下，在每个数出现的位置加上一个 1
相同数尽量地将权值放到最右边的那个数上，然后删去前一个位置的权值
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
#include <bitset>
#include <string>
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

const int maxn=3e4+10, maxq=2e5+10, maxa=1e6+10;
struct data
{
	int l,r,id;
	bool operator < (const data &v) const {return r < v.r;}
};
struct BIT
{
	int bit[maxn],siz;
	void init(int _n) {siz=_n; CLR(bit);}
	void add(int p, int x){for(int i=p; i<=siz; i+=i&-i) bit[i]+=x;}
	int sum(int p) {int res=0; for(int i=p; i>0; i-=i&-i) res+=bit[i]; return res;}
};
int N, M, A[maxn], last[maxa], ans[maxq];
data Q[maxq];
BIT bit;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		CLR(last); bit.init(N);
		for(int i=1; i<=N; i++) scanf("%d", &A[i]);
		scanf("%d", &M);
		for(int i=1; i<=M; i++) scanf("%d%d", &Q[i].l, &Q[i].r), Q[i].id=i;
		sort(Q+1,Q+1+M);
		int np=1;
		for(int i=1; i<=N; i++)
		{
			if(last[ A[i] ]) bit.add(last[A[i]], -1);
			bit.add(i, 1);
			last[A[i]] = i;
			for(; np<=M && Q[np].r==i; np++) ans[Q[np].id] = bit.sum(Q[np].r) - bit.sum(Q[np].l-1);
		}
		for(int i=1; i<=M; i++) printf("%d\n", ans[i]);
	}
	return 0;
}


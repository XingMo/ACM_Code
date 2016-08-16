/*
HDU - 5820
给定一个网格图，上面有 N个灯
求任意两个灯之间，是否至少存在一条曼哈顿最短路径
使得路径上的每一个拐点都有一个灯

主席树+扫描线
枚举每一个节点，利用主席树维护一下
这个点及左边最近节点、上面最近节点三个点构成的矩形
以及此点、右边最近节点和上面最近节点三个点构成的矩形
这两个矩形内是否存在点，如果存在，那么就是不合法的图

具体主席树就是每一行建一棵树，每遇到一个点就在这位置加一
然后枚举的点的左边点 y值加一和右边点 y值减一为询问区间
询问枚举点的时间和上面点的时间两个版本的询问区间上的差
就能得出矩形内有多少个点

要考虑一下边界情况，比如左边没有点的，右边没有点的，
上面没有点的这些情况，询问的时候都要询问到边界

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

const int maxn=5e5+10, maxl=5e4;
struct PSegmentTree
{
	struct node
	{
		int ls,rs,sum;
	} segt[maxn*40];
	int siz,time,len,root[maxn];
	void init(int _n){siz=0; time=0; len=_n; segt[0].ls=segt[0].rs=segt[0].sum=0;}
	int update(int,int,int=-1,int=-1,int=-1);
	int query(int,int,int,int=-1,int=-1,int=-1);
	void maintain(int);
};

int N;
int up[maxl+10];
Pii P[maxn];
PSegmentTree pstree;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		if(!N) break;
		CLR(up);
		for(int i=0; i<N; i++) scanf("%d%d", &P[i].first, &P[i].second);
		sort(P, P+N);
		N = unique(P, P+N)-P;
		pstree.init(maxl);
		
		bool ok=1;
		for(int nl=0,nr; nl<N; nl=nr)
		{
			nr = nl;
			while(nr<N && P[nl].first == P[nr].first) nr++;
			int l, r, ntime, ptime, delt;
			for(int i=nl; i<nr; i++)
			{
				pstree.update(P[i].second, 1);
				ptime = up[P[i].second];
				ntime = pstree.time;
				l = i==nl?0:P[i-1].second;
				r = i==nr-1?50001:P[i+1].second;
				delt = pstree.query(ntime,l+1,r-1) - pstree.query(ptime,l+1,r-1) - 1;
				if(delt>0) {ok=0; break;}
			}
			if(!ok) break;
			for(int i=nl; i<nr; i++) up[P[i].second] = pstree.time;
		}
		puts(ok?"YES":"NO");
	}
	return 0;
}

int PSegmentTree::update(int p,int v,int np,int nl,int nr)
{
	int tp=++siz;
	if(np==-1)
	{
		np=root[time], nl=1, nr=len;
		root[++time] = tp;
	}
	node &now=segt[np], &to=segt[tp];
	to = now;
	if(nl==nr)
	{
		to.sum += v;
		return tp;
	}
	int mid=(nl+nr)>>1;
	if(p<=mid) to.ls = update( p, v, now.ls, nl, mid);
	else to.rs = update( p, v, now.rs, mid+1, nr);
	maintain(tp);
	return tp;
}

int PSegmentTree::query(int nt,int ql,int qr,int np,int nl,int nr)
{
	if(np==-1) {np=root[nt]; nl=1; nr=len;}
	node &now=segt[np];
	if(ql<=nl && nr<=qr) return now.sum;
	int mid=(nl+nr)>>1, res=0;
	if(ql<=mid) res += query(nt,ql,qr,now.ls,nl,mid);
	if(qr> mid) res += query(nt,ql,qr,now.rs,mid+1,nr);
	return res;
}

void PSegmentTree::maintain(int np)
{
	segt[np].sum = segt[segt[np].ls].sum + segt[segt[np].rs].sum;
}

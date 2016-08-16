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
#include <cassert>
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

const int maxn=1e5+10;
struct SegmentTree
{
	#define Lson np<<1,nl,mid
	#define Rson np<<1|1,mid+1,nr
	#define Npos np,nl,nr
	struct node
	{
		LL sum,val,add;
	} segt[maxn<<2];
	int len;
	void adjust(int &np, int &l, int &r){if(np==-1) {np=1; l=1; r=len;}}
	void build(int=-1,int=-1,int=-1);
	void add(int,int,int,int=-1,int=-1,int=-1);
	void rsqrt(int,int,int=-1,int=-1,int=-1);
	LL sum(int,int,int=-1,int=-1,int=-1);
	void maintain(int,int,int);
	void pushdown(int,int,int);
	void pri(int np,int nl,int nr)
	{
		node &now=segt[np];
		printf("l:%d r:%d sum:%lld val:%lld add:%lld\n", nl, nr, now.sum, now.val, now.add);
	}
};

int N, M, A[maxn];
SegmentTree tree;
int main()
{
	#ifdef LOCAL
//	freopen("1008.in", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		scanf("%d%d", &N, &M);
		for(int i=1; i<=N; i++) scanf("%d", &A[i]);
		tree.len=N;
		tree.build();
		for(int i=1,opt,l,r,x; i<=M; i++)
		{
			scanf("%d%d%d", &opt, &l, &r);
			if(opt==1) {scanf("%d", &x); tree.add(l,r,x);}
			if(opt==2) {tree.rsqrt(l,r);}
			if(opt==3) {printf("%lld\n", tree.sum(l,r));}
//			PCUT;
		}
	}
	return 0;
}

void SegmentTree::build(int np, int nl, int nr)
{
	adjust(Npos);
	segt[np].add=0; segt[np].val=-1;
	if(nl==nr) {segt[np].sum = segt[np].val = A[nl]; return;}
	int mid=(nl+nr)>>1;
	build(Lson); build(Rson);
	maintain(Npos); return;
}

void SegmentTree::add(int ql, int qr, int qv, int np, int nl, int nr)
{
	adjust(Npos);
//	pri(Npos);
	if(ql<=nl && nr<=qr) {segt[np].add+=qv; maintain(Npos); return;}
	int mid=(nl+nr)>>1; pushdown(Npos);
	if(qr<=mid)
	{
		add( ql, qr, qv, Lson);
		maintain(Rson);
	}
	else if(ql>mid)
	{
		add( ql, qr, qv, Rson);
		maintain(Lson);
	}
	else
	{
		add( ql, qr, qv, Lson);
		add( ql, qr, qv, Rson);
	}
	maintain(Npos);return;
}

void SegmentTree::rsqrt(int ql, int qr, int np, int nl, int nr)
{
	adjust(Npos);
//	pri(Npos);
	if(ql<=nl && nr<=qr && ~segt[np].val)
	{
		segt[np].val = sqrt(segt[np].val);
		segt[np].sum = (nr-nl+1)*segt[np].val;
		segt[np].add = 0;
		return;
	}
	int mid=(nl+nr)>>1; pushdown(Npos); maintain(Lson); maintain(Rson);
	if(ql<=mid) rsqrt(ql, qr, Lson);
	if(qr>mid) rsqrt(ql, qr, Rson);
	maintain(Npos); return;
}

LL SegmentTree::sum(int ql, int qr, int np, int nl, int nr)
{
	adjust(Npos);
//	pri(Npos);
	if(ql<=nl && nr<=qr) {return segt[np].sum;}
	int mid=(nl+nr)>>1; pushdown(Npos); maintain(Lson); maintain(Rson);
	LL res=0;
	if(ql<=mid) res += sum( ql, qr, Lson);
	if(qr>mid) res += sum( ql, qr, Rson);
	return res;
}

void SegmentTree::maintain(int np, int nl, int nr)
{
	node &now=segt[np];
	if(~now.val)
	{
		now.val += now.add;
		now.sum = (nr-nl+1)*now.val;
		now.add = 0;
	}
	else
	{
		node &lson=segt[np<<1], &rson=segt[np<<1|1];
		now.sum = lson.sum + rson.sum;
		now.sum += (nr-nl+1)*now.add;
		if(lson.val == rson.val) now.val=lson.val;
		else now.val = -1;
		if(~now.val)
		{
			now.val += now.add;
			now.add = 0;
		}
	}
}

void SegmentTree::pushdown(int np, int nl, int nr)
{
	node &now=segt[np], &lson=segt[np<<1], &rson=segt[np<<1|1];
	if(~now.val)
	{
		lson.val=rson.val=now.val;
		now.val=-1;
	}
	if(now.add)
	{
		lson.add += now.add;
		rson.add += now.add;
		now.add = 0;
	}
}

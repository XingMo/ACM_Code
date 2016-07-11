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
struct SegmentTree
{
	//add1, add2, set, query
	struct node
	{
		int l,r;
		LL setv, addv, begv, difv, sum;
	} segt[4*maxn];
	void build(int,int,int);
	void add(int,int,int,LL); // add1
	void add(int,int,int,LL,LL); // add2
	void set(int,int,int,LL);
	LL query(int,int,int);
	void maintain(int);
	bool pushdown(int);
};
int N,M;
int inpt[maxn];
SegmentTree tree;

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
		scanf("%d%d", &N ,&M);
		for(int i=1; i<=N; i++) scanf("%d", &inpt[i]);
		tree.build(1,1,N);
		for(int i=1; i<=M; i++)
		{
			int opt, l, r, val;
			scanf("%d%d%d", &opt, &l, &r);
			if(opt==4) printf("%lld\n", tree.query(1,l,r));
			else
			{
				scanf("%d", &val);
				if(opt==1) tree.add(1,l,r,val);
				if(opt==2) tree.add(1,l,r,val,val);
				if(opt==3) tree.set(1,l,r,val);
			}
		}
	}
	return 0;
}

void SegmentTree::build(int np, int nl, int nr)
{
	node &now=segt[np];
	now.l = nl;
	now.r = nr;
	now.setv = -1;
	now.addv = now.begv = now.difv = 0;
	if(nl==nr)
	{
		now.sum = inpt[nl];
		return;
	}
	int mid=(nl+nr)>>1;
	build(np*2, nl, mid);
	build(np*2+1, mid+1, nr);
	maintain(np);
}

// add1
void SegmentTree::add(int np, int ql, int qr, LL val)
{
	node &now=segt[np];
	if(ql<=now.l && now.r<=qr)
	{
		now.addv+=val;
		maintain(np);
		return;
	}
	bool ifpush = pushdown(np);
	int mid=(now.l+now.r)>>1;
	if(qr<=mid)
	{
		add(np*2, ql, qr, val);
		if(ifpush) maintain(np*2+1);
	}
	else if(ql>mid)
	{
		add(np*2+1, ql, qr, val);
		if(ifpush) maintain(np*2);
	}
	else
	{
		add(np*2, ql, qr, val);
		add(np*2+1, ql, qr, val);
	}
	maintain(np);
}

// add2
void SegmentTree::add(int np, int ql, int qr, LL beg, LL dif)
{
	node &now=segt[np];
	if(ql<=now.l && now.r<=qr)
	{
		now.begv+=beg;
		now.difv+=dif;
		maintain(np);
		return;
	}
	bool ifpush = pushdown(np);
	int mid=(now.l+now.r)>>1;
	if(qr<=mid)
	{
		add(np*2, ql, qr, beg, dif);
		if(ifpush) maintain(np*2+1);
	}
	else if(ql>mid)
	{
		add(np*2+1, ql, qr, beg, dif);
		if(ifpush) maintain(np*2);
	}
	else
	{
		int pos=max(ql, now.l);
		LL nxt = beg+dif*(mid-pos+1);
		add(np*2, ql, qr, beg, dif);
		add(np*2+1, ql, qr, nxt, dif);
	}
	maintain(np);
}

void SegmentTree::set(int np, int ql, int qr, LL val)
{
	node &now=segt[np];
	if(ql<=now.l && now.r<=qr)
	{
		now.setv = val;
		now.addv = now.begv = now.difv = 0;
		maintain(np);
		return;
	}
	bool ifpush = pushdown(np);
	int mid=(now.l+now.r)>>1;
	if(qr<=mid)
	{
		set(np*2, ql, qr, val);
		if(ifpush) maintain(np*2+1);
	}
	else if(ql>mid)
	{
		set(np*2+1, ql, qr, val);
		if(ifpush) maintain(np*2);
	}
	else
	{
		set(np*2, ql, qr, val);
		set(np*2+1, ql, qr, val);
	}
	maintain(np);
}

LL SegmentTree::query(int np, int ql, int qr)
{
	node &now=segt[np];
	if(ql<=now.l && now.r<=qr) return now.sum;
	bool ifpush = pushdown(np);
	if(ifpush) maintain(np*2);
	if(ifpush) maintain(np*2+1);
	int mid=(now.l+now.r)>>1;
	LL res=0;
	if(ql<=mid) res += query(np*2, ql, qr);
	if(qr>mid)  res += query(np*2+1, ql, qr);
	return res;
}

bool SegmentTree::pushdown(int np)
{
	node &now=segt[np];
	node &lson=segt[np*2], &rson=segt[np*2+1];
	bool res=0;
	if(~now.setv)
	{
		lson.setv = rson.setv = now.setv;
		lson.addv = lson.begv = lson.difv = 0;
		rson.addv = rson.begv = rson.difv = 0;
		res=1;
	}
	if(now.addv)
	{
		lson.addv += now.addv;
		rson.addv += now.addv;
		res=1;
	}
	if(now.begv)
	{
		int pos=((now.l+now.r)>>1)-now.l+1;
		lson.begv += now.begv;
		rson.begv += now.begv + pos*now.difv;
		lson.difv += now.difv;
		rson.difv += now.difv;
		res=1;
	}
	now.setv = -1;
	now.addv = now.begv = now.difv = 0;
	return res;
}

void SegmentTree::maintain(int np)
{
	node &now=segt[np];
	if(now.l==now.r)
	{
		if(~now.setv) now.sum = now.setv;
		if(now.addv) now.sum += now.addv;
		if(now.begv) now.sum += now.begv;
		now.setv = -1;
		now.addv = now.begv = now.difv = 0;
	}
	else
	{
		node &lson=segt[np*2], &rson=segt[np*2+1];
		now.sum = lson.sum + rson.sum;
		int n = now.r-now.l+1;
		if(~now.setv) now.sum = now.setv*n;
		if(now.addv) now.sum += now.addv*n;
		if(now.begv) now.sum += n*now.begv + n*(n-1)/2*now.difv;
	}
}

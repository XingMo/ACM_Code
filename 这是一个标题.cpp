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
const LL INF=0x3f3f3f3f3f3f3f3f;
struct SegmentTree
{
	struct node
	{
		int l,r;
		LL pre, suf, res, sum;
	} segt[4*maxn];
	void build(int,int,int);
	node query(int,int,int);
	void maintain(int);
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
		scanf("%d%d", &N, &M);
		for(int i=1; i<=N; i++) scanf("%d", &inpt[i]);
		tree.build(1,1,N);
		for(int i=1; i<=M; i++)
		{
			int l,r;
			scanf("%d%d", &l, &r);
			printf("%lld\n", tree.query(1,l,r).res);
		}
	}
	return 0;
}

void SegmentTree::build(int np, int nl, int nr)
{
	segt[np].l = nl;
	segt[np].r = nr;
	if(nl==nr)
	{
		maintain(np);
		return;
	}
	int mid=(nl+nr)>>1;
	build(np*2, nl, mid);
	build(np*2+1, mid+1, nr);
	maintain(np);
}

SegmentTree::node SegmentTree::query(int np, int ql, int qr)
{
	node &now=segt[np];
	if(ql<=now.l && now.r<=qr)
	{
		return now;
	}
	int mid=(now.l+now.r)>>1;
	node lres, rres, nres;
	nres.pre = nres.suf = nres.res = -INF; nres.sum=0;
	lres.pre = lres.suf = lres.res = -INF; lres.sum=0;
	rres.pre = rres.suf = rres.res = -INF; rres.sum=0;
	if(ql<=mid)
	{
		lres=query(np*2, ql, qr);
	}
	if(qr>mid)
	{
		rres=query(np*2+1, ql, qr);
	}
	nres.res = max(lres.suf+rres.pre, max(lres.res, rres.res));
	nres.pre = max(lres.pre, lres.sum+rres.pre);
	nres.suf = max(rres.suf, lres.suf+rres.sum);
	nres.sum = lres.sum+rres.sum;
	return nres;
}

void SegmentTree::maintain(int np)
{
	node &now = segt[np];
	if(now.l == now.r)
	{
		now.pre = now.suf = now.res = now.sum = inpt[now.l];
	}
	else
	{
		node &lson=segt[np*2], &rson=segt[np*2+1];
		now.pre = max(lson.pre, lson.sum+rson.pre);
		now.suf = max(rson.suf, lson.suf+rson.sum);
		now.res = max(lson.suf+rson.pre, max(lson.res, rson.res));
		now.sum = lson.sum + rson.sum;
	}
}

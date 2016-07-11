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
	struct node
	{
		int l,r,sum,addv;
	} segt[4*maxn];
	void build(int,int,int);
	void update(int,int,int,int);
	int query(int,int,int);
	void pushdown(int);
	void maintain(int);
};
int N,Q;
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
		scanf("%d", &N);
		
		scanf("%*s%*s");
		scanf("%d", &Q);
		tree.build(1,1,N);
		for(int i=1; i<=Q; i++)
		{
			int opt,a,b;
			scanf("%d%d%d", &opt, &a, &b);
			if(opt)
			{
				printf("%d\n", tree.query(1,a,b));
			}
			else
			{
				tree.update(1,a,a,b);
			}
		}
		
		scanf("%*s%*s");
		scanf("%d", &Q);
		tree.build(1,1,N);
		for(int i=1; i<=Q; i++)
		{
			int opt,a,b,c;
			scanf("%d", &opt);
			if(opt)
			{
				scanf("%d", &a);
				printf("%d\n", tree.query(1,a,a));
			}
			else
			{
				scanf("%d%d%d", &a, &b, &c);
				tree.update(1,a,b,c);
			}
		}
	}
	return 0;
}

void SegmentTree::build(int np, int nl, int nr)
{
	segt[np].l = nl;
	segt[np].r = nr;
	segt[np].sum = segt[np].addv = 0;
	if(nl==nr) return;
	int mid=(nl+nr)>>1;
	build(np*2, nl, mid);
	build(np*2+1, mid+1, nr);
}

void SegmentTree::update(int np, int ql, int qr, int val)
{
	node &now=segt[np];
	if(ql<=now.l && now.r<=qr)
	{
		now.addv+=val;
		maintain(np);
		return;
	}
	int mid=(now.l+now.r)>>1;
	pushdown(np);
	if(qr<=mid)
	{
		update(np*2, ql, qr, val);
		maintain(np*2+1);
	}
	else if(ql>mid)
	{
		update(np*2+1, ql, qr, val);
		maintain(np*2);
	}
	else
	{
		update(np*2, ql, qr, val);
		update(np*2+1, ql, qr, val);
	}
	maintain(np);
}

int SegmentTree::query(int np, int ql, int qr)
{
	node &now=segt[np];
	if(ql<=now.l && now.r<=qr) return now.sum;
	int mid=(now.l+now.r)>>1;
	pushdown(np);
	maintain(np*2);
	maintain(np*2+1);
	int ans=0;
	if(ql<=mid) ans += query(np*2, ql, qr);
	if(qr>mid)  ans += query(np*2+1, ql, qr);
	return ans;
}

void SegmentTree::pushdown(int np)
{
	if(segt[np].addv)
	{
		segt[np*2].addv += segt[np].addv;
		segt[np*2+1].addv += segt[np].addv;
		segt[np].addv=0;	
	}
}

void SegmentTree::maintain(int np)
{
	node &now=segt[np];
	if(now.l==now.r)
	{
		now.sum+=now.addv;
		now.addv=0;
	}
	else
	{
		node &lson=segt[np*2], &rson=segt[np*2+1];
		now.sum = lson.sum+rson.sum;
		now.sum += now.addv;
	}
}

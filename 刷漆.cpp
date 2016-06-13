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

typedef map<int,int>::iterator mit;

const int maxn=1e5+10;
struct SegmentTree
{
	struct node
	{
		int l,r, setv;
		map<int,int> col;
		void pri()
		{ 
			printf("l:%d r:%d s:%d\n", l, r, setv);
			for(mit it=col.begin(); it!=col.end(); it++)
			{
				printf("%d: %d\n", it->first, it->second);
			}
		}
	} segt[4*maxn];
	void build(int,int,int);
	void update(int,int,int,int);
	int query(int,int,int,int);
	void maintain(int);
	void pushdown(int);
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
			int opt, l, r, val;
			scanf("%d%d%d%d", &opt, &l, &r, &val);
			l++; r++;
			if(opt==1)
			{
//				puts("u0");
				tree.update(1,l,r,val);
//				puts("u1");
			}
			else
			{
//				puts("q0");
				printf("%d\n", tree.query(1,l,r,val));
//				puts("q1");
			}
		}
	}
	return 0;
}

void SegmentTree::build(int np, int nl, int nr)
{
	node &now=segt[np];
	now.l=nl;
	now.r=nr;
	now.setv=-1;
	now.col.clear();
	if(nl==nr)
	{
		now.col.insert(make_pair(inpt[nl], 1));
		return;
	}
	int mid=(nl+nr)>>1;
	build(np*2, nl, mid);
	build(np*2+1, mid+1, nr);
	maintain(np);
}

void SegmentTree::update(int np, int ql, int qr, int val)
{
	node &now=segt[np];
	if(ql<=now.l && now.r<=qr)
	{
		now.setv=val;
		maintain(np);
//		now.pri();
		return;
	}
	pushdown(np);
	int mid=(now.l+now.r)>>1;
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

int SegmentTree::query(int np, int ql, int qr, int val)
{
	node &now=segt[np];
	if(ql<=now.l && now.r<=qr)
	{
//		now.pri();
		return now.col[val];
	}
	pushdown(np);
	maintain(np*2);
	maintain(np*2+1);
	int mid=(now.l+now.r)>>1;
	int ans=0;
	if(ql<=mid)
	{
		ans += query(np*2, ql, qr, val);
	}
	if(qr>mid)
	{
		ans += query(np*2+1, ql, qr, val);
	}
	return ans;
};

void SegmentTree::pushdown(int np)
{
	node &now=segt[np];
	if(now.setv==-1) return;
	node &lson=segt[np*2];
	node &rson=segt[np*2+1];
	lson.setv=rson.setv=now.setv;
	now.setv=-1;
}

void SegmentTree::maintain(int np)
{
	node &now=segt[np];
	if(now.l==now.r)
	{
		if(~now.setv)
		{
			now.col.clear();
			now.col.insert( make_pair(now.setv, 1) );
		}
		now.setv=-1;
		return;
	}
	else
	{
		now.col.clear();
		if(~now.setv) 
		{
			now.col.insert( make_pair(now.setv, now.r-now.l+1) );
		}
		else
		{
			node &lson=segt[np*2], &rson=segt[np*2+1];
			for(mit it=lson.col.begin(); it!=lson.col.end(); it++)
			{
				now.col[ it->first ] += it->second;
			}
			for(mit it=rson.col.begin(); it!=rson.col.end(); it++)
			{
				now.col[ it->first ] += it->second;
			}	
		}
	}
}

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
#include <complex>
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

const int maxn=1e5+10, INF=0x3f3f3f3f;
const char chr[4] = {'e', 'a', 's', 'y'};
struct SegmentTree
{
	struct node
	{
		int l,r,sum,setv;
		void pri(){printf("l:%d r:%d sum:%d setv:%d\n", l, r, sum, setv);}
	} segt[maxn*4];
	void build(int,int,int);
	void clear(int,int,int);
	void update(int,int);
	int leftmost(int,int,int);
	int query(int,int,int);
	void maintain(int);
	void pushdown(int);
};
struct Query
{
	int l,r,id;
	bool operator < (const Query &rhs) const {return r < rhs.r;}
};

char str[maxn];
int near[maxn][4];
int N,Q;
int ans[maxn];
Query qry[maxn];
SegmentTree tree;

void expend(int);
int startE(int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%s", str+1))
	{
		N = strlen(str+1);
		tree.build(1,1,N);
		scanf("%d", &Q);
		for(int i=0; i<Q; i++) scanf("%d%d", &qry[i].l, &qry[i].r), qry[i].id=i;
		CLR(near[0]);
		for(int i=1; i<=N; i++)
		{
			for(int j=0; j<4; j++) near[i][j] = near[i-1][j];
			for(int j=0; j<4; j++) if(str[i] == chr[j]) {near[i][j] = i; break;}
		}
		sort(qry, qry+Q);
		int np=0;
		for(int q=0; q<Q; q++)
		{
			printf("%d %d\n", qry[q].l, qry[q].r);
			while(np<qry[q].r) expend(++np);
			int res = tree.query(1,qry[q].l,qry[q].r);
			printf("res: %d test:%d\n", res, tree.query(1,1,N));
			int temp;
			int lm = startE(temp=tree.leftmost(1,qry[q].l,qry[q].r)); // bug
			printf("lm: %d lef: %d\n", lm, temp);
			if(lm<qry[q].l && res) res--;
			ans[qry[q].id] = res;
		}
		for(int q=0; q<Q; q++) printf("%d\n", ans[q]);
	}
	return 0;
}

int startE(int np)
{
	if(np==INF) return 0;
	np = near[np][2];
	np = near[np][1];
	np = near[np][0];
	return np;
}

void expend(int np)
{
	if(str[np] != chr[3]) return;
	int lm = startE(np);
	if(!lm) return;
	printf("ex-lm: %d %d\n", lm, np);
	tree.clear(1,lm,np);
	tree.update(1,np);
}

void SegmentTree::build(int np, int nl, int nr)
{
	node &now = segt[np];
	now.l=nl; now.r=nr;
	now.setv=-1; now.sum=0;
	if(nl==nr) return;
	int mid = (nl+nr)>>1;
	build(np*2, nl, mid);
	build(np*2+1, mid+1, nr);
}

void SegmentTree::clear(int np, int ql, int qr)
{
	node &now = segt[np];
	if(ql<=now.l && now.r<=qr)
	{
		now.sum = now.setv = 0;
		return;
	}
	pushdown(np);
	int mid = (now.l+now.r)>>1;
	if(qr <= mid)
	{
		clear(np*2, ql, qr);
		maintain(np*2+1);
	}
	else if(ql > mid)
	{
		clear(np*2+1, ql, qr);
		maintain(np*2);
	}
	else
	{
		clear(np*2, ql, qr);
		clear(np*2+1, ql,qr);
	}
	maintain(np);
}

void SegmentTree::update(int np, int pos)
{
	node &now = segt[np];
	if(now.l == now.r){now.sum = 1; now.setv=-1;return;}
	pushdown(np);
	maintain(np*2);
	maintain(np*2+1);
	int mid = (now.l+now.r)>>1;
	if(pos<=mid) update(np*2, pos);
	else update(np*2+1, pos);
	maintain(np);
}

int SegmentTree::leftmost(int np, int ql, int qr)
{
	node &now = segt[np];
//	now.pri();
	if(now.l==now.r) return now.l;
	if(!now.sum) return INF;
	pushdown(np);
	int mid = (now.l+now.r)>>1;
	int tl, tr;
	if(qr<=mid)
	{
		maintain(np*2+1);
		tl = leftmost(np*2, ql, qr);
	}
	else if(ql > mid)
	{
		maintain(np*2);
		tr = leftmost(np*2+1, ql, qr);
	}
	else 
	{
		tl = leftmost(np*2, ql, qr);
		tr = leftmost(np*2+1, ql, qr);
	}
	maintain(np);
	return min(tl,tr);
}

int SegmentTree::query(int np, int ql, int qr)
{
	node &now = segt[np];
	if(ql<=now.l && now.r<=qr) return now.sum;
	pushdown(np);
	maintain(np*2); maintain(np*2+1);
	int mid = (now.l+now.r)>>1, res=0;
	if(ql<=mid) res += query(np*2, ql, qr);
	if(qr>mid)  res += query(np*2+1, ql, qr);
	return res;
}

void SegmentTree::pushdown(int np)
{
	node &now = segt[np];
	if(~now.setv)
	{
		node &lson = segt[np*2], &rson = segt[np*2+1];
		lson.setv = rson.setv = now.setv;
		now.setv = -1;
	}
}

void SegmentTree::maintain(int np)
{
	node &now = segt[np];
	if(now.l == now.r)
	{
		if(~now.setv)
		{
			now.sum = now.setv;
			now.setv = -1;
		}
	}
	else
	{
		node &lson = segt[np*2], &rson = segt[np*2+1];
		now.sum = lson.sum + rson.sum;
		if(~now.setv)
		{
			now.sum = now.setv;
		}
	}
}

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

const int maxn=2e5+10, MOD=72807249;
struct SegmentTree
{
	const static int maxn=2e5+10;
	struct node
	{
		int l,r,val;
	} segt[4*maxn];
	void build(int,int,int);
	void update(int,int,int);
	void maintain(int);
};

int N;
int sque[maxn];
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
		tree.build(1,1,N);
		
		for(int i=1; i<=N; i++)
		{
			int opt;
			scanf("%d%d", &opt, &sque[i]);
			if(opt==1) tree.update(1,i,sque[i]);
			else tree.update(1,sque[i],1);
			printf("%d\n", tree.segt[1].val);
		}
	}
	return 0;
}

void SegmentTree::build(int np, int nl, int nr)
{
	node &now=segt[np];
	now.l = nl;
	now.r = nr;
	now.val = 1;
	if(nl==nr) return;
	int mid=(nl+nr)>>1;
	build(np*2, nl, mid);
	build(np*2+1, mid+1, nr);
	return;
}

void SegmentTree::update(int np, int pos, int val)
{
	node &now=segt[np];
	if(now.l==now.r)
	{
		now.val=val;
		return;
	}
	int mid=(now.l+now.r)>>1;
	if(pos<=mid) update(np*2, pos, val);
	else update(np*2+1, pos, val);
	maintain(np);
}

void SegmentTree::maintain(int np)
{
	node &now=segt[np];
	node &lson=segt[np*2], &rson=segt[np*2+1];
	now.val = (LL)lson.val*rson.val%MOD; 
}

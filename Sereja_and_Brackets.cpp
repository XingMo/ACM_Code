/*
Codeforces - 380C
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

const int maxn=1e6+10;
struct SegmentTree
{
	struct node
	{
		int l,r,bl,br,res;
		node(){bl=br=res=0;}
	} segt[4*maxn];
	void build(int,int,int);
	node query(int,int,int);
};
char inpt[maxn];
SegmentTree tree;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	scanf("%s", inpt+1);
	tree.build(1,1,strlen(inpt+1));
	int Q,l,r;
	scanf("%d", &Q);
	for(int q=0; q<Q; q++)
	{
		scanf("%d%d", &l, &r);
		printf("%d\n", tree.query(1,l,r).res);
	}
	return 0;
}

void SegmentTree::build(int np, int nl, int nr)
{
	node &now=segt[np];
	now.l=nl;
	now.r=nr;
	if(nl==nr)
	{
		now.res=0;
		if(inpt[nl]=='('){now.bl=1; now.br=0;}
		else {now.bl=0; now.br=1;}
		return;
	}
	int mid=(nl+nr)>>1;
	build(np*2, nl, mid);
	build(np*2+1, mid+1, nr);
	node &lson=segt[np*2], &rson=segt[np*2+1];
	int cor = min(lson.bl, rson.br);
	now.res = lson.res + rson.res + 2*cor;
	now.bl = lson.bl + rson.bl - cor;
	now.br = lson.br + rson.br - cor;
}

SegmentTree::node SegmentTree::query(int np, int ql, int qr)
{
	node &now=segt[np];
	if(ql<=now.l && now.r<=qr)
	{
		return now;
	}
	int mid=(now.l+now.r)>>1;
	node res, lres, rres;
	if(ql<=mid) lres = query(np*2, ql, qr);
	if(qr>mid)  rres = query(np*2+1, ql, qr);
	int cor = min(lres.bl, rres.br);
	res.res = lres.res + rres.res + 2*cor;
	res.bl  = lres.bl + rres.bl - cor;
	res.br  = lres.br + rres.br - cor;
	return res;
}


/*
SPOJ - 3267
给定一个序列，询问区间内有多少个不同的数

这题有离线询问+树状数组的解法
这里是主席树的在线解法
基本思路和离线的一样，只不过在线了一下
能离线还是离线比较好
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

const int maxn=3e4+10, maxa=1e6+10, maxq=2e5+10;
struct PSegmentTree
{
	struct node
	{
		int ls,rs,sum;
	} segt[maxn*40];
	int siz,time,len,root[2*maxn];
	void init(int _n){siz=0; time=0; len=_n;}
	int update(int,int,int=-1,int=-1,int=-1);
	int query(int,int,int,int,int);
	void maintain(int);
};

int N, M, A[maxn], last[maxa];
int qt[maxn];
PSegmentTree pstree;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		CLR(last);
		pstree.init(N);
		for(int i=1; i<=N; i++)
		{
			scanf("%d", &A[i]);
			if(last[A[i]]) pstree.update(last[A[i]], -1);
			pstree.update(i, 1);
			last[A[i]] = i;
			qt[i] = pstree.root[pstree.time];
		}
		scanf("%d", &M);
		for(int i=1, l, r; i<=M; i++)
		{
			scanf("%d%d", &l, &r);
			printf("%d\n", pstree.query(l, r, qt[r], 1, N));
		}
	}
	return 0;
}

int PSegmentTree::update(int p, int v, int np, int nl, int nr)
{
	int tp = ++siz;
	if(np==-1)
	{
		np=root[time], nl=1, nr=len;
		root[++time]=tp;
	}
	node &now=segt[np], &to=segt[tp];
	to = now;
	
	if(nl==nr) {to.sum += v; return tp;}
	int mid=(nl+nr)>>1;
	if(p<=mid) to.ls = update(p, v, now.ls, nl, mid);
	else to.rs = update(p, v, now.rs, mid+1, nr);
	maintain(tp);
	return tp;
}

int PSegmentTree::query(int ql, int qr, int np, int nl, int nr)
{
	node &now = segt[np];
	if(ql<=nl && nr<=qr) return now.sum;
	int mid = (nl+nr)>>1, ans=0;
	if(ql<=mid) ans += query(ql, qr, now.ls, nl, mid);
	if(qr>mid)  ans += query(ql, qr, now.rs, mid+1, nr);
	return ans;
}

void PSegmentTree::maintain(int np)
{
	segt[np].sum = segt[segt[np].ls].sum + segt[segt[np].rs].sum;
}

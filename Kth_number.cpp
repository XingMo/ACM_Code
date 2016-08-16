/*
HDU - 2665
静态区间第 k大

这道题有很多种比主席树简单了一万倍的算法
不过作为主席树入门还是很合适的 orz

这题的具体做法就是，先离散化值，在建立权值线段树
从左到右扫一遍数组，对第 i个数，在 A[i]的位置 +1
然后询问 [l,r]的时候直接找出 l-1和 r这两个时间的主席树
根据左儿子值的个数，来决定接下来是往左走还是往右走
和整体二分一样，往右走的时候要减去左边的贡献

这个主席树和我以往的线段树风格不太一样，
所以注释一下免得忘记了
1. 首先一个节点所管到的区间范围不记录在 node里
而是边递归边算，这样是为了节省空间
2. 主席树每个节点初始值都是 0，可以不build
直接设 0为虚节点，然后 update时插入即可
所有不存在的点都正好指向了虚节点 0 （只要虚节点的左儿子和右儿子都指向自己）
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

const int maxn=1e5+10;
struct PSegmentTree
{
	struct node
	{
		int sum,ls,rs;
	} segt[maxn*4*10];
	int siz,time,len,root[maxn];
	void init(int _n){siz=0; time=0; len=_n;}
	int update(int,int,int=-1,int=-1,int=-1);
	int query(int,int,int,int,int);
	void maintain(int);
};
struct Discrete
{
	int ais[maxn],siz;
	void init(){sort(ais, ais+siz); siz = unique(ais, ais+siz)-ais;}
	void add(int _n){ais[siz++]=_n;}
	int id(int _n){return lower_bound(ais, ais+siz, _n)-ais + 1;}
};

int N,M,A[maxn];
Discrete D;
PSegmentTree pstree;

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
		
		D.siz=0;
		for(int i=1; i<=N; i++)
		{
			scanf("%d", &A[i]);
			D.add(A[i]);
		}
		D.init();
		
		pstree.init(D.siz);
		for(int i=1; i<=N; i++) pstree.update(D.id(A[i]), 1);
		for(int i=1,l,r,k; i<=M; i++)
		{
			scanf("%d%d%d", &l, &r, &k);
			int idx = pstree.query(pstree.root[l-1], pstree.root[r], 1, D.siz, k);
			printf("%d\n", D.ais[idx-1]);
		}
	}
	return 0;
}

int PSegmentTree::update(int p, int v, int np, int nl, int nr)
{
	int tp=++siz;
	if(np==-1) np=root[time], nl=1, nr=len;
	if(np==root[time]) root[++time]=tp;
	segt[tp] = segt[np];
	node &now = segt[np], &to = segt[tp];
	
	if(nl==nr) {to.sum += v; return tp;}
	int mid=(nl+nr)>>1;
	if(p<=mid) to.ls = update(p, v, now.ls, nl, mid);
	else to.rs = update(p, v, now.rs, mid+1, nr);
	maintain(tp);
	return tp;
}

int PSegmentTree::query(int tl, int tr, int nl, int nr, int k)
{
	if(nl==nr) return nl;
	int mid=(nl+nr)>>1;
	int res = segt[segt[tr].ls].sum - segt[segt[tl].ls].sum;
	if(res>=k) return query(segt[tl].ls, segt[tr].ls, nl, mid, k);
	else return query(segt[tl].rs, segt[tr].rs, mid+1, nr, k-res);
}

void PSegmentTree::maintain(int np)
{
	segt[np].sum = segt[segt[np].ls].sum + segt[segt[np].rs].sum;
}

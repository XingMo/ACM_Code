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

const int maxn = 5e4 + 4, maxm=1e6+4;

inline int gcd(int x, int y){return y?gcd(y, x%y):x;}

struct Cnt
{
	LL arr[maxm];
	int siz;
	void init(){memset(arr, 0, sizeof(arr)); siz=0;}
	void add(int p, LL x)
	{
		if(!arr[p]) siz++;
		arr[p]+=x; 
	}
	void del(int p, LL x)
	{
		arr[p]-=x;
		if(!arr[p]) siz--;
	}
};

struct SegmentTree
{
	struct node
	{
		int l,r,d;
	} segt[4*maxn];
	void build(int,int,int);
	void update(int,int,int);
	int query(int,int,int);
} tree;

struct SparseTable
{
	int st[22][maxn], siz, tlog;
	void init(int _siz, int arr[])
	{
		siz = _siz;
		tlog = log2(siz);
		for(int i=1; i<=siz; i++) st[0][i] = arr[i];
		for(int j=1; j<=tlog; j++)
		{
			int len=1<<(j-1), lim=siz-(1<<j)+1;
			for(int i=1; i<=lim; i++) st[j][i] = gcd(st[j-1][i], st[j-1][i+len]); 
		}
	}
	int query(int l, int r)
	{
		int flr=log2(r-l+1), len=1<<flr;
		return gcd(st[flr][l], st[flr][r-len+1]);
	}
} st;

int N,Q,in[maxn];
Cnt ans;
vector<Pii> tL, tR;

void init();
void work();
void get(int);

int main(){
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	#endif
	
	tL.resize(maxn); tR.resize(maxn);
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		ans.init();
		scanf("%d%d", &N, &Q);
		for(int i=1; i<=N; i++) scanf("%d", &in[i]);
		tree.build(1,1,N);
		init();
		printf("Case #%d:\n", ck);
		for(int q=0; q<Q; q++) work();
	}
	return 0;
}

void init()
{
	st.init(N, in);
	for(int i=1,p; i<=N; i++)
	{
		p = i;
		while(p <= N)
		{
			int d = st.query(i,p), l=p, r=N;
			while(l<r)
			{
				int mid = (l+r+1)>>1;
				if(st.query(i, mid) >= d) l = mid;
				else r = mid-1;
			}
			ans.add(d, l-p+1);
			p=l+1;
		}
	}
}

void get(int P)
{
	tL.clear(); tR.clear();
	int p = P;
	while(p <= N)
	{
		int d = tree.query(1,P,p), l=p, r=N;
		while(l<r)
		{
			int mid = (l+r+1)>>1;
			if(tree.query(1, P, mid) >= d) l = mid;
			else r = mid-1;
		}
		tR.push_back({d, l-p+1});
		p=l+1;
	}
	p = P;
	while(p >= 1)
	{
		int d = tree.query(1,p,P), l=1, r=p;
		while(l<r)
		{
			int mid = (l+r)>>1;
			if(tree.query(1, mid, P) >= d) r = mid;
			else l = mid+1;
		}
		tL.push_back({d, p-l+1});
		p=l-1;
	}
}

void work()
{
	int P,V;
	scanf("%d%d", &P, &V);
	get(P);
	for(auto &pr0:tL) for(auto &pr1:tR)
	{
		int d = gcd(pr0.first, pr1.first);
		LL x = (LL)pr0.second*pr1.second;
		ans.del(d, x);
	}
	tree.update(1, P, V);
	get(P);
	for(auto &pr0:tL) for(auto &pr1:tR)
	{
		int d = gcd(pr0.first, pr1.first);
		LL x = (LL)pr0.second*pr1.second;
		ans.add(d, x);
	}
	printf("%d\n", ans.siz);
}

void SegmentTree::build(int np, int nl, int nr)
{
	node &now = segt[np];
	now.l=nl; now.r=nr;
	if(nl==nr) {now.d = in[nl]; return;}
	int mid = (nl+nr)>>1;
	build(np*2, nl, mid);
	build(np*2+1, mid+1, nr);
	now.d = gcd(segt[np*2].d , segt[np*2+1].d); 
}

void SegmentTree::update(int np, int p, int v)
{
	node &now = segt[np];
	if(now.l==now.r) {now.d = v; return;}
	int mid = (now.l+now.r)>>1;
	if(p<=mid) update(np*2, p, v);
	else update(np*2+1, p, v);
	now.d = gcd(segt[np*2].d, segt[np*2+1].d);
}

int SegmentTree::query(int np, int ql, int qr)
{
	node &now = segt[np];
	if(ql<=now.l && now.r<=qr) return now.d;
	int mid = (now.l+now.r)>>1;
	if(qr<=mid) return query(np*2, ql, qr);
	else if(ql>mid)  return query(np*2+1, ql, qr);
	else return gcd(query(np*2, ql, qr), query(np*2+1, ql, qr));
}

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
#include <ctime>
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) ((a)*(a))

const int maxn=2e5+10;
int N,M,bsiz;
map<int,int> col[maxn];
int flag[maxn];
int inpt[maxn];

void pri()
{
	for(int i=0; i<N; i++)
	{
		int nc=inpt[i];
		if(~flag[i/bsiz]) nc=flag[i/bsiz];
		printf("%d ", nc); 
	}
	puts("");
}

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
//		bsiz=sqrt(N*log2(N)*log2(N));
		bsiz=316;
		for(int i=0; i<N; i++) scanf("%d", &inpt[i]);
		MST(flag,-1);
		for(int i=0; i<=N/bsiz; i++) col[i].clear();
		for(int i=0; i<N; i++)
		{
			int b=i/bsiz;
			col[b][inpt[i]]++;
		}
		for(int t=1; t<=M; t++)
		{
			int opt,l,r,v;
			scanf("%d%d%d%d", &opt, &l, &r, &v);
			int L=l/bsiz, R=r/bsiz;
			if(opt==1)
			{
				for(int i=L; i<=R; i++)
				{
					int nl=i*bsiz, nr=i*bsiz+bsiz-1;
					if(nr>=N) nr=N-1;
					if(l<=nl && nr<=r)
					{
						col[i].clear();
						flag[i]=v;
						col[i].insert(make_pair(v,bsiz));
					}
					else
					{
						if(~flag[i])
						{
							for(int j=nl; j<=nr; j++) inpt[j]=flag[i];
							flag[i]=-1;
						}
						int tl=max(l,nl), tr=min(r,nr);
						for(int j=tl; j<=tr; j++)
						{
							map<int,int>::iterator it=col[i].find(inpt[j]);
							it->second-=1;
							if(it->second==0) col[i].erase(it);
							inpt[j]=v;
						}
						col[i][v] += tr-tl+1;
					}
				}
			}
			else
			{
				int ans=0;
				for(int i=L; i<=R; i++)
				{
					int nl=i*bsiz, nr=i*bsiz+bsiz-1;
					if(nr>=N) nr=N-1;
					if(l<=nl && nr<=r) ans += col[i][v];
					else
					{
						int tl=max(l,nl), tr=min(r,nr);
						if(~flag[i])
						{
							if(flag[i]==v) ans += tr-tl+1;
						}
						else for(int j=tl; j<=tr; j++) if(inpt[j]==v) ans++;
					}
				}
				printf("%d\n", ans);
			}
		}
	}
	return 0;
}

//#pragma comment(linker, "/STACK:102400000,102400000")
//#include <cstdio>
//#include <iostream>
//#include <cstdlib>
//#include <cstring>
//#include <algorithm>
//#include <cmath>
//#include <cctype>
//#include <map>
//#include <set>
//#include <queue>
//using namespace std;
//typedef pair<int,int> Pii;
//typedef long long LL;
//typedef unsigned long long ULL;
//typedef double DBL;
//typedef long double LDBL;
//#define MST(a,b) memset(a,b,sizeof(a))
//#define CLR(a) MST(a,0)
//#define Sqr(a) ((a)*(a))

//typedef map<int,int>::iterator mit;

//const int maxn=1e5+10;
//struct SegmentTree
//{
//	struct node
//	{
//		int l,r, setv;
//		map<int,int> col;
//		void pri()
//		{ 
//			printf("l:%d r:%d s:%d\n", l, r, setv);
//			for(mit it=col.begin(); it!=col.end(); it++)
//			{
//				printf("%d: %d\n", it->first, it->second);
//			}
//		}
//	} segt[4*maxn];
//	void build(int,int,int);
//	void update(int,int,int,int);
//	int query(int,int,int,int);
//	void maintain(int);
//	void pushdown(int);
//};
//int N,M;
//int inpt[maxn];
//SegmentTree tree;

//int main()
//{
//	#ifdef LOCAL
//	freopen("in.txt", "r", stdin);
////	freopen("out.txt", "w", stdout);
//	#endif
//	
//	int T;
//	scanf("%d", &T);
//	for(int ck=1; ck<=T; ck++)
//	{
//		scanf("%d%d", &N, &M);
//		for(int i=1; i<=N; i++) scanf("%d", &inpt[i]);
//		tree.build(1,1,N);
//		for(int i=1; i<=M; i++)
//		{
//			int opt, l, r, val;
//			scanf("%d%d%d%d", &opt, &l, &r, &val);
//			l++; r++;
//			if(opt==1)
//			{
////				puts("u0");
//				tree.update(1,l,r,val);
////				puts("u1");
//			}
//			else
//			{
////				puts("q0");
//				printf("%d\n", tree.query(1,l,r,val));
////				puts("q1");
//			}
//		}
//	}
//	return 0;
//}

//void SegmentTree::build(int np, int nl, int nr)
//{
//	node &now=segt[np];
//	now.l=nl;
//	now.r=nr;
//	now.setv=-1;
//	now.col.clear();
//	if(nl==nr)
//	{
//		now.col.insert(make_pair(inpt[nl], 1));
//		return;
//	}
//	int mid=(nl+nr)>>1;
//	build(np*2, nl, mid);
//	build(np*2+1, mid+1, nr);
//	maintain(np);
//}

//void SegmentTree::update(int np, int ql, int qr, int val)
//{
//	node &now=segt[np];
//	if(ql<=now.l && now.r<=qr)
//	{
//		now.setv=val;
//		maintain(np);
////		now.pri();
//		return;
//	}
//	pushdown(np);
//	int mid=(now.l+now.r)>>1;
//	if(qr<=mid)
//	{
//		update(np*2, ql, qr, val);
//		maintain(np*2+1);
//	}
//	else if(ql>mid)
//	{
//		update(np*2+1, ql, qr, val);
//		maintain(np*2);
//	}
//	else
//	{
//		update(np*2, ql, qr, val);
//		update(np*2+1, ql, qr, val);
//	}
//	maintain(np);
//}

//int SegmentTree::query(int np, int ql, int qr, int val)
//{
//	node &now=segt[np];
//	if(ql<=now.l && now.r<=qr)
//	{
////		now.pri();
//		return now.col[val];
//	}
//	pushdown(np);
//	maintain(np*2);
//	maintain(np*2+1);
//	int mid=(now.l+now.r)>>1;
//	int ans=0;
//	if(ql<=mid)
//	{
//		ans += query(np*2, ql, qr, val);
//	}
//	if(qr>mid)
//	{
//		ans += query(np*2+1, ql, qr, val);
//	}
//	return ans;
//};

//void SegmentTree::pushdown(int np)
//{
//	node &now=segt[np];
//	if(now.setv==-1) return;
//	node &lson=segt[np*2];
//	node &rson=segt[np*2+1];
//	lson.setv=rson.setv=now.setv;
//	now.setv=-1;
//}

//void SegmentTree::maintain(int np)
//{
//	node &now=segt[np];
//	if(now.l==now.r)
//	{
//		if(~now.setv)
//		{
//			now.col.clear();
//			now.col.insert( make_pair(now.setv, 1) );
//		}
//		now.setv=-1;
//		return;
//	}
//	else
//	{
//		now.col.clear();
//		if(~now.setv) 
//		{
//			now.col.insert( make_pair(now.setv, now.r-now.l+1) );
//		}
//		else
//		{
//			node &lson=segt[np*2], &rson=segt[np*2+1];
//			for(mit it=lson.col.begin(); it!=lson.col.end(); it++)
//			{
//				now.col[ it->first ] += it->second;
//			}
//			for(mit it=rson.col.begin(); it!=rson.col.end(); it++)
//			{
//				now.col[ it->first ] += it->second;
//			}	
//		}
//	}
//}

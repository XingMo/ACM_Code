#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <climits>
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) (a*a)

int debug;

const int maxn=5e4+10, INF=INT_MAX;
#define BIRD 0
#define WALL 1

struct Object
{
	int u,v,h,id,flag;
	bool operator < (const Object &v) const {return h < v.h;}
};

struct Discrete
{
	int *arry,siz;
	Discrete(int tsiz=maxn*6){siz=0; arry=new int[tsiz];}
	~Discrete(){delete []arry;}
	int id(int x){return lower_bound(arry, arry+siz, x) - arry;}
	int pos(int x){return arry[x];}
	void init()
	{
		sort(arry, arry+siz);
		siz=unique(arry, arry+siz) - arry;
	}
	void add(int x){arry[siz++]=x;}
};

struct SegmentTree
{
	struct node
	{
		int l,r,h,id;
		void pri(const char *a="\n"){printf("l:%d r:%d %s", l, r, a);};
	} *segt;
	SegmentTree(int siz){segt=new node[4*siz];}
	~SegmentTree(){delete []segt;}
	
	void build(int,int,int);
	Pii query(int,int);
	void update(int,int,int,int,int);
	void pushdown(int);
	void maintain(int);
};

int N,M;
int isiz[2];
Object inpt[2][6*maxn];
Discrete ais[2];

int bird[2][maxn];
int wall[maxn];

SegmentTree tree(6*maxn);

void addw(int,int,int,int,int,int);
void Scan(int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		ais[0].siz=ais[1].siz=0;
		isiz[0]=isiz[1]=0;
		MST(bird[0],0x3f); MST(bird[1],-1);
		CLR(wall);
		
		for(int i=0; i<N; i++)
		{
			int x1,y1,x2,y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			if(y1==y2) 
			{
				addw(0,x1,x2,y1,i,WALL);
				addw(1,y1,y1,x1,i,WALL);
				addw(1,y1,y1,x2,i,WALL);
			}
			else
			{
				addw(1,y1,y2,x1,i,WALL);
				addw(0,x1,x1,y1,i,WALL);
				addw(0,x1,x1,y2,i,WALL);
			}
			
			ais[0].add(x1); ais[0].add(x2);
			ais[1].add(y1); ais[1].add(y2);
		}
		
//		puts("X:");
//		for(int i=0; i<isiz[0]; i++) printf("%d %d %d\n", inpt[0][i].u, inpt[0][i].v, inpt[0][i].h);
//		puts("Y:");
//		for(int i=0; i<isiz[1]; i++) printf("%d %d %d\n", inpt[1][i].u, inpt[1][i].v, inpt[1][i].h);
		
		for(int i=0; i<M; i++)
		{
			int x,y;
			scanf("%d%d", &x, &y);
			addw(0,x,x,y,i,BIRD);
			addw(1,y,y,x,i,BIRD);
			
			ais[0].add(x);
			ais[1].add(y);
		}
		
		ais[0].init(); ais[1].init();
		
		sort(inpt[0], inpt[0]+isiz[0]);
		sort(inpt[1], inpt[1]+isiz[1]);
		
		Scan(0);
		Scan(1);
		
		reverse(inpt[0], inpt[0]+isiz[0]);
		reverse(inpt[1], inpt[1]+isiz[1]);
		
		Scan(0);
		Scan(1);
		
		for(int i=0; i<M; i++) if(~bird[1][i]) wall[bird[1][i]]++;
		
		for(int i=0; i<N; i++) printf("%d\n", wall[i]);
	}
}

void addw(int flr, int u, int v, int h, int id, int flag)
{
	if(u>v) swap(u,v);
	inpt[flr][isiz[flr]].u = u;
	inpt[flr][isiz[flr]].v = v;
	inpt[flr][isiz[flr]].h = h;
	inpt[flr][isiz[flr]].id = id;
	inpt[flr][isiz[flr]].flag = flag;
	isiz[flr]++;
}

void Scan(int flr)
{
	tree.build(1,0,ais[flr].siz);
	for(int i=0; i<isiz[flr]; i++)
	{
//		if(debug)
//		{
//			Object &now=inpt[flr][i];
//			puts((inpt[flr][i].flag==WALL)?"wall":"bird");
//			printf("%d: %d %d %d\n", now.id, now.u, now.v, now.h);
//		}
		if(inpt[flr][i].flag == WALL)
		{
			tree.update(1, ais[flr].id(inpt[flr][i].u), ais[flr].id(inpt[flr][i].v), inpt[flr][i].id, inpt[flr][i].h);
		}
		else
		{
//			if(debug) 
//			{
//				printf("%d\n", ais[flr].siz);
//				for(int i=0; i<ais[flr].siz; i++) printf("%d ", tree.query(1,i).first);puts("");
//				for(int i=0; i<ais[flr].siz; i++) printf("%d ", tree.query(1,i).second);puts("");
//			}
			Pii info=tree.query(1, ais[flr].id(inpt[flr][i].u));
			if(info.first==-1) continue;
//			if(debug) printf("wid=%d\n", info.first);
			int res, id;
			id=inpt[flr][i].id;
			res=abs(inpt[flr][i].h - info.second);
			if(res < bird[0][id])
			{
				bird[0][id] = res;
				bird[1][id] = info.first;
			}
		}
	}
}

void SegmentTree::build(int np, int nl, int nr)
{
	node &now=segt[np];
	now.l=nl;
	now.r=nr;
	now.id=-1;
	if(nl==nr) return;
	int mid=(nl+nr)>>1;
	build(np*2, nl, mid);
	build(np*2+1, mid+1, nr);
}

Pii SegmentTree::query(int np, int ql)
{
	node &now=segt[np];
	if(now.l==now.r) return make_pair(now.id, now.h);
	pushdown(np);
	int mid=(now.l+now.r)>>1;
	if(ql<=mid) return query(np*2, ql);
	else return query(np*2+1, ql);
}

void SegmentTree::update(int np, int ql, int qr, int tid, int th)
{
	node &now=segt[np];
	
	if(ql<=now.l && now.r<=qr)
	{
		now.id=tid;
		now.h=th;
		return;
	}
	pushdown(np);
	int mid=(now.l+now.r)>>1;
	if(ql<=mid) update(np*2,ql,qr,tid,th);
	if(qr>mid) update(np*2+1,ql,qr,tid,th);
}

void SegmentTree::pushdown(int np)
{
	node &now=segt[np];
	if(now.id==-1) return;
	node &lson=segt[np*2];
	node &rson=segt[np*2+1];
	lson.id=rson.id=now.id;
	lson.h=rson.h=now.h;
	now.id=-1;
}

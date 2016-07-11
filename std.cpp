#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
using namespace std;
typedef pair<int,int> Pii;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define LL long long
#define ULL unsigned long long
int maxx(int a,int b){return a>b?a:b;}
int minn(int a,int b){return a<b?a:b;}
int abss(int a){return a<0?(-a):a;}

const int INF=0x3f3f3f3f;
struct stnode
{
	int l,r,tmax,tmin;
	int neg;
	void pri(){printf("l:%d r:%d tmax:%d tmin:%d neg:%d\n", l, r, tmax, tmin, neg);
	}
};
const int maxn=1e4+10;
int N,M,dfst;
int edge[2*maxn][4];
int last[maxn];

int dept[maxn]; // depth of node
int size[maxn]; // size of node
int fath[maxn]; // father of node
int hedg[maxn]; // heavy-edge of node
int ntop[maxn]; // top of node
int dfsn[maxn]; // dfs-num of node

int sque[maxn]; // initial sequence
stnode segt[4*maxn]; // segement-tree

void adde(int,int,int,int);
void dfs1(int,int,int);
void dfs2(int,int,int,int);

void build(int,int,int);
void setval(int,int,int);
void negval(int,int,int);
int query(int,int,int);
void pushdown(int);
void maintain(int);
void swap(int&,int&);
void negswap(int&,int&);

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
		dfst=0;
		CLR(last);CLR(dept);CLR(size);CLR(fath);CLR(hedg);CLR(ntop);CLR(dfsn);CLR(sque);
		CLR(segt);
		scanf("%d%d", &N, &M);
		for(int i=1; i<N; i++)
		{
			int u,v,w;
			scanf("%d%d%d", &u, &v, &w);
			adde(u,v,w,i);adde(v,u,w,i+N);
		}
		dfs1(1,0,1);
		dfs2(1,0,0,1);
		build(1,2,dfst);
		char str[10];
//		for(int i=1; i<=N; i++) printf("%d ", dfsn[i]);puts("");
		for(int i=0; i<M; i++)
		{
			int opt,l,r;
			scanf("%d%d%d", &opt, &l, &r);
			if(opt==1)
			{
				int u=edge[l][0],v=edge[l][1];
				if(dept[u]>dept[v]) v=u;
				setval(1,dfsn[v],r);
			}
			else if(opt==3)
			{
				int u=l,v=r;
				int ans=-INF;
				while(v!=u)
				{
					if(ntop[u]!=ntop[v])
					{
						if(dept[ntop[u]]>dept[ntop[v]]) swap(u,v);
//						printf("pre: u:%d v:%d\n", u, v);
						int nt=ntop[v];
						if(nt==1) nt=edge[hedg[nt]][1];
//						printf("nans:%d\n", query(1,dfsn[nt],dfsn[v]));
						ans=maxx(ans,query(1,dfsn[nt],dfsn[v]));
						v=fath[nt];
					}
					else
					{
						if(dept[u]>dept[v]) swap(u,v);
						u=edge[hedg[u]][1];
//						printf("nans:%d\n", query(1,dfsn[u],dfsn[v]));
						ans=maxx(ans,query(1,dfsn[u],dfsn[v]));
						v=u;
					}
//					printf("u:%d v:%d ans:%d\n", u, v, ans);system("pause");
				}
				printf("%d\n", ans);
			}
			else
			{
				int u=l,v=r;
				while(v!=u)
				{
					if(ntop[u]!=ntop[v])
					{
						if(dept[ntop[u]]>dept[ntop[v]]) swap(u,v);//printf("pre: u:%d v:%d\n", u, v);
						int nt=ntop[v];
						if(nt==1) nt=edge[hedg[nt]][1];
						negval(1,dfsn[nt],dfsn[v]);
						v=fath[nt];
					}
					else
					{
						if(dept[u]>dept[v]) swap(u,v);
						u=edge[hedg[u]][1];
						negval(1,dfsn[u],dfsn[v]);
						v=u;
					}
//					printf("u:%d v:%d\n", u, v);system("pause");
				}
			}
		}
	}
	return 0;
}

void adde(int u, int v, int w, int i)
{
	edge[i][0]=u;
	edge[i][1]=v;
	edge[i][2]=w;
	edge[i][3]=last[u];
	last[u]=i;
}

void dfs1(int u, int f, int d)
{
	fath[u]=f;
	dept[u]=d;
	size[u]=1;
	int tmax=-1;
	for(int e=last[u]; e; e=edge[e][3])
	{
		int v=edge[e][1];
		if(v==f) continue;
		dfs1(v,u,d+1);
		if(tmax<size[v])
		{
			tmax=size[v];
			hedg[u]=e;
		}
		size[u]+=size[v];
	}
	return;
}

void dfs2(int u,int f,int val,int top)
{
	dfsn[u]=++dfst;
	sque[dfst]=val;
	ntop[u]=top;
	if(!hedg[u]) return;
	int v,w;
	v=edge[hedg[u]][1];
	w=edge[hedg[u]][2];
	dfs2(v,u,w,top);
	for(int e=last[u]; e; e=edge[e][3])
	{
		v=edge[e][1];
		w=edge[e][2];
		if(v==f||e==hedg[u]) continue;
		dfs2(v,u,w,v);
	}
	return;
}

void build(int np, int nl, int nr)
{
	stnode &now=segt[np];
	now.l=nl;
	now.r=nr;
	now.neg=0;
	if(nl==nr){now.tmax=now.tmin=sque[nl];return;}
	int mid=(nl+nr)>>1;
	build(np*2,nl,mid);
	build(np*2+1,mid+1,nr);
	now.tmax=maxx(segt[np*2].tmax,segt[np*2+1].tmax);
	now.tmin=minn(segt[np*2].tmin,segt[np*2+1].tmin);
}

void setval(int np, int ql, int val)
{
	stnode &now=segt[np];
//	printf("np:%d ql:%d val:%d\n", np, ql, val);now.pri();system("pause");
	if(now.l==now.r)
	{
		now.tmax=now.tmin=val;
		now.neg=0;
		return;
	}
	pushdown(np);
	int mid=(now.l+now.r)>>1;
	if(ql<=mid)
	{
		setval(np*2,ql,val);
		maintain(np*2+1);
	}
	else if(ql>mid)
	{
		setval(np*2+1,ql,val);
		maintain(np*2);
	}
	else
	{
		setval(np*2,ql,val);
		setval(np*2+1,ql,val);
	}
	maintain(np);
}

void negval(int np, int ql, int qr)
{
	stnode &now=segt[np];
//	printf("np:%d ql:%d val:%d neg:%d\n", np, ql, val, neg);now.pri();system("pause");
	if(ql<=now.l&&now.r<=qr)
	{
		now.neg+=1;
		maintain(np);
		return;
	}
	pushdown(np);
	int mid=(now.l+now.r)>>1;
	if(qr<=mid)
	{
		negval(np*2,ql,qr);
		maintain(np*2+1);
	}
	else if(ql>mid)
	{
		negval(np*2+1,ql,qr);
		maintain(np*2);
	}
	else
	{
		negval(np*2,ql,qr);
		negval(np*2+1,ql,qr);
	}
	maintain(np);
}

int query(int np, int ql, int qr)
{
	stnode &now=segt[np];
//	printf("np:%d ql:%d qr:%d\n", np, ql, qr);now.pri();system("pause");
	maintain(np);
	if(ql<=now.l&&now.r<=qr)
	{
		return now.tmax;
	}
	pushdown(np);
	int mid=(now.l+now.r)>>1;
	if(qr<=mid)
	{
		maintain(np*2+1);
		return query(np*2,ql,qr);
	}
	else if(ql>mid)
	{
		maintain(np*2);
		return query(np*2+1,ql,qr);
	}
	else
	{
		return maxx( query(np*2,ql,qr), query(np*2+1,ql,qr));
	}
}

void pushdown(int np)
{
	stnode &now=segt[np];
	stnode &lson=segt[np*2];
	stnode &rson=segt[np*2+1];
	if(!now.neg) return;
	lson.neg+=now.neg;
	rson.neg+=now.neg;
	now.neg=0;
}

void maintain(int np)
{
	stnode &now=segt[np];
	if(now.l==now.r)
	{
		if(now.neg&1)
		{
			negswap(now.tmax,now.tmin);
		}
		now.neg=0;
	}
	else
	{
		int mid=(now.l+now.r)>>1;
		stnode &lson=segt[np*2];
		stnode &rson=segt[np*2+1];
		now.tmax=maxx(lson.tmax,rson.tmax);
		now.tmin=minn(lson.tmin,rson.tmin);
		now.neg&=1;
		if(now.neg)
		{
			negswap(now.tmax,now.tmin);
		}
	}
}

void negswap(int &u, int &v)
{
	int nmax=-u,nmin=-v;
	u=maxx(nmax,nmin);
	v=minn(nmax,nmin);
}

void swap(int &u, int &v)
{
	int tem=u;
	u=v;
	v=tem;
}

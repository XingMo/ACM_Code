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

const int maxn=1e5+10;
struct data
{
	int t,l,r,v;
};
struct Discrete
{
	int siz, ais[2*maxn];
	void add(int n){ais[siz++] = n;}
	void init()
	{
		sort(ais, ais+siz);
		siz = unique(ais, ais+siz) - ais;
	}
	int id(int n)
	{
		int p = lower_bound(ais, ais+siz, n) - ais + 1;
//		if(p>=siz || ais[p]!=n) return -1;
		return p;
	}
};
struct BIT
{
	int siz, bit[2*maxn];
	void init(int tn){siz=tn; CLR(bit);}
	void add(int p, int n)
	{
		for(int i=p; i<=siz; i+=i&-i) bit[i]+=n;
	}
	int sum(int p)
	{
		int res=0;
		for(int i=p; i>0; i-=i&-i) res+=bit[i];
		return res;
	}
};

int Q;
data arry[maxn], temp[maxn];
int inpt[maxn][3];
int ans[maxn];
BIT bit;
Discrete D;

void CDQ(int,int);

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
		scanf("%d", &Q);
		D.siz=0;
		CLR(ans);
		
		int scnt=0;
		for(int i=1; i<=Q; i++)
		{
			int opt,l,r;
			scanf("%d%d", &opt, &l);
			arry[i].t=i;
			if(!opt)
			{
				scanf("%d", &r);
				scnt++;
				inpt[scnt][0] = l;
				inpt[scnt][1] = r;
				inpt[scnt][2] = i;
				arry[i].l = l;
				arry[i].r = r;
				arry[i].v = 1;
				D.add(l); D.add(r);
			}
			else
			{
				arry[i].l = inpt[l][0];
				arry[i].r = inpt[l][1];
				arry[i].v = -1;
			}
		}
		D.init();
		bit.init(D.siz);
		for(int i=1; i<=Q; i++)
		{
			arry[i].l = D.id(arry[i].l);
			arry[i].r = D.id(arry[i].r);
		}
		
		CDQ(1,Q);
		
		for(int i=1; i<=scnt; i++) printf("%d\n", ans[ inpt[i][2] ]);
	}
	return 0;
}

void CDQ(int nl, int nr)
{
	if(nl>=nr) return;
	int mid=(nl+nr)>>1;
	CDQ(nl, mid); CDQ(mid+1,nr);
	
	int tl=mid;
	for(int tr=nr; tr>mid; tr--)
	{
		while(tl>=nl && arry[tl].l >= arry[tr].l)
		{
			bit.add( arry[tl].r, arry[tl].v);
			tl--;
		}
		ans[ arry[tr].t ] += bit.sum( arry[tr].r );
	}
	for(int i=mid; i>tl; i--) bit.add( arry[i].r, -arry[i].v);
	
	tl=nl;
	int tp=nl;
	for(int tr=mid+1; tr<=nr; tr++)
	{
		while(tl<=mid && arry[tl].l < arry[tr].l) temp[tp++] = arry[tl++];
		temp[tp++] = arry[tr];
	}
	while(tl<=mid) temp[tp++] = arry[tl++];
	
	for(int i=nl; i<=nr; i++) arry[i]=temp[i];
}


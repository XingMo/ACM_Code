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

const int maxn=1e5+10;
struct Discrete
{
	int ais[maxn], siz;
	void init()
	{
		sort(ais, ais+siz);
		siz = unique(ais, ais+siz) - ais;
	}
	void add(int _n){ais[siz++] = _n;}
	int id(int _n) {return lower_bound(ais, ais+siz, _n)-ais+1;}
};
struct data
{
	int t,x,v,id;
	bool operator < (const data &rhs) const {return t<rhs.t;}
};

int N;
data Q[maxn], temp[maxn];
int ans[maxn], typ[maxn], cnt[maxn];
Discrete D;

void CDQ(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		CLR(ans); CLR(cnt);
		D.siz=0;
		for(int i=1; i<=N; i++)
		{
			Q[i].id=i;
			scanf("%d%d%d", &typ[i], &Q[i].t, &Q[i].x);
			if(typ[i]==1) Q[i].v = 1;
			if(typ[i]==2) Q[i].v = -1;
			if(typ[i]==3) Q[i].v = 0;
			D.add(Q[i].x);
		}
		D.init();
		for(int i=1; i<=N; i++) Q[i].x = D.id(Q[i].x);
		CDQ(1,N);
		for(int i=1; i<=N; i++) if(typ[i]==3) printf("%d\n", ans[i]); 
	}
	return 0;
}

void CDQ(int l, int r)
{

	//-----------
//	puts("begin:");
//	printf("l:%d r:%d\n", l, r);
//	for(int i=l; i<=r; i++) printf("t:%d x:%d v:%d\n", Q[i].t, Q[i].x, Q[i].v);
//	PCUT;
	
	if(l>=r) return;
	int mid=(l+r)>>1;
	CDQ(l,mid); CDQ(mid+1,r);
	
	int nl=l,nr=mid+1;
	for(; nr<=r; nr++)
	{
		while(nl<=mid && Q[nl].t < Q[nr].t)
		{
			cnt[Q[nl].x] += Q[nl].v;
			nl++;
		}
		ans[Q[nr].id] += cnt[Q[nr].x];
	}
	for(int i=l; i<nl; i++) cnt[Q[i].x] -= Q[i].v;
	
	nl=l, nr=mid+1;
	int np=l;
	for(; nr<=r; nr++)
	{
		while(nl<=mid && Q[nl].t < Q[nr].t) temp[np++] = Q[nl++];
		temp[np++] = Q[nr];
	}
	for(; nl<=mid; nl++) temp[np++] = Q[nl];
	for(int i=l; i<=r; i++) Q[i] = temp[i];
	
	//-----------------
//	printf("l:%d r:%d\n", l, r);
//	for(int i=l; i<=r; i++) printf("t:%d x:%d v:%d\n", Q[i].t, Q[i].x, Q[i].v);
//	PCUT;
}


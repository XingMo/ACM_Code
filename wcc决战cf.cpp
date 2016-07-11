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
#include <cassert>
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) ((a)*(a))

const int maxn=3e4+10;
struct data
{
	int l,r,id;
	data(int a,int b,int c):l(a),r(b),id(c){}
};

struct Modui
{
	int n, bsiz;
	ULL res[maxn];
	vector<data> Q;
	void init(int tn)
	{
		n=tn;
		bsiz=sqrt(n);
		Q.clear();
	}
	ULL val(int,int,int);
	void solve();
};

int N,M;
ULL A[maxn];
ULL psum[64][maxn];
ULL pow2[64];
Modui mo;
bool cmp(data x, data y)
{
//	assert(mo.bsiz!=0);
	if(x.l/mo.bsiz != y.l/mo.bsiz) return x.l/mo.bsiz < y.l/mo.bsiz;
	return x.r < y.r;
}

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	#endif
	
	pow2[0]=1;
	for(int i=1; i<64; i++) pow2[i]=pow2[i-1]<<1;
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		scanf("%d%d", &N, &M);
		mo.init(N);
		for(int i=1; i<=N; i++)
		{
			scanf("%llu", &A[i]);
			A[i]^=A[i-1];
			for(int j=0; j<64; j++)
			{
				psum[j][i]=psum[j][i-1];
				if(A[i]&pow2[j]) psum[j][i]++;
			}
		}
//		assert(mo.Q.size()==0);
//		puts("done");
		for(int i=1; i<=M; i++)
		{
			int l,r;
			scanf("%d%d", &l, &r);
			mo.Q.push_back(data(l,r,i));
		}
		sort(mo.Q.begin(), mo.Q.end(), cmp);
		mo.solve();
		for(int i=1; i<=M; i++) printf("%llu\n", mo.res[i]);
	}
	return 0;
}

ULL Modui::val(int p, int l, int r)
{
//	assert(p>=0&&p<=N);
//	assert(l>=0&&l<=N);
//	assert(r>=0&&r<=N);
	ULL sum=0;
	for(int i=0; i<64; i++)
	{
		ULL pl=0;
		if(l-1>=0) pl = psum[i][l-1];
		ULL cnt=psum[i][r]-pl;
		if(A[p]&pow2[i]) cnt=r-l+1-cnt;
		sum+=pow2[i]*cnt;
	}
	return sum;
}

void Modui::solve()
{
	// [nl-1, nr]
	ULL sum=A[1];
	int nl=1,nr=1;
	for(int i=0; i<(int)Q.size(); i++)
	{
		int ql=Q[i].l, qr=Q[i].r;
		while(nr<qr)
		{
			sum+=val(nr+1, nl-1, nr);
			nr++;
		}
		while(nl>ql)
		{
			sum+=val(nl-2, nl-1, nr);
			nl--;
		}
		while(nr>qr)
		{
			sum-=val(nr, nl-1, nr);
			nr--;
		}
		while(nl<ql)
		{
			sum-=val(nl-1, nl-1, nr);
			nl++;
		}
//		assert(Q[i].id>0 && Q[i].id<=M);
		res[Q[i].id]=sum;
	}
}


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

const int maxn=1500, MOD=110119;

int R;
LL N, M;
LL fact[2*MOD+10];
pair<LL,LL> P[maxn];
LL val[maxn];

LL Pow(LL,LL,LL);
LL lucas(LL,LL,LL);
bool Get(LL,LL,LL,LL,LL&,LL&);

bool cmp(pair<LL,LL> x, pair<LL,LL> y)
{
	return (x.first+x.second)/3 < (y.first+y.second)/3;
}

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	fact[0]=1;
	for(int i=1; i<MOD+10; i++) fact[i] = (LL)fact[i-1]*i%MOD;
	
	int ck=0;
	while(~scanf("%lld%lld%d", &N, &M, &R))
	{
		ck++;
		printf("Case #%d: ", ck);
		N--; M--;
		int bcnt=0;
		LL x,y,r,c;
		for(int i=0; i<R; i++) 
		{
			scanf("%lld%lld", &x, &y);
			if(!Get(0,0,x-1,y-1,r,c)) continue;
			P[bcnt++] = {x-1, y-1};
		}
		if(!Get(0,0,N,M,r,c)) {printf("0\n"); continue;}
		P[bcnt++] = {N,M};
		sort(P, P+bcnt, cmp);
		
		for(int i=0; i<bcnt; i++)
		{
			Get(0,0, P[i].first, P[i].second, r, c);
			val[i] = lucas(r,c,MOD);
		}
		
		for(int i=0; i<bcnt; i++)
		{
			for(int j=i+1; j<bcnt; j++)
			{
				if(!Get(P[i].first, P[i].second, P[j].first, P[j].second, r, c)) continue;
				val[j] = (val[j] - val[i]*lucas(r,c,MOD)%MOD) %MOD;
			}
		}
		
		LL ans=0;
		for(int i=bcnt-1; i>=0; i--) if(P[i].first==N && P[i].second==M)
		{
			ans = val[i];
			break;
		}
		printf("%lld\n", (ans+MOD)%MOD);
		// + MOD
	}	
	return 0;
}


LL Pow(LL x, LL n, LL p)
{
	LL res=1;
	while(n)
	{
		if(n&1) res = x*res%p;
		x = x*x%p;
		n>>=1;
	}
	return res;
}

LL lucas(LL n, LL k, LL p)
{
    if(n==0) return 1;
    LL tn=n%p, tk=k%p;
    if(tn<tk) return 0;
    return fact[tn] * Pow(fact[tk]*fact[tn-tk]%p, p-2, p)%MOD * lucas(n/p, k/p, p) %MOD;
}

bool Get(LL a, LL b, LL n, LL m, LL &r, LL &c)
{
	if((3+n+m-a-b)%3!=0) return 0;
	r = (3+n+m-a-b)/3;
	c = m+2-b-r;
	r--; c--;
	if(c>=0 && c<=r && r>=0) return 1;
	else return 0;
}


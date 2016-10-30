/*
HDU - 3461
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

const int maxm=1e3+10, MOD=1000000007;
struct Discrete
{
	int ais[maxm*2], siz;
	void init()
	{
		sort(ais, ais+siz);
		siz = unique(ais, ais+siz) - ais;
	}
	void add(int _n){ais[siz++]=_n;}
	int id(int _n){return lower_bound(ais, ais+siz, _n)-ais+1;}
};

int N,M;
int in[maxm][2];
Discrete D;
int unin[maxm*2];

int uf(int x){return x==unin[x]?x:(unin[x] = uf(unin[x]));}
int Pow(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		D.siz = 0;
		for(int i=0; i<M; i++)
		{
			scanf("%d%d", &in[i][0], &in[i][1]);
			D.add(in[i][0]-1); D.add(in[i][1]);
		}
		D.init();
		for(int i=1; i<=D.siz; i++) unin[i] = i;
		int cnt = 0;
		for(int i=0,l,r; i<M; i++)
		{
			l=D.id(in[i][0]-1), r=D.id(in[i][1]);
			if(uf(l) != uf(r))
			{
				cnt ++;
				unin[uf(l)] = uf(r);
			}
		}
		printf("%d\n", Pow(26,N-cnt));
	}
	return 0;
}

int Pow(int x, int n)
{
	int res = 1;
	while(n)
	{
		if(n&1) res = (LL)x*res%MOD;
		x = (LL)x*x%MOD;
		n>>=1;
	}
	return res;
}

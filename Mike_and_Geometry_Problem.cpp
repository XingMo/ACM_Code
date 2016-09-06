/*
Codeforces - 689E
给定 n条 x轴上的线段，问从中任选 k条的交集的长度的和是多少

对于数轴上的每一点，计算它对答案的贡献
比如一条线段 [l,r]，那么我在 [l,r]的区间上都加 1
最后枚举数轴上的每一点，可以得出它被多少条线段覆盖过
然后用组合数算一算即可
当然坐标要先离散化一下，然后由于是静态的区间更新，所以直接差分即可
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

const int maxn=2e5+10, MOD=1e9+7;
struct Discrete
{
	int ais[2*maxn],siz;
	void init(){sort(ais, ais+siz); siz = unique(ais,ais+siz)-ais;}
	void add(int _n){ais[siz++]=_n;}
	int id(int _n){return lower_bound(ais,ais+siz,_n)-ais;}
};

int N,K,in[2][maxn];
int axis[2*maxn];
LL fact[2][maxn];
Discrete D;

LL Pow(LL,LL,LL);
LL C(LL,LL);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	fact[0][0] = fact[1][0] = 1;
	for(int i=1; i<maxn; i++) fact[0][i] = fact[0][i-1]*i%MOD, fact[1][i] = Pow(fact[0][i], MOD-2, MOD);
	
	while(~scanf("%d%d", &N, &K))
	{
		D.siz=0; CLR(axis);
		for(int i=0; i<N; i++)
		{
			scanf("%d%d", in[0]+i, in[1]+i);
			D.add(in[0][i]); D.add(in[1][i]+1);
		}
		D.init();
		for(int i=0; i<N; i++)
		{
			axis[D.id(in[0][i])] ++;
			axis[D.id(in[1][i]+1)] --;
		}
		LL res=0, sum=0;
		for(int i=0; i<D.siz-1; i++)
		{
			sum += axis[i];
			axis[i] = sum;
			res += ((LL)D.ais[i+1]-D.ais[i])*C(axis[i],K)%MOD;
			if(res>=MOD) res -= MOD;
		}
		cout << res << "\n";
	}
	return 0;
}

LL C(LL n, LL k)
{
	if(n<k || n<0 || k<0) return 0;
	return fact[0][n]*fact[1][k]%MOD*fact[1][n-k]%MOD;
}

LL Pow(LL x, LL n, LL p)
{
	LL res=1;
	while(n)
	{
		if(n&1) res=x*res%p;
		x=x*x%p;
		n>>=1;
	}
	return res;
}

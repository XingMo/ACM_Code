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

const int maxn=2e5+10, maxk=100+10, MOD = 1e9+7;
struct AMatrix
{
	static const int size=100+10;
	int row, col, n[size][size];
	void construct(int,int,int*,int*);
	int gauss();
	void pri()
	{
		for(int i=0; i<row; i++,puts("")) for(int j=0; j<col; j++) printf("%9d", n[i][j]);
	}
};

int N,K,A[maxk],B[maxk];
LL fact[2][maxn];
AMatrix am;

LL Pow(LL,LL,LL);
inline LL Comb(LL,LL);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	fact[0][0] = fact[1][0] = 1;
	for(int i=1; i<maxn; i++) fact[0][i] = fact[0][i-1]*i%MOD, fact[1][i] = Pow(fact[0][i], MOD-2, MOD);
	
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		scanf("%d%d", &N, &K);
		for(int i=0; i<K; i++) scanf("%d", &A[i]);
		for(int i=0; i<K; i++) scanf("%d", &B[i]);
		am.construct(N,K,A,B);
		int res = am.gauss();
		printf("%d\n", res);
	}
	return 0;
}

void AMatrix::construct(int N, int K, int A[], int B[])
{
	CLR(n);
	row=col=K;
	for(int i=0; i<K; i++)
	{
		for(int j=0; j<K; j++)
		{
			n[i][j] = Comb(B[j]-A[i]+N-1, N-1);
		}
	}
}

int AMatrix::gauss()
{
	int r,c;
	for(r=0,c=0; r<row && c<col; c++)
	{
		for(int i=r; i<row; i++) if(n[i][c])
		{
			if(i!=r) for(int j=c; j<col+1; j++) swap(n[r][j], n[i][j]);
			break;
		}
		if( !n[r][c] ) return 0;
		for(int i=r+1; i<row; i++) if(n[i][c])
		{
			LL rate = (LL)n[i][c]*Pow(n[r][c], MOD-2, MOD)%MOD;
			for(int j=c; j<col+1; j++) n[i][j] = ((n[i][j] - rate*n[r][j])%MOD + MOD)%MOD;
		}
		r++;
	}
	LL res=1;
	for(int i=0; i<col; i++) res = res*n[i][i]%MOD;
	return int((res+MOD)%MOD);
}

LL Pow(LL x, LL n, LL p)
{
	LL res=1;
	while(n)
	{
		if(n&1) res=res*x%p;
		x=x*x%p;
		n>>=1;
	}
	return res;
}

inline LL Comb(LL n, LL k)
{
	if(n<k || n<0 || k<0) return 0;
	else return fact[0][n]*fact[1][k]%MOD *fact[1][n-k]%MOD;
}

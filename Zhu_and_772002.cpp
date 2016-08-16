/*
HDU - 5833
有 N个数，每个数的所有质因子都不超过 2000
问选择其中若干个数使他们的乘积为平方数的方案数
其中 N<=300

CCPC16网赛的题，据说是原题，学长直接把以前的代码贴上去就过了
显然题目可以转化为选择若干个数，使他们的每个质因子的次幂和为偶数
首先设 x_i为是否选择第 i个数，x_i的取值为 0或 1
分解每个数，然后根据每个质因子建立一个模 2方程，然后进行消元
最后就能得出其中自由变元的个数 k，最后答案为 2^k-1 （去掉全不选的一种情况）
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

const int maxn=300+10, maxl=2000+10, MOD=1000000007;
struct AMatrix
{
	const static int size = 310;
	int row, col, first[size];
	int n[size][size+1], x[size];
	void construct(int,LL*);
	int gauss();
	void pri()
	{
		printf("%d %d\n", row, col);
		for(int i=0; i<10; i++,puts("")) for(int j=0; j<10; j++) printf("%d ", n[i][j]);
	}
};

bool sieve[maxl];
int prime[maxl],pcnt,pow2[maxn];
int N;
LL A[maxn];
AMatrix am;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	pow2[0]=1;
	for(int i=1; i<maxn; i++) pow2[i] = pow2[i-1]*2%MOD;
	for(int i=2; i<maxl; i++) if(!sieve[i])
	{
		prime[pcnt++]=i;
		for(int j=i*i; j<maxl; j+=i) sieve[j]=1;
	}
	
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		scanf("%d", &N);
		for(int i=0; i<N; i++) scanf("%lld", &A[i]);
		am.construct(N,A);
		int res = am.gauss();
		printf("Case #%d:\n", ck);
		printf("%d\n", pow2[res]-1);
	}
	return 0;
}

void AMatrix::construct(int N, LL A[])
{
	CLR(n);
	row=0; col=N;
	for(int i=0; i<N; i++)
	{
		LL tem = A[i];
		for(int j=0, cnt; j<pcnt; j++) if(tem%prime[j]==0)
		{
			row = max(row, j+1);
			cnt=0;
			while(tem%prime[j]==0) tem /= prime[j], cnt++;
			n[j][i] = cnt&1;
		}
	}
}

int AMatrix::gauss()
{
	CLR(x); CLR(first);
	int r,c;
	for(r=0,c=0; r<row && c<col; c++)
	{
		int tmax = r;
		for(int i=r+1; i<row; i++) if( n[i][c] > n[tmax][c] ) tmax = i;
		if(tmax != r) for(int i=c; i<col+1; i++) swap( n[r][i], n[tmax][i]);
		if(n[r][c]==0) continue;
		first[r] = c;
		for(int i=r+1; i<row; i++) if( n[i][c] )
		{
			for(int j=c; j<col+1; j++) n[i][j] ^= n[r][j];
		}
		r++;
	}
	return col-r;
}

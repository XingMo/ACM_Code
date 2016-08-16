/*
HDU - 5730
给定一段长度为 N的序列，长度为 i的连续一段有 a_i种染色方案
问一共有多少中染色方案，其中 N<=1e5

一个很显然的dp方程，设 dp[i]为前 i个的染色方案
dp[i] = \sum_{j=1}^{i} a[j]*dp[i-j]
这很显然就是一个卷积的形式……所以用上 FFT就可以了
但是问题在于，dp[i]依赖于 dp[i-j]，所以不能直接一次 FFT就算出来，要 N次
这样一来，时间复杂度就是 O(N^2logN)的，还不如直接暴力

所以我们还要用上 CDQ分治的思想
对于一段区间，先算出前半段的 dp值，再与 a值卷积，然后产生对后半段的贡献
这样分治地去算，时间复杂度就是 O(Nlog^2(N))
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

const int maxn=1e5+10, MOD=313, maxl=1<<19;
const DBL PI = acos(-1.0);
typedef complex<DBL> clx;

int N, W[maxn], dp[maxn];
clx A[maxl], B[maxl];

void conv(int,clx*,clx*);
void FFT(int,clx*,int);
void cdq(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N) && N)
	{
		for(int i=1; i<=N; i++) scanf("%d", &W[i]), W[i]%=MOD;
		CLR(dp);
		dp[0]=1;
		cdq(0,N);
		printf("%d\n", dp[N]);
	}
	return 0;
}

void cdq(int l, int r)
{
	if(l==r) return;
	int mid=(l+r)>>1, len=1;
	while(len <= 2*(r-l+1)) len<<=1;

	cdq(l,mid);
	for(int i=0; i<len; i++)
	{
		A[i] = clx(l+i+1<=r?W[i+1]:0, 0);
		B[i] = clx(l+i<=mid?dp[l+i]:0, 0);
	}
	conv(len,A,B);
	for(int i=mid+1; i<=r; i++)
	{
		dp[i] += fmod(A[i-l-1].real(), MOD) + 0.5;
		dp[i] = (dp[i]%MOD + MOD)%MOD;
	}
	cdq(mid+1, r);
}

void conv(int n, clx A[], clx B[])
{
	FFT(n,A,1); FFT(n,B,1);
	for(int i=0; i<n; i++) A[i]=A[i]*B[i];
	FFT(n,A,-1);
}

void FFT(int n, clx A[], int dir)
{
	for(int i=0,j=0; i<n; i++)
	{
		if(i<j) swap(A[i], A[j]);
		for(int k=n>>1; (j^=k)<k; k>>=1);
	}
	clx wn,w,z;
	for(int len=2,m,i,j; len<=n; len<<=1)
	{
		m=len>>1;
		wn = clx(cos(dir*2.0*PI/len), sin(dir*2.0*PI/len));
		for(i=0; i<n; i+=len)
		{
			w = clx(1.0, 0.0);
			for(j=0; j<m; j++)
			{
				z = A[i+m+j]*w;
				A[i+m+j] = A[i+j] - z;
				A[i+j] += z;
				w *= wn;
			}
		}
	}
	if(dir==-1) for(int i=0; i<n; i++) A[i] /= n;
}

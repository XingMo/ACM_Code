/*
HDU - 1402
两个大整数的高精度乘法

由于 N比较大，所以暴力模拟是不行的
要用到 FFT，FFT入门题了……
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

const int maxn=1<<19;
const DBL PI = acos(-1.0);
struct clx
{
	DBL r,i;
	clx operator + (const clx &v) const {return {r+v.r, i+v.i};}
	clx operator - (const clx &v) const {return {r-v.r, i-v.i};}
	clx operator * (const clx &v) const {return {r*v.r-i*v.i, r*v.i+i*v.r};}
};

char str[2][maxn];
clx A[maxn], B[maxn], C[maxn], W[maxn], cjW[maxn];
int res[maxn];

void init_W(int);
void FFT(int,clx*,clx*);
void conv(int,clx*,clx*,clx*);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	while(~scanf("%s%s", str[0], str[1]))
	{
		int lena=strlen(str[0]), lenb=strlen(str[1]), len=1;
		while(len < lena*2 || len < lenb*2) len<<=1;
		
		CLR(A); CLR(B); CLR(C);
		for(int i=0; i<lena; i++) A[i].r = str[0][lena-i-1] - '0';
		for(int i=0; i<lenb; i++) B[i].r = str[1][lenb-i-1] - '0';
		
		init_W(len);
		conv(len,A,B,C);
		
		CLR(res);
		int tot=0;
		for(int i=0; i<len; i++)
		{
			res[i] += C[i].r + 0.5;
			res[i+1] += res[i]/10;
			res[i] %=10;
			if(res[i]) tot=i;
		}
		while(tot>=0) putchar(res[tot--]+'0');
		puts("");
	}
	return 0;
}

void conv(int n, clx A[], clx B[], clx C[])
{
	FFT(n,A,W); FFT(n,B,W);
	for(int i=0; i<n; i++) C[i]=A[i]*B[i];
	FFT(n,C,cjW);
	for(int i=0; i<n; i++) C[i].r /= n;
}

void init_W(int n)
{
	for(int i=0; i<n; i++)
	{
		W[i] = {cos(2.0*PI*i/n), sin(2.0*PI*i/n)};
		cjW[i] = {cos(2.0*PI*i/n), -sin(2.0*PI*i/n)};
	}
}

void FFT(int n, clx A[], clx W[])
{
	for(int i=0,j=0; i<n; i++)
	{
		if(i<j) swap(A[i], A[j]);
		for(int k=n>>1; (j^=k)<k; k>>=1);
	}
	for(int len=2; len<=n; len<<=1)
	{
		int m = len>>1;
		for(int i=0; i<n; i+=len)
		{
			for(int j=0; j<m; j++)
			{
				clx z = A[i+m+j]*W[n/len*j];
				A[i+m+j] = A[i+j] - z;
				A[i+j] = A[i+j] + z;
			}
		}
	}
}

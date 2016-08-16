/*
HDU - 4609
给定 N根木棍，随机选择其中三根木棍，
问三根木棍能组成三角形的概率是多少

首先要算出能组成三角形的方案数
直接的想法是 O(N^3)枚举三条边
但实际上，可以利用卷积预处理出枚举两条边的所有情况
只要记录下长度为 i的木棍的数量 cnt[i]
然后再将两个序列卷积即可
之后对 A[i]排序，枚举第三条边，
将其作为最大边，然后就可以计算了

具体一点，卷积算出结果后，要先去重
首先要去掉同一条边选两次的，
再去掉同一对边正着反着各取一次的，所以除以 2
预处理出来后，对于每个 A[i]可以得到两条边加起来大于它的方案数
减去这两条一条比它小，一条比它大的，
以及一条选它的，以及两条都比它大的，最后累计到答案里

小心爆 int，尤其是算总方案数那里
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

const int maxn=1e5+10, maxl=1<<19;
const DBL PI=acos(-1.0);
typedef complex<DBL> clx;

int N, in[maxn], cnt[maxl];
LL sum[maxl];
clx A[maxl],B[maxl];

void FFT(int,clx*,int);

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
		CLR(cnt); CLR(sum);
		scanf("%d", &N);
		
		int tmax=0, len=1;
		for(int i=1; i<=N; i++) scanf("%d", &in[i]), cnt[in[i]]++, tmax=max(tmax, in[i]);
		for(int i=0; i<maxl; i++) A[i] = B[i] = {(DBL)cnt[i], 0.0};
		
		while(len <= tmax*2) len<<=1;
		
		FFT(len,A,1); FFT(len,B,1);
		for(int i=0; i<len; i++) A[i]*=B[i];
		FFT(len,A,-1);
		
		for(int i=1; i<len; i++) sum[i] = A[i].real()+0.5;
		for(int i=1; i<=N; i++) sum[in[i]+in[i]] --;
		for(int i=1; i<len; i++) sum[i] >>= 1;
		for(int i=1; i<len; i++) sum[i] += sum[i-1];
		
		LL ans=0, tot = (LL)N*(N-1)*(N-2)/6;
		sort(in+1, in+1+N);
		for(int i=1; i<=N; i++)
		{
			LL tem = sum[len-1]-sum[in[i]] - (LL)(i-1)*(N-i) - (LL)(N-1) - (LL)(N-i)*(N-i-1)/2;
//			printf("%d: %lld %lld\n", in[i], tem, sum[len-1]-sum[in[i]]);
			ans += tem;
		}
		printf("%.7f\n", (DBL)ans/tot);
	}
	return 0;
}

void FFT(int n, clx A[], int dir)
{
	for(int i=0,j=0; i<n; i++)
	{
		if(i<j) swap(A[i], A[j]);
		for(int k=n>>1; (j^=k)<k; k>>=1);
	}
	clx wn,w,z;
	for(int len=2, m, i, j; len<=n; len<<=1)
	{
		m=len>>1;
		wn = {cos(dir*2.0*PI/len), sin(dir*2.0*PI/len)};
		for(i=0; i<n; i+=len)
		{
			w = {1.0, 0.0};
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

/*
Codeforces - 689D
给定两个序列 A，B，求问有多少个区间 [l,r]满足
max(A[l,r]) = min(B[l,r])

考虑枚举区间左端点，移动右端点的过程中
max(A[l,r])肯定越来越大，min(B[l,r])越来越小
用 d = max(A[l,r])-min(B[l,r])来表示这个过程
发现在移动 r的过程中，d单调递增
所以枚举左端点，二分右端点，找出 d=0的一段区间
至于 max(A[l,r])和 min(B[l,r])用稀疏表预处理一下即可
二分的时候应该要注意判一下无解的情况
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

const int maxn=2e5+10;
inline int maxx(int a,int b){return a>b?a:b;}
inline int minn(int a,int b){return a<b?a:b;}
struct SparseTable
{
	int arr[20][maxn], (*cmp)(int,int);
	void init(int*,int,int (*)(int,int));
	int query(int,int);
} smax, smin;
int N, A[maxn], B[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		for(int i=1; i<=N; i++) scanf("%d", A+i);
		for(int i=1; i<=N; i++) scanf("%d", B+i);
		smax.init(A, N, maxx);
		smin.init(B, N, minn);
		LL res=0;
		for(int i=1,l,r,mid,lb,ub; i<=N; i++)
		{
			l=i, r=N;
			while(l<r)
			{
				mid = (l+r)>>1;
				if(smax.query(i,mid)-smin.query(i,mid) >= 0) r = mid;
				else l=mid+1;
			}
			lb=l;
			l=i, r=N;
			while(l<r)
			{
				mid = (l+r+1)>>1;
				if(smax.query(i,mid)-smin.query(i,mid) <=0 ) l = mid;
				else r=mid-1;
			}
			ub=l;
			res += ub-lb+1;
			if(lb==ub && smax.query(i,ub)-smin.query(i,ub)) res--;
		}
		cout << res << "\n";
	}
	return 0;
}

void SparseTable::init(int A[], int len, int (*_cmp)(int,int))
{
	cmp = _cmp;
	int tlog = log2(len);
	for(int i=1; i<=len; i++) arr[0][i] = A[i];
	for(int j=1; j<=tlog; j++)
	{
		int tlen=1<<j-1, lim=len-(1<<j)+1;
		for(int i=1; i<=lim; i++)
		{
			arr[j][i] = cmp(arr[j-1][i], arr[j-1][i+tlen]);
		}
	}
}

int SparseTable::query(int l, int r)
{
	if(l>r) swap(l,r);
	int flr = log2(r-l+1), len=1<<flr;
	return cmp(arr[flr][l], arr[flr][r-len+1]);
}

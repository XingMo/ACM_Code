/*
HDU - 5726
给定一个序列，每次询问一个区间
输出这个区间上所有数的GCD，以及GCD与其相同的区间个数

赛上太智障了读错了题，以为是求得是GCD相同的子区间的个数

一个连续区间的GCD，用倍增法预处理一下，就能做到 O(1)查询
对于相同区间计数，就把询问先离线一下
枚举区间左端点，区间GCD是随右端点递减的，并且是阶梯式的
并且由于GCD递减的很快，这样一个阶梯只有几层，可以当作log的
所以对于每一个GCD，二分右端点，就能求出答案
时间复杂度 O(N*log(N)*log(N))
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
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) ((a)*(a))
int GCD(int a,int b){return b?GCD(b,a%b):a;}

const int maxn = 1e5+10;
struct SparseTable
{
	int st[20][maxn], siz;
	void init(int*, int);
	int query(int,int);
};

int N, Q, A[maxn];
SparseTable st;
map<int,LL> ans;
int query[maxn][3];

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
		scanf("%d", &N);
		for(int i=1; i<=N; i++) scanf("%d", &A[i]);
		st.init(A, N);
		ans.clear();
		
		scanf("%d", &Q);
		for(int i=0; i<Q; i++)
		{
			scanf("%d%d", &query[i][0], &query[i][1]);
			query[i][2]=st.query( query[i][0], query[i][1]);
			ans.insert(make_pair( query[i][2], 0));
		}
		for(int i=1; i<=N; i++)
		{
			int np=i;
			while(np<=N)
			{
				int d=st.query(i, np);
				int l=np, r=N;
				while(l<r)
				{
					int mid=(l+r+1)>>1;
					if(st.query(i, mid)<d) r=mid-1;
					else l=mid;
				}
				if(ans.find(d) != ans.end()) ans[d] += l-np+1;
				np=r+1;
			}
		}
		printf("Case #%d:\n", ck);
		for(int i=0; i<Q; i++)
		{
			printf("%d %lld\n", query[i][2], ans[query[i][2]] );
		}
	}
	return 0;
}

void SparseTable::init(int arry[], int N)
{
	int siz=N, tlog=log2(N);
	for(int i=1; i<=N; i++) st[0][i] = arry[i];
	for(int i=1; i<=tlog; i++)
	{
		int len=1<<(i-1), nlim=N-(1<<i);
		for(int j=1; j<=nlim+1; j++)
			st[i][j] = GCD(st[i-1][j], st[i-1][j+len]);
	}
}

int SparseTable::query(int l, int r)
{
	int flr=log2(r-l+1), len=1<<flr;
	return GCD( st[flr][l], st[flr][r-len+1]);
}

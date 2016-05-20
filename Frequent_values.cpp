/*
POJ - 3368
给定一个非减的数列，求问给定的一个区间内，出现最多的数出现了多少次

由于数列非减，所以相同的数必然是在一起的
所以可以预处理出一块相同数区间的左端点，右端点，以及块的大小
查询一个区间[l,r]，如果区间被一个数块包含，则输出 r-l+1
如果中间有若干个块，则在左端点所在块的包含数量，
右端点所在块的包含数量，以及中间块的大小的最大值中取最大
中间块求最大用 sparse table预处理一下即可

时间复杂度 O(n*log(n))
*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
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
#define Sqr(a) (a*a)

const int maxn=1e5+10,INF=0x3f3f3f3f;
struct SparseTable
{
	int **spas,tlog;
	SparseTable(int*,int);
	~SparseTable();
	int query(int,int);
};
int N,Q;
int inpt[maxn];
int L[maxn], R[maxn];
int bsiz[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &Q)&&N)
	{
		inpt[0]=-INF;
		int sp=0;
		for(int i=1; i<=N; i++) 
		{
			scanf("%d", &inpt[i]);
			if(inpt[i-1] != inpt[i])
			{
				for(int j=sp; j<i; j++) 
				{
					R[j]=i-1;
					bsiz[j]=i-sp;
				}
				sp=i;
			}
			L[i]=sp;
		}
		for(int i=sp; i<=N; i++) 
		{
			R[i]=N;
			bsiz[i]=N-sp+1;
		}
		
		SparseTable st(bsiz+1, N);
		
		for(int i=1; i<=Q; i++)
		{
			int l,r,ans;
			scanf("%d%d", &l, &r);
			if(L[l]==L[r]) ans=r-l+1;
			else
			{
				ans=max(R[l]-l+1, r-L[r]+1);
				l=R[l]+1, r=L[r]-1;
				if(l<=r) ans=max(ans, st.query(l,r));
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}

SparseTable::SparseTable(int arry[], int len)
{
	tlog=log2(len);
	spas=new int*[tlog+2];
	for(int i=0; i<=tlog; i++) spas[i]=new int[len-(1<<i)+1];
	for(int i=0; i<len; i++) spas[0][i]=arry[i];
	
	for(int j=1; j<=tlog; j++)
	{
		int tlen=1<<j-1,nlim=len-(1<<j)+1;
		for(int i=0; i<nlim; i++)
		{
			spas[j][i]=max(spas[j-1][i], spas[j-1][i+tlen]);
		}
	}
}

SparseTable::~SparseTable()
{
	for(int i=0; i<=tlog; i++) delete[] spas[i];
	delete[] spas;
}

int SparseTable::query(int l, int r)
{
	l--; r--;
	int flr=log2(r-l+1);
	int nlen=1<<flr;
	return max(spas[flr][l], spas[flr][r-nlen+1]);
}

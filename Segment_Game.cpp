/*
HDU-5372
给定若干条长度为 1、2、3...递增的线段
每次向数轴上添加一条线段，或者删除一条线段
问每次添加的线段能完全覆盖多少条已有线段

这题卡CDQ分治，而CDQ分治没有用到长度递增这个条件
之前的线段与正在添加的线段的位置情况只有三种
之前的线段 [l0, r0], 当前线段 [l,r]
1. l0<l，则必有 r0<r
2. r0>r，则必有 l0>l
3. l<l0，r0<r
对于第三种情况，正是我们要求的，但不好直接统计
所以统计前两种情况
利用树状数组统计之前线段左端位置小于当前左端点
以及之前线段右端位置大于当前右端点
再用总的相减就能得到答案
用CDQ的话时间复杂度是 O(N*logN*logN)， 会 TLE
树状数组的话复杂度就是 O(N*logN)
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

const int maxn=2e5+10;
struct Discrete
{
	int ais[2*maxn], siz;
	void init()
	{
		sort(ais,ais+siz);
		siz=unique(ais, ais+siz)-ais;
	}
	void add(int _n){ais[siz++]=_n;}
	int id(int _n)
	{
		int p=lower_bound(ais, ais+siz, _n)-ais;
//		if(ais[p]!=_n || p>=siz) return -1;
		return p+1;
	}
};
struct BIT
{
	int bit[2*maxn], siz;
	void init(int _n){siz=_n; CLR(bit);}
	void add(int _p, int _v){ for(int i=_p; i<=siz; i+=i&-i) bit[i]+=_v;}
	int sum(int _p){ int res=0; for(int i=_p; i>0; i-=i&-i) res+=bit[i]; return res;}
};
int N;
int inpt[maxn][2];
int pos[maxn][2];
Discrete D;
BIT L,R;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int ck=0;
	while(~scanf("%d", &N))
	{
		D.siz=0;
		int nlen=0, tot=0;
		for(int i=0; i<N; i++)
		{
			scanf("%d%d", &inpt[i][0], &inpt[i][1]);
			if(!inpt[i][0])
			{
				nlen++;
				D.add(inpt[i][1]);
				D.add(inpt[i][1]+nlen);
			}
		}
		D.init();
		L.init(D.siz);
		R.init(D.siz);
		nlen=0;
		printf("Case #%d:\n", ++ck);
		for(int i=0; i<N; i++)
		{
			if(inpt[i][0]==0)
			{
				nlen++;
				pos[nlen][0] = D.id(inpt[i][1]);
				pos[nlen][1] = D.siz - D.id(inpt[i][1]+nlen) + 1;
				printf("%d\n", tot-L.sum(pos[nlen][0]-1)-R.sum(pos[nlen][1]-1) );
				L.add(pos[nlen][0], 1);
				R.add(pos[nlen][1], 1);
				tot++;
			}
			else
			{
				L.add(pos[inpt[i][1]][0], -1);
				R.add(pos[inpt[i][1]][1], -1);
				tot--;
			}
		}
	}
	return 0;
}


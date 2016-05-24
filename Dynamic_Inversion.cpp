/*
Uva - 11990
动态逆序对，求删除一个点之前序列中逆序对的个数

首先倒过来看这个问题，把点先全部删掉
然后从最后一个点开始倒着往数列中加点
求加完这个点逆序对的变化

分块做法，把下标看成 x，值看成 y
这样就变成了平面上的点，
将平面分成 bsiz*bsiz，bsiz=sqrt(N)
加入一个点的时候，在它左上方区域的和右下方区域中的点的数目
就是加入这个点所能产生的逆序对的数目
所以只要维护一下每行每个块的前缀和就好，方便求数目
加入一个点 (x,y)的时候，先暴力更新这行的前缀和 O(sqrt(N))
然后利用前缀暴力扫每一行，求得左上和右下区域内点的个数 O(sqrt(N))
不在块内的再暴力扫一遍统计 O(sqrt(N))
时间复杂度 O(M*sqrt(N))

CDQ分治做法，把删除时间看作 t，下标看作 x，值看作 y
然后对 x排序，对 t偏序，用树状数组维护 y
具体来说就是对于每个点 (t_0, x_0, y_0)
先统计 t < t_0，x < x_0，y > y_0 的 (t,x,y)的个数
再统计 t < t_0，x > x_0，y < y_0 的 (t,x,y)的个数
做法参考了这个 http://blog.csdn.net/u011542204/article/details/50571409
*/

/*
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

const int maxn=2e5+10, maxs=500;
int N,M,bsiz,blen;
int X[maxn], Y[maxn];
bool ban[maxn];
bool have[maxn];

LL psum[maxs][maxs];

int que[maxn];
LL ans[maxn];

LL insert(int,int);
LL sum(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		CLR(X); CLR(Y);
		CLR(psum); CLR(ban); CLR(have);
		bsiz=sqrt(N)+10;
		blen=N/bsiz+1;
		LL tans=0;
		for(int i=0; i<N; i++) 
		{
			scanf("%d", &Y[i]);
			Y[i]--;
			X[ Y[i] ] = i;
		}
		for(int i=0; i<M; i++)
		{
			scanf("%d", &que[i]);
			que[i]--;
			ban[ X[ que[i] ] ]=1;
		}
		
		for(int i=0; i<N; i++)
		{
			if(!ban[i]) tans+=insert(i, Y[i]);
//			printf("%lld\n", tans);
		}
		
		for(int i=M-1; i>=0; i--)
		{
			tans+=insert(X[ que[i] ], que[i]);
			ans[i]=tans;
		}
		for(int i=0; i<M; i++) printf("%lld\n", ans[i]);
	}
	return 0;
}

LL insert(int x, int y)
{
	have[x]=1;
	int tx=x/bsiz;
	int ty=y/bsiz;
	for(int i=tx; i<blen; i++) psum[i][ty]++;
	
	LL res=-2*sum(x,y);
	res+=sum(N-1,y);
	res+=sum(x,N-1);
	return res;
}

LL sum(int x,int y)
{
	int tx=x/bsiz;
	int ty=y/bsiz;
	LL res=0;
	if(tx) for(int i=0; i<ty; i++) res+=psum[tx-1][i];
	for(int i=tx*bsiz; i<=x; i++)
	{
		if(have[i] && Y[i]<ty*bsiz) res++;
	}
	for(int i=ty*bsiz; i<=y; i++)
	{
		if(have[X[i]] && X[i]<=x) res++;
	}
	return res;
}
*/

/*
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

const int maxn=2e5+10;
struct BIT
{
	int bit[maxn], siz;
	int lowbit(int x){return x&-x;}
	void add(int x,int v) { while(x<=siz) bit[x]+=v,x+=lowbit(x);}
	int sum(int x) { int res=0; while(x>0) res+=bit[x],x-=lowbit(x); return res;}
	void init(){CLR(bit);}
} tree;
int N,M;
int inpt[maxn], posi[maxn];
bool ban[maxn];
struct piii{int t,x,y;} data[maxn], temp[maxn];

LL ans[maxn];
void CDQ(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		CLR(ban); CLR(ans);
		tree.siz=N;
		tree.init();
		for(int i=1; i<=N; i++)
		{
			scanf("%d", &inpt[i]);
			posi[ inpt[i] ] = i;
		}
		int nt=N;
		for(int i=1; i<=M; i++)
		{
			int x;
			scanf("%d", &x);
			ban[ posi[x] ] = 1;
			data[nt].t = nt;
			data[nt].x = posi[ x ];
			data[nt].y = x;
			nt--;
		}
		for(int i=1; i<=N; i++)
		{
			if(!ban[i])
			{
				data[nt].t = nt;
				data[nt].x = i;
				data[nt].y = inpt[i];
				nt--;
			}
		}
		
		CDQ(1,N);
		for(int i=1; i<=N; i++) ans[i]+=ans[i-1];
		for(int i=N; i>N-M; i--) printf("%lld\n", ans[i]);
	}
	return 0;
}

void CDQ(int L, int R)
{
	if(L>=R) return;
	int mid=(L+R)>>1;
	CDQ(L,mid); CDQ(mid+1, R);
	
	// 统计 t < t_0，x < x_0，y > y_0
	int tl=L;
	for(int i=mid+1; i<=R; i++)
	{
		while(tl<=mid && data[tl].x < data[i].x) tree.add(data[tl++].y,1);
		ans[data[i].t] += tree.sum(N)-tree.sum(data[i].y);
	}
//	tree.init(); 不要用memset，这样是 N^2的
	for(int i=L; i<tl; i++) tree.add(data[i].y,-1);
	
	// 统计 t < t_0，x > x_0，y < y_0
	tl=mid;
	for(int i=R; i>mid; i--)
	{
		while(tl>=L && data[tl].x > data[i].x) tree.add(data[tl--].y,1);
		ans[data[i].t] += tree.sum(data[i].y-1);
	}
//	tree.init();
	for(int i=mid; i>tl; i--) tree.add(data[i].y,-1);
	
	// 归并排序
	tl=L;
	int np=L;
	for(int i=mid+1; i<=R; i++)
	{
		while(tl<=mid && data[tl].x < data[i].x) temp[np++] = data[tl++];
		temp[np++] = data[i];
	}
	while(tl<=mid) temp[np++] = data[tl++];
	
	for(int i=L; i<=R; i++) data[i] = temp[i];
}
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

int N,M;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	
	return 0;
}


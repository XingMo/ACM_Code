/*
HDU - 5412
动态区间第 K小

很经典的题，可以用线段树套平衡树在线解决
但是这题貌似卡树套树，况且我也不会手写平衡树

可以使用“整体二分”的分治思想解决

将每个数据处理成 (x, y, v)的三元组
其中 x为这个数的下标，y为大小，v为1时表示添加，-1表示删除
开始时读入 N个数据，进行 N次添加操作
修改操作视作删除这个数，然后在原位置再添加一个数这样两个操作

对于每个询问，处理成 (l, r, k)的三元组
l表示询问左端点，r为右端点，k为k小

然后把询问和数据按照出现的时间顺序放在一起，
这样这些三元组就对时间天然有序

然后进行整体二分，二分答案为 mid，
在每层递归中，按时间顺序处理三元组

如果当前处理一个数据，并且这个数大小 <=mid，
就把它的影响用数据结构来维护一下 （树状数组）
如果 <=mid，就放到左边，反之放到右边

如果当前处理一个询问，那么从数据结构中就能知道，
[l,r]区间中 <=mid的数有多少个
如果个数 >=mid，说明当前二分的这个mid太大了
那么就把这个三元组放到左边，和哪些<=mid的数据在一起
如果个数 < mid，说明当前二分的这个mid太小了
那么就将其放到右边，和那些 >mid的数据放在一起
并且 k要减去当前个数（扣去左区间的影响）

这样将询问和数据放在一起，对数据进行了一个归并排序
最后数据将会是有序的，但与此同时，询问也跟着数据进行了排序
询问与答案数据的距离会随着递归层数的增加越来越小，直到得出答案，递归结束
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

const int maxn=1e5+10;
struct Discrete
{
	int d[2*maxn], siz;
	void init()
	{
		sort(d, d+siz);
		siz = unique(d, d+siz) - d;
	}
	void add(int _n){ d[siz++]=_n;}
	int id(int _n){ return lower_bound(d, d+siz, _n)-d+1;}
};
struct data
{
	int opt, l, r, v;
	data(){};
	data(int a,int b,int c,int d){opt=a; l=b; r=c; v=d;}
	void pri()
	{
		printf("o:%d l:%d r:%d v:%d\n", opt, l, r, v);
	}
};
struct BIT
{
	int bit[maxn], siz;
	void init(int _n){ siz=_n; CLR(bit);}
	void add(int p, int x){ for(int i=p; i<=siz; i+=i&-i) bit[i]+=x;}
	int sum(int p){ int res=0; for(int i=p; i>0; i-=i&-i) res+=bit[i]; return res;}
};
int N,Q;
int inpt[maxn];
data list[3*maxn], teml[3*maxn], temr[3*maxn];
Discrete D;
BIT bit;
int ans[maxn];

void solve(int,int,int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		D.siz=0;
		int ap=0, list_siz=0;
		for(int i=1; i<=N; i++)
		{
			scanf("%d", &inpt[i]);
			D.add(inpt[i]);
			list[list_siz++] = data(0,i,inpt[i],1);
		}
		scanf("%d", &Q);
		for(int i=1; i<=Q; i++)
		{
			int opt, l, r, k;
			scanf("%d", &opt);
			if(opt==1)
			{
				scanf("%d%d", &l, &k);
				D.add(k);
				list[list_siz++] = data(0,l,inpt[l],-1);
				list[list_siz++] = data(0,l,k,1);
				inpt[l]=k;
			}
			else
			{
				scanf("%d%d%d", &l, &r, &k);
				list[list_siz++] = data(++ap,l,r,k);
			}
		}
		
		D.init();
		bit.init(N);
		for(int i=0; i<list_siz; i++) if(!list[i].opt) list[i].r = D.id(list[i].r);
		solve(0,list_siz,1,D.siz);
		
		for(int i=1; i<=ap; i++) printf("%d\n", ans[i]);
	}
	return 0;
}

void solve(int ql, int qr, int nl, int nr)
{
//	printf("ql:%d qr:%d nl:%d nr:%d mid:%d\n", ql, qr, nl, nr, (nl+nr)>>1);
//	for(int i=ql; i<qr; i++) list[i].pri();
	if(nl==nr)
	{
		for(int i=ql; i<qr; i++) if(list[i].opt)
		{
			ans[list[i].opt] = D.d[nl-1];
		}
//		puts("--------");
		return;
	}
	
	int mid=(nl+nr)>>1;
	int sizl=0, sizr=0;
	for(int i=ql; i<qr; i++)
	{
		if(!list[i].opt)
		{
			if(list[i].r <= mid)
			{
				bit.add(list[i].l, list[i].v);
				teml[sizl++] = list[i];
			}
			else temr[sizr++] = list[i];
		}
		else
		{
			int have = bit.sum(list[i].r) - bit.sum(list[i].l-1);
//			printf("i:%d have:%d o:%d\n", i, have, list[i].opt);
			if(have >= list[i].v) teml[sizl++] = list[i];
			else
			{
				list[i].v -= have;
				temr[sizr++] = list[i];
			}
		}
	}
	for(int i=0; i<sizl; i++) if(!teml[i].opt)
		bit.add(teml[i].l, -teml[i].v);
	for(int i=0; i<sizl; i++) list[ql+i]=teml[i];
	for(int i=0; i<sizr; i++) list[ql+sizl+i]=temr[i];
//	puts("--------");
	solve(ql, ql+sizl, nl, mid);
	solve(ql+sizl, qr, mid+1, nr);
}


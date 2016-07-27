/*
HDU - 5741
给定一个二进制的字符串，有 M次询问
问是否存在含有 a个 0 ，b个 1的区间

如果把所有答案预处理出来，
发现答案 (a,b)在平面上构成了一个很有规律的封闭图形
而选定区间包含的块全是完整的时候，答案正好落在边界点上
所以可以把所有边界点处理出来，然后二分查找答案

这个二分不是很好写，要根据图形的规律想好了再写
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
#include <ctime>
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define SQR(a) ((a)*(a))
#define PCUT puts("----------")

const int maxn=1e3+10, INF=0x3f3f3f3f;
int N,M;
int inpt[maxn];
int psum[maxn][2];
int upc,dnc;
Pii ans[maxn*maxn], up[maxn*maxn], down[maxn*maxn];

void init();

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
		scanf("%d%d", &N, &M);
		for(int i=0; i<N; i++)
		{
			scanf("%d", &inpt[i]);
			psum[i][0] = psum[i-1][0];
			psum[i][1] = psum[i-1][1];
			psum[i][i&1] += inpt[i];
		}
		init();
		for(int i=0; i<M; i++)
		{
			int a,b;
			scanf("%d%d", &a, &b);
			if( a > psum[N-1][0]) {putchar('0'); continue;}
			int l=0, r=upc-1, flr, cel;
			while(l<r)
			{
				int mid=(l+r+1)>>1;
				if(up[mid].first <= a) l=mid;
				else r=mid-1;
			}
			flr = up[l].second;
			l=0, r=dnc-1;
			while(l<r)
			{
				int mid=(l+r)>>1;
				if(down[mid].first >= a) r=mid;
				else l=mid+1;
			}
			cel = down[l].second;
			if(cel<=b && b<=flr) putchar('1');
			else putchar('0');
		}
		puts("");
	}
	return 0;
}

void init()
{
	int tot=0;
	ans[tot++]=Pii(0,0);
	for(int i=0; i<N; i++)
	{
		for(int j=i; j<N; j++)
		{
			int a = psum[j][0]-psum[i-1][0];
			int b = psum[j][1]-psum[i-1][1];
			ans[tot++]=Pii(a,b);
		}
	}
	sort(ans, ans+tot);
	tot = unique(ans, ans+tot)-ans;
	
	upc=0, dnc=0;
	int y=-1, x=ans[0].first, tem=-1;
	for(int i=0; i<tot; i++)
	{
		if(ans[i].first != x)
		{
			if(tem > y)
			{
				y=tem;
				up[upc++] = Pii(x, y);
			}
			x = ans[i].first;
		}
		tem = max(tem, ans[i].second);
	}
	up[upc++] = Pii(x, tem);
		
	y=INF, x=ans[tot-1].first, tem=INF;
	for(int i=tot-1; i>=0; i--)
	{
		if(ans[i].first != x)
		{
			if(tem < y)
			{
				y=tem;
				down[dnc++] = Pii(x,y);
			}
			x = ans[i].first;
		}
		tem = min(tem, ans[i].second);
	}
	down[dnc++] = Pii(x, tem);
	reverse(down, down+dnc);
}


/*
CQU - 21465
带四个操作的并查集
1. 合并两点所在集合
2. 解散一个集合
3. 查询某点所在集合元素个数
4. 查询两点是否在同一个集合

带解散操作的点权并查集

维护权值的思路是，将权值维护在根节点上，然后在合并的时候合并权值

解散的基本思路是，将解散集合的根节点连到0上，Cnt[0]为1
在查询是否在一个集合的时候，特判一下都连在0上的情况
在合并两点的时候，如果此一点连在0上，则将其映射到新开的一个节点上，++n，并初始化新节点
因此要开一个id数组表示此点现在的映射点，并且unin数组和Cnt数组要开得大于点数加最大操作数
其余操作和普通并查集基本一致
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

const int maxn=1e5+10, maxm=1e6+10;
struct Union
{
	int n;
	int unin[maxn+maxm];
	int Cnt[maxn+maxm], id[maxn];
	void init(int tn)
	{
		n=tn;
		Cnt[0]=1;
		for(int i=1; i<=n; i++) 
		{
			id[i]=i;
			unin[i]=i;
			Cnt[i]=1;
		}
	}
	int find(int x)
	{
		if(unin[x]==x) return x;
		else return unin[x]=find(unin[x]);
	}
	void joint(int x, int y)
	{
		int fx=find(id[x]), fy=find(id[y]);
		if( fx==fy && fx!=0 && fy!=0) return;
		if( fx==0 ) {Cnt[id[x]]=0; id[x]=++n; fx=id[x]; unin[fx]=fx; Cnt[fx]=1;}
		if( fy==0 ) {Cnt[id[y]]=0; id[y]=++n; fy=id[y]; unin[fy]=fy; Cnt[fy]=1;}
		unin[fy]=fx;
		Cnt[fx]+=Cnt[fy];
	}
	int judge(int x, int y)
	{
		if(x==y) return 1;
		int fx=find(id[x]), fy=find(id[y]);
		if( unin[fx]==0 || unin[fy]==0 ) return 0;
		return unin[fx]==unin[fy];
	}
	int query(int x)
	{
		int fx=find(id[x]);
		return Cnt[fx];
	}
	void disjt(int x)
	{
		int fx=find(id[x]);
		unin[fx]=0;
	}
};
int N,M;
Union U;

int main()
{
	#ifdef LOCAL
	freopen("3.in", "r", stdin);
	freopen("out.txt", "w", stdout);
	#endif
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		scanf("%d%d", &N, &M);
		U.init(N);
		for(int i=1; i<=M; i++)
		{
			char opt;
			int x,y;
			scanf(" %c", &opt);
			if(opt=='U')
			{
				scanf("%d%d", &x, &y);
				U.joint(x,y);
			}
			if(opt=='F')
			{
				scanf("%d%d", &x, &y);
				if(U.judge(x,y)) puts("Yes");
				else puts("No");
			}
			if(opt=='S')
			{
				scanf("%d", &x);
				printf("%d\n", U.query(x));
			}
			if(opt=='D')
			{
				scanf("%d", &x);
				U.disjt(x);
			}
		}
	}
	return 0;
}

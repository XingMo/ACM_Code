/*
Codeforces - 13E
有 N个洞排成一列，每个洞有一个能量值 a_i
将一个球丢进第 i个洞内，它将跳跃到 i+a_i个洞
这样一直跳跃直到跳出 N的范围
现在有两种操作，往第 i个洞内丢球，将第 i个洞的能量值修改为 b
每次丢球，输出这个球最后进入的洞的编号以及跳跃次数

刚开始想了一万种思路，发现都没法维护这个修改
后来看了下题解，发现是分块暴力搞……
果然分块的境界还不够啊，以后像这种维护不了的东西果断要想到分块啊……

将 N个洞按 sqrt(N)的大小分块，
每个洞维护一个跳出这一块后第一个进入的洞 nxt[i]
以及跳出这一块之前的跳跃次数 cnt[i]
每次修改都暴力重新维护一下一整个块，复杂度 O(sqrt(N))
每次询问都顺着 nxt[i]走，复杂度也是 O(sqrt(N))
总的复杂度就是 O(N*sqrt(N))
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

const int maxn=1e5+10;
int N,M,bsiz,A[maxn],cnt[maxn],nxt[maxn];

int id(int x){return x/bsiz;}
void maintain(int i)
{
	if(i+A[i]>=N)
	{
		cnt[i] = 1;
		nxt[i] = N;
	}
	else
	{
		int j = i+A[i];
		if(id(i)==id(j))
		{
			if(nxt[j]==N) nxt[i] = j, cnt[i] = 1;
			else nxt[i] = nxt[j], cnt[i] = cnt[j]+1;
		}
		else
		{
			cnt[i] = 1;
			nxt[i] = j;
		}
	}
}

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		CLR(cnt); CLR(nxt);
		bsiz=sqrt(N);
		for(int i=0; i<N; i++) scanf("%d", &A[i]);
		for(int i=N-1; i>=0; i--) maintain(i);
		for(int i=0,opt,a,b; i<M; i++)
		{
			scanf("%d%d", &opt, &a);
			a--;
			if(opt)
			{
				int sum=0, end=a;
				while(a<N)
				{
					sum += cnt[a];
					end = a;
					a = nxt[a];
				}
				printf("%d %d\n", end+1, sum);
			}
			else
			{
				scanf("%d", &A[a]);
				int l=bsiz*id(a), r=min(N,bsiz*(id(a)+1));
				for(int j=r-1; j>=l; j--) maintain(j);
			}
		}
	}
	return 0;
}


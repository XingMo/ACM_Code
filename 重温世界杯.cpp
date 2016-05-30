/*
HDU - 1422
给定一个环，可以从任意一个点出发
每到达一个城市，可以获得一定金钱并有一定花费
当金钱为负数时结束，问最多能走多少个城市

Two Pointers
把花费减去获得，得到一个点的权值
然后再把原数组复制一遍以方便处理
枚举左端点，移动右端点计算对左端点的前缀和
当前缀和为负数时，更新答案并移动左端点到 r+1

移动左端点到 r+1的原因是，移动左端点到 [l+1, r]中任意一个位置 i
r位置的前缀和都必然要减去一个正数 sum(l,i)，所以都是不合法的
所以直接移动到 r+1即可

时间复杂度 O(N)
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

const int maxn=1e5+10;
int N;
int inpt[2*maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		for(int i=1; i<=N; i++)
		{
			int a,b;
			scanf("%d%d", &a, &b);
			inpt[i] = inpt[i+N] = a-b;
		}
		int l=1,r=1, ans=0;
		while(l<=N)
		{
			if(inpt[l]<0) {l++; continue;}
			LL sum=0;
			for(r=l; r-l+1<=N; r++)
			{
				sum+=inpt[r];
				if(sum<0) break;
			}
			if(r-l+1>N) {ans=N; break;}
			else
			{
				ans=max(r-l, ans);
				l = r+1;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}


/*
SCU - 4531
给定一个一般图，要求用最少的点覆盖所有边
并且使用的点数不超过 10个

一般图的最小点覆盖是一个 NP问题
这道题的正解是直接暴力枚举
按顺序枚举每一条边，每当遇到第一条左右端点均未覆盖的边
就枚举覆盖左右端点，对于两种情况再分别进行 dfs

由于每覆盖一条边至少用掉一个点，所以dfs深度不超过 10层
每层都选择覆盖左端点或者右端点，所以是 2^10
在加上每层dfs都从上一次考虑的边开始，
能保证一次出解只遍历一遍所有边
所以复杂度不会超过 O(2^10*M)
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

const int maxn=1e3+10, maxm=2e3+10, INF=0x3f3f3f3f;
int N,M,ans;
Pii inpt[maxm];
bool vis[maxn];

void dfs(int,int);

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
		CLR(vis);
		ans=INF;
		scanf("%d%d", &N, &M);
		for(int i=0; i<M; i++) scanf("%d%d", &inpt[i].first, &inpt[i].second);
		dfs(0,0);
		if(ans==INF) puts("Poor lcy");
		else printf("%d\n", ans);
	}
	return 0;
}

void dfs(int dep, int st)
{
	if(dep > 10) return;
	bool allclear = 1;
	for(int i=st; i<M; i++)
	{
		if(vis[inpt[i].first] || vis[inpt[i].second]) continue;
		allclear = 0;
		vis[inpt[i].first] = 1;
		dfs(dep+1, i+1);
		vis[inpt[i].first] = 0;
		
		vis[inpt[i].second] = 1;
		dfs(dep+1, i+1);
		vis[inpt[i].second] = 0;
		
		break;
	}
	if(allclear) ans = min(ans, dep);
}

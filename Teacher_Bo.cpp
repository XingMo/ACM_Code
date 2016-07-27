/*
HDU - 5762
给定平面上的若干个点，问是否存在两个点对
{A,B}，{C,D}使得前者的曼哈顿距离等于后者

首先所有的坐标不会超过 1e5,
意味这曼哈顿距离的范围在 0到 2e5之间
并且它只要判定是否存在解

所以我们直接暴力枚举点对，然后把得到的曼哈顿距离标记一下
如果这个距离值之前已经出现过了，说明有解，直接跳出循环
根据鸽巢原理，这个次数不会超过 2e5次
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

const int maxn=2e5+10;
bool vis[maxn];
int inpt[2][maxn];

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
		int N, M;
		scanf("%d%d", &N, &M);
		CLR(vis);
		bool ok=0;
		for(int i=0; i<N; i++)
		{
			scanf("%d%d", &inpt[0][i], &inpt[1][i]);
			if(ok) continue;
			for(int j=0; j<i; j++)
			{
				int dist = abs(inpt[0][i]-inpt[0][j]) + abs(inpt[1][i]-inpt[1][j]);
				if(vis[dist]){ok=1; break;}
				vis[dist] = 1;
			}
		}
		puts(ok?"YES":"NO");
	}
	return 0;
}


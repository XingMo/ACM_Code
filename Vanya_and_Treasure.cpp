/*
CodeForces - 677D
一个N*M的网格图，每个格子有一把钥匙，上面一个权值
要求从 1到 P按顺序收集钥匙，保证 P只有一把
问收集全部钥匙的最短距离是多少

首先 dp[x][y]表示收集 (x,y)的最小距离
然后这题不能暴力，复杂度是 O(N^4)
官方题解的 bfs复杂度没看懂，所以退而求其次，
实现了一下comment的二维树状数组

树状数组维护二维静态前缀最小值，感觉很tricky
其实就是利用了树状数组的结构，然后树状数组只能维护前缀，
这题正好只需要知道前缀最小就行了
对于一个点 (x_0,y_0)，我们需要直到它左上区域，右上区域，左下区域，右下区域对他的最优值
左上： dp[x][y] + x_0-x + y_0-y
右上： dp[x][y] + x_0-x + y-y_0
左下： dp[x][y] + x-x_0 + y_0-y
右下： dp[x][y] + x-x_0 + y-y_0
而其中 x_0，y_0对一个点来说是定值
所以左上维护出最小的 dp[x][y]-x-y，右上维护出最小的 dp[x][y]-x+y
左下维护出最小的 dp[x][y]+x-y，右下维护出最小的 dp[x][y]+x+y
然后再用 x_0，y_0与上面四个式子凑出相应的曼哈顿距离，就得到最优值了
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

const int maxn=3e2+10, INF=0x3f3f3f3f;
struct BIT
{
	int n;
	int bit[maxn][maxn];
	int tim[maxn][maxn];
	void init(int tn)
	{
		n=tn;
		MST(bit,0x3f);
		CLR(tim);
	}
	void update(int nt,int x,int y,int val)
	{
		for(int i=x; i<=n; i+=i&-i) for(int j=y; j<=n; j+=j&-j)
		{
			if(tim[i][j]!=nt) {tim[i][j]=nt; bit[i][j]=INF;}
			bit[i][j] = min( bit[i][j], val);
		}
	}
	int query(int nt,int x,int y)
	{
		int res=INF;
		for(int i=x; i>0; i-=i&-i) for(int j=y; j>0; j-=j&-j)
		{
			if(tim[i][j]==nt) res = min(res, bit[i][j]);
		}
		return res;
	}
};

int N,M,P,Lim;
int Map[maxn][maxn];
vector<Pii> list[maxn*maxn];
int dp[maxn][maxn];
BIT bit[4];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	scanf("%d%d%d", &N, &M, &P);
	MST(dp,0x3f);
	Lim=max(N,M);
	for(int i=0; i<4; i++) bit[i].init(Lim);
	
	for(int i=1; i<=N; i++) for(int j=1; j<=M; j++)
	{
		scanf("%d", &Map[i][j]);
		list[ Map[i][j] ].push_back(make_pair(i,j));
	}
	
	for(int i=0; i<(int)list[1].size(); i++)
	{
		int x=list[1][i].first, y=list[1][i].second;
		dp[x][y] = x+y-2;
		bit[0].update(1, x, y, dp[x][y]-x-y);
		bit[1].update(1, x, Lim-y+1, dp[x][y]-x+y );
		bit[2].update(1, Lim-x+1, y, dp[x][y]+x-y );
		bit[3].update(1, Lim-x+1, Lim-y+1, dp[x][y]+x+y);
	}
	for(int nt=2; nt<=P; nt++)
	{
		for(int i=0; i<(int)list[nt].size(); i++)
		{
			int x=list[nt][i].first, y=list[nt][i].second;
			int &now=dp[x][y];
			now = min(now, bit[0].query(nt-1, x, y) + x + y);
			now = min(now, bit[1].query(nt-1, x, Lim-y+1) + x - y);
			now = min(now, bit[2].query(nt-1, Lim-x+1, y) - x + y);
			now = min(now, bit[3].query(nt-1, Lim-x+1, Lim-y+1) - x - y);
		}
		for(int i=0; i<(int)list[nt].size(); i++)
		{
			int x=list[nt][i].first, y=list[nt][i].second;
			bit[0].update(nt, x, y, dp[x][y]-x-y);
			bit[1].update(nt, x, Lim-y+1, dp[x][y]-x+y );
			bit[2].update(nt, Lim-x+1, y, dp[x][y]+x-y );
			bit[3].update(nt, Lim-x+1, Lim-y+1, dp[x][y]+x+y);
		}
	}
	
	int x=list[P][0].first, y=list[P][0].second;
	printf("%d\n", dp[x][y]);
	return 0;
}

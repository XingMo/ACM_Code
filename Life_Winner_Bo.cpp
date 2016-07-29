/*
HDU - 5754
有一个 N*M的国际象棋棋盘，刚开始左上角有一个棋子
每次只能往右下角移动，谁先到达右下角谁就赢
如果无论如何也到不了右下角，就平局
有四种棋子，王、车、马、后

博弈四合一

1. 王
打表即可
2. 车
相当于两堆分别为 N-1和 M-1的石子的 Nimm游戏
3. 马
有平局的游戏，规则如下
如果一个局面能取得胜利，那么先手会胜
如果不能取得胜利，那么先手会尽量和局
如果不能和局，先手只能接受失败
判定方法如下：
如果一个局面后继有必败点，那么这个点必胜
如果一个局面后继全是必胜点，那么这个点必败
如果以上条件都不满足，那么这个点必平
4. 后
裸的威佐夫(Wythoff)博弈，O(N)打表可得
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
#include <cassert>
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

const int maxn=1e3+10;
int N,M;

int king[maxn][maxn];
int KING(int,int);

int knight[maxn][maxn];
int KNIGHT(int,int);

int queen[maxn][maxn];
bool vis[maxn];
int QUEEN();

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	MST(king,-1);
	king[1][1]=0;
	for(int i=1000; i>=1; i--) for(int j=i; j>=1; j--) if(king[i][j]==-1)
		KING(i,j);
	
	MST(knight,-1);
	knight[1][1]=0;
	for(int i=1000; i>=1; i--) for(int j=i; j>=1; j--) if(knight[i][j]==-1)
		KNIGHT(i,j);
		
	MST(queen,-1);
	QUEEN();
	
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		int ty;
		scanf("%d%d%d", &ty, &N, &M);
		if(ty==1)
		{
			if(king[N][M]) puts("B");
			else puts("G");
		}
		if(ty==2)
		{
			if( N!=M ) puts("B");
			else puts("G");
		}
		if(ty==3)
		{
			if(knight[N][M]==1) puts("B");
			else if(knight[N][M]==2) puts("D");
			else puts("G");
		}
		if(ty==4)
		{
			if(queen[N-1][M-1]) puts("B");
			else puts("G");
		}
	}
	return 0;
}

int KING(int x,int y)
{
	if(king[x][y]!=-1 || king[y][x]!=-1 ) return king[x][y];
	if(x>1) if( !KING(x-1,y) ) return king[x][y] = king[y][x] = 1;
	if(y>1) if( !KING(x,y-1) ) return king[x][y] = king[y][x] = 1;
	if(x>1 && y>1) if( !KING(x-1, y-1) ) return king[x][y] = king[y][x] = 1;
	return king[x][y]=king[y][x]=0;
}

int KNIGHT(int x,int y)
{
	if(~knight[x][y] || ~knight[y][x]) return knight[x][y];
	if( (x-1<=0 || y-2<=0) && (x-2<=0 || y-1<=0) ) return knight[y][x] = knight[x][y] = 2;
	
	int ok0=2, ok1=2;
	if(x-1>0 && y-2>0) ok0 = KNIGHT(x-1, y-2);
	if(x-2>0 && y-1>0) ok1 = KNIGHT(x-2, y-1);
	if(ok0==0 || ok1==0 ) return knight[x][y] = knight[y][x] = 1;
	if( ok0==1 && ok1==1 ) return knight[y][x] = knight[x][y] = 0;
	return knight[y][x] = knight[x][y] = 2;
}

int QUEEN()
{
	int k=0,a=0,b=0;
	queen[0][0]=0;
	for(int i=1; i<maxn && i+k+1<maxn; i++) if(!vis[i])
	{
		k++;
		a=i; b=a+k;
		vis[a]=1; vis[b]=1;
		queen[a][b] = queen[b][a] = 0;
	}
	return 0;
}

/*
LightOJ - 1364
一副扑克牌，不断地从中抽牌
要求四种花色都至少要有给定的张数
其中如果抽到了王牌，可以将其变为任意花色
求满足条件时，抽出的期望张数

刚开始想错了，两张王牌并非在一开始就给定了
而是在游戏中可以视当前情况选择着变的
这两种方式是不一样的

由于牌数其实并不会很多，
复杂度乘一乘发现才 1e7级别的，所以直接暴力DP

将两张王牌当前变成了什么，四种花色有多少张全部表示成状态
这样就是一个六维的dp数组，然后暴力转移即可
当抽到王牌的时候，对它变成各种牌的情况取 min
抽到其他牌的期望全部加起来
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

const DBL eps=1e-8;
int A[4];
DBL dp[5][5][16][16][16][16];

DBL DP(int,int,int,int,int,int);

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
		int ok=0;
		for(int i=0; i<4; i++)
		{
			scanf("%d", &A[i]);
			if(A[i] > 13) ok += A[i]-13;
		}
		if(ok>2) {printf("Case %d: -1\n", ck); continue;}
		MST(dp,0xc0);
		DBL ans = DP(0,0,0,0,0,0);
		printf("Case %d: %.7f\n", ck, ans);
	}
	return 0;
}

DBL DP(int J0, int J1, int C,int D,int H,int S)
{
	if(dp[J0][J1][C][D][H][S] > eps) return dp[J0][J1][C][D][H][S];
	if(C>=A[0] && D>=A[1] && H>=A[2] && S>=A[3]) return dp[J0][J1][C][D][H][S] = 0.0;
	
	DBL tot = 54-C-D-H-S, lc=13-C, ld=13-D, lh=13-H, ls=13-S;
	if(J0==1) lc++; if(J1==1) lc++;
	if(J0==2) ld++; if(J1==2) ld++;
	if(J0==3) lh++; if(J1==3) lh++;
	if(J0==4) ls++; if(J1==4) ls++;
	 
	DBL res=0.0, tem;
	if(!J0)
	{
		tem = 1e9;
		tem = min(tem, (DP(1, J1, C+1, D, H, S)+1)/tot);
		tem = min(tem, (DP(2, J1, C, D+1, H, S)+1)/tot);
		tem = min(tem, (DP(3, J1, C, D, H+1, S)+1)/tot);
		tem = min(tem, (DP(4, J1, C, D, H, S+1)+1)/tot);
		res += tem;
	}
	
	if(!J1)
	{
		tem = 1e9;
		tem = min(tem, (DP(J0, 1, C+1, D, H, S)+1)/tot);
		tem = min(tem, (DP(J0, 2, C, D+1, H, S)+1)/tot);
		tem = min(tem, (DP(J0, 3, C, D, H+1, S)+1)/tot);
		tem = min(tem, (DP(J0, 4, C, D, H, S+1)+1)/tot);
		res += tem;
	}
	
	if(lc) res += (DP(J0, J1, C+1, D, H, S)+1)*lc/tot;
	if(ld) res += (DP(J0, J1, C, D+1, H, S)+1)*ld/tot;
	if(lh) res += (DP(J0, J1, C, D, H+1, S)+1)*lh/tot;
	if(ls) res += (DP(J0, J1, C, D, H, S+1)+1)*ls/tot;
	
	return dp[J0][J1][C][D][H][S] = res;
}


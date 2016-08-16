/*
HDU - 5802
给定一个数 P，可以对 P进行三种操作
停顿一次，给这个数 +1，-x
其中减法操作，如果上次操作为 -x，那么这次减的数就为 2x
如果上次操作为加或者停顿，那么这次就减去 1
其中 P最小为 0, 问最少几次能把 P变成 Q

贪心XJB乱搞
如果 P<=Q，直接不停地 +1即可
如果 P >Q，那么先不断地减，直到再减 P<=Q
这时候有两种决策，一是继续减，然后加回来
二是停顿一下，然后继续减
两种决策取一个 min即为答案
dfs的时候要记录一下前面停顿的个数，继续减再加回来的时候，
可以将一些 +1移动到前面停顿的位置上

有个trick：
P不能小于 0的含义是 P最小为 0
比如 P=2，x=8时，可以继续减，不过减完 P=0
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
#define PCUT puts("\n----------")

LL P,Q;
LL prec[35];
LL solve(LL,LL);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	prec[0] = 1;
	for(int i=1; i<35; i++) prec[i] = prec[i-1]<<1;
	for(int i=0; i<35; i++) prec[i] --; 

	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		scanf("%lld%lld", &P, &Q);
		if(P<=Q) printf("%lld\n", Q-P);
		else printf("%lld\n", solve(P-Q, 0));
	}
	return 0;
}

LL solve(LL rem, LL scnt)
{
	LL ocnt;
	for(ocnt=1; ocnt<35; ocnt++) if(rem-prec[ocnt] <= 0)
		break;
	if(rem-prec[ocnt] == 0) return ocnt;
	LL tem = Q - max(0LL, Q + rem-prec[ocnt]);
	LL ans = tem - min(tem, scnt) + ocnt;
	return min(ans, 1 + ocnt-1 + solve(rem-prec[ocnt-1], scnt+1));
}

/*
LightOJ - 1284
一个三维的空间格子，每次随机选择两个点
由这两个点构成体对角线的正方体内的格子翻转状态
开始所有格子状态为 0，问最后状态为 1的格子的期望个数

对于每个格子，计算他对答案的贡献
枚举每个格子，对于每一维，
很容易算出这一维上它不被选到的概率
用 1减去，再把三维的概率乘起来，就是他被选中的概率

然后翻转 K次就比较有技巧了
由于 K比较大，所以不好直接计算
设翻转 K次，其中有奇数次选到了的概率为 f(n)，
有偶数次被选到了的概率为 g(n)，显然 g(n) = 1-f(n)
f(n) = p*g(n-1) + (1-p)*f(n-1) = p*(1-f(n-1)) + (1-p)*f(n-1)
f(n) = (1-2*p)*f(n-1) + p
这是一个一阶的递推式，很容易求出通项公式
f(n) = (1 - (1-2*p)^n)/2
然后用快速幂求解即可
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

const int maxk=1e4+10;
DBL Get(DBL,int);
DBL calc(DBL,DBL);

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
		int X,Y,Z,K;
		scanf("%d%d%d%d", &X, &Y, &Z, &K);
		DBL ans=0, tot=(DBL)X*Y*Z;
		for(int i=1; i<=X; i++) for(int j=1; j<=Y; j++) for(int k=1; k<=Z; k++)
		{
			DBL p = calc(i,X)*calc(j,Y)*calc(k,Z);
			ans += Get(p,K);
		}
		printf("Case %d: %.7f\n", ck, ans);
	}
	return 0;
}

DBL Get(DBL p, int n)
{
	p = 1-2*p;
	DBL res=1;
	while(n)
	{
		if(n&1) res=res*p;
		p=p*p;
		n>>=1;
	}
	return 0.5*(1-res);
}

DBL calc(DBL i, DBL n)
{
	return 1.0- ( SQR(n-i) + SQR(i-1) )/ SQR(n);
}

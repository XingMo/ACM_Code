/*
Codeforces - 585C
A和B两个人玩一个游戏，开始时一共有 X个橘子和 Y个苹果
A先拿出一个橘子，B拿出一个苹果，然后进行若干次操作
每次一个人将所有的水果给另一个人，
然后再从袋子里拿出与之前等量的两种水果
最后袋子里的水果恰好被拿完，求构造一个满足条件的操作序列

如果直到 Stern-Brocot Tree这个东西的话，
会发现整个游戏过程和它的构造过程是一样的

刚开始有 0/1 和 1/0两个既约分数
其中分母代表橘子，分子代表苹果，第一个分数代表 A，第二个分数代表 B
然后每次将其中一个分数替换成两个分数的 mediant（中间值）
a/b 和 c/d的中间值为 {a+c}/{b+d}
所以根据 Stern-Brocot Tree的性质:
Y/X要是上面的一个节点，必须满足 GCD(X,Y)==1
并且如果 GCD(X,Y)==1，那么 Y/X一定是上面的一个节点
然后就顺着这个树去找节点就好了

如果 GCD(X,Y)!=1，那么就是 "Impossible"
如果 X>Y，就顺着左儿子向下走，并且将分数换成 Y/{X-Y}，同理 Y>X
那么这就是一个更相减损法了，同样可以用辗转相除法来优化
这样一来时间复杂度就是 O(log(max(X,Y)))
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

LL GCD(LL a, LL b) {return b?GCD(b,a%b):a;}
LL X,Y;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%lld%lld", &X, &Y))
	{
		if(GCD(X,Y)!=1) puts("Impossible");
		else
		{
			while(X>1 && Y>1)
			{
				if(X>Y)
				{
					printf("%lldA", X/Y);
					X -= X/Y*Y;
				}
				else
				{
					printf("%lldB", Y/X);
					Y -= Y/X*X;
				}
			}
			if(Y==1) printf("%lldA", X/Y-1);
			if(X==1) printf("%lldB", Y/X-1);
			puts("");
		}
	}
	return 0;
}


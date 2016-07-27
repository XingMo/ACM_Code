/*
HDU - 4349
给定n求满足 C(n,m)为奇数的 m的个数

首先朴素的想法是把每一个组合数都求出来
但是组合数比较大，所以自然的就想到 mod 2
所以很关键的一点是要转化为 C(n,m)%2
即 C(n,m)%2 = 1 的m的个数
利用lucas定理展开，审视乘积中的每一个组合数
由于 C(0,0) = C(1,0) = C(1,1) = 1，C(0,1) = 0
所以要想结果为 1，当 n的二进制某一位为 0时，m此位只能为 0
当 n的二进制某位为 1时，m此位可为 0，可为 1
根据乘法原理，n的二进制位有 cnt个 1 ，答案即为 2^cnt
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

int N;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		int cnt=__builtin_popcount(N);
		printf("%d\n", 1<<cnt);
	}
	return 0;
}


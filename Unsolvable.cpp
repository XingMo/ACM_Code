/*
Codeforces - 225E
求正整数 z，使得方程
z = [x/2]+y+xy 没有正整数解

数论好题！
首先显然要把向下取整的去掉
令 x=2k+1 (k>=0)
z = k + 2y + 2ky
z = k + 2y(k+1)
z+1 = (2y+1)(k+1) (k>=0)
由此可以看出，对于任何 z+1含奇质因子的都能构造出解，
所以要想无解，z+1 = 2^t，即 z = 2^t-1

令 x=2k (k>0)
z = k + y + 2ky
2z + 1 = 2k + 2y + 4ky + 1
2z + 1 = (2y+1)(2k+1) (k>0)
2^(t+1) - 1 = (2y+1)(2k+1)
所以除非 2^(t+1) - 1是个质数，否则都能构造出解
形如 2^t - 1的质数是梅森质数，目前找到了 49个梅森质数
题目只要求前 40个，百度一下，你就知道。
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

const int MOD=1e9+7;
int N;
int tp[50]={0, 2, 3, 5, 7, 13, 17, 19, 31, 61, 89, 107, 127, 521, 607, 1279, 2203, 2281, 3217, 4253, 4423, 9689, 9941, 11213, 19937, 21701, 23209, 44497, 86243, 110503, 132049, 216091, 756839, 859433, 1257787, 1398269, 2976221, 3021377, 6972593, 13466917, 20996011, 24036583, 25964951, 30402457, 32582657};
LL Pow(LL,LL,LL);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		printf("%d\n", (int)(Pow(2,tp[N]-1,MOD)-1+MOD)%MOD);
	}
	return 0;
}

LL Pow(LL x, LL n, LL p)
{
	LL res=1;
	while(n)
	{
		if(n&1) res=res*x%p;
		x=x*x%p;
		n>>=1;
	}
	return res;
}

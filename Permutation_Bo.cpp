/*
HDU - 5753
给定一个数列 C，以及一个 N的排列 H
如果 H_i比两边的数都大，那么f(H)就累加上 C_i
问 f(H)的期望取值为多少

根据期望的线性性质，对于 C中的每一个数
求它被统计入答案的概率，然后再乘以这个数算出贡献

如果它在数列两端，那么一共只有两种排列，所以概率是 1/2
如果它在数列中间，那么有 3!种排列，其中 2!种满足要求，所以概率是 1/3
注意特判一下 N=1的情况
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

const int maxn=1e3+10;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int N, C;
	while(~scanf("%d", &N))
	{
		if(N==1)
		{
			scanf("%d", &C);
			printf("%.6f\n", C*1.0);
			continue;
		}
		int sum0=0, sum1=0;
		for(int i=1; i<=N; i++)
		{
			scanf("%d", &C);
			if(i==1 || i==N) sum1 += C;
			else sum0 += C;
		}
		printf("%.6f\n", sum0/3.0+sum1*0.5);
	}
	return 0;
}


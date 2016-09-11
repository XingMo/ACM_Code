/*
Codeforces - Gym10081D (NEERC)
给定一个数，将其变成若干个数的和
如果这些数有因子，那么只能是 2或 3
并且这些数两两不能除尽

构造题
如果这个数为 1,那么答案就为 1
若不为 1，那么如果他是奇数
那么我减去最大的一个 3次幂转化为一个偶数，
再不断地提出 2，变成一个奇数，循环直到其变为 1
所以这个数 N = 3^{a_1} + 2^{b_1}(3^{a_2} + 2^{b_2}(...))
其中 3的次数 a_1 > a_2 > a_3 ...
而展开后 2的次数 0 < b_1*b_2*b3... < b_2*b_3... < b_3...
所以这些数按顺序排开，他们 3这个因子的次数是递减的
而 2这个因子的次数是递增的，所以相互不能整除，即为答案
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

int siz;
LL outp[110], pow3[110];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	#ifndef LOCAL
	freopen("distribution.in", "r", stdin);
	freopen("distribution.out", "w", stdout);
	#endif
	
	pow3[0]=1;
	for(int i=1; i<=39; i++) pow3[i]=pow3[i-1]*3;
	
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		LL N, mul=1;
		siz = 0;
		cin >> N;
		while(N)
		{
			while(!(N&1)) {mul<<=1; N>>=1;}
			for(int i=39; i>=0; i--) if(pow3[i]<=N)
			{
				outp[siz++] = mul*pow3[i];
				N -= pow3[i];
				break;
			}
		}
		printf("%d\n", siz);
		for(int i=0; i<siz; i++) cout << outp[i] << ' ';
		puts("");
	}
	return 0;
}


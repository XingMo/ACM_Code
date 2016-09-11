/*
Codeforces - Gym100801H (NEERC)
给定一个字符串hash，为 \sum_{i=0}^{len-1} str[i]*31^{len-1-i}
求 K个长度不超过 1000的字符串，使得他们的hash值相等
其中每个hash值是 32位有符号整数，K<=1000

构造题
先要把每个hash看作生成一个 31进制数
那么我随意生成一个字符串，
在高位减一，在低位加上 31，hash结果是一样的

所以我生成一个长度为 1000的字符串，然后逐位进行这样的操作
就正好能构造出 1000个hash值相等的字符串
然后输出前 K个即可
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

const int maxn=1e3+10;
int N;
char str[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	#ifndef LOCAL
	freopen("hash.in", "r", stdin);
	freopen("hash.out", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		for(int i=0; i<1000; i++) str[i] = 'X';
		puts(str);
		for(int i=0; i<N-1; i++) 
		{
			str[i] -= 1; str[i+1] += 31;
			puts(str);
			str[i] += 1; str[i+1] -= 31;
		}
	}
	return 0;
}

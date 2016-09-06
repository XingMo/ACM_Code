/*
CSU - 1803 （湖南省赛16）
给定 N和 M，问有多少对 a和 b
其中 1<=a<=N，1<=b<=M，且 a*b%2016=0

刚开始想错了，导致我花了很多时间去思考如何去重
后来看到一种特别机智的做法
a*b = (k*2016 + t)*b = t*b = 0 (mod 2016)
所以只要枚举 a mod 2016的余数
对于每个这样的余数，找出有多少个 b符合条件
然后对于 a和 a+2016的答案是一样的
这样统计就方便多了
别忘了最后减去 a=0的情况
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

const int maxn=2016+10;
LL gcd(LL a, LL b){return b?gcd(b,a%b):a;}
int N,M;
LL res[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		LL ans=0;
		for(int i=0; i<2016; i++) res[i] = M/(2016/gcd(2016,i));
		for(int i=0; i<2016; i++) ans += N/2016*res[i];
		N%=2016;
		for(int i=0; i<=N; i++) ans += res[i];
		ans -= res[0];
		cout << ans << "\n";
	}
	return 0;
}


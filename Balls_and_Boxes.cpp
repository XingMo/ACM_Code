/*
HDU - 5810
有 N个球， M个盒子，随机将球放入盒子中
求每个盒子球个数的方差的期望值
方差 V = sum_{i=1}^m {X_i - bar{X}}^2 / m

推推公式啥的，赛上没推出来，最后找规律过得
果然期望和概率还是太差了啊 orz

首先可以展开公式，V = sum_{i=1}^m {X_i}/m - n^2/m^2
然后就变成求前面那项的期望了，
用一个随机变量 Y_j来表示第 j个球是否在第 i个盒子里
E(X_i) = E((sum_{j=1}^n Y_j)^2)
利用期望的线性性展开这个和式得到 
E((sum_{j-1}^n Y_j)^2) = E(sum_{j=1}^n Y_j^2) + E(sum_{j=1}^n sum_{k=1}^n {j!=k} Y_j*Y_k)
= nE(Y_j^2) + n(n-1)E(Y_j*Y_k)
= n/m + n(n-1)/m^2
所以最后的答案就是 
E(V) = n/m + n(n-1)/m^2 - n^2/m^2
=n(m-1)/m^2
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

LL GCD(LL a, LL b){return b?GCD(b, a%b):a;}
LL N,M;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%lld%lld", &N, &M))
	{
		if(!N && !M) break;
		LL D = GCD(N*(M-1), M*M);
		printf("%lld/%lld\n", N*(M-1)/D, M*M/D);
	}
	return 0;
}

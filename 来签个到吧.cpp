/*
SCU - 4519
盒子里有若干个球，每个球上面都有一个数字，数字各不相同
每次从中选两个数字 x，y，设 z=abs(x-y)
若 z不在盒子中，则加入这个数
反复执行操作，直到无法再向盒子里加数
随机从盒子中摸出一个球，反复执行这个操作直到所有球都被摸出来过
问最后的期望步数

第一部分的构造：
设所有数的最大公因数是D
则所有数可以表示为 x=k*D
所以所有的 |y-x|=k'*D，必然是 D的倍数
实际上这个相减的过程是更相减损法的再现
所以保证一定能构造出最大公因数 D
构造出 D后，用最大的数不断减去 D，
就能构造出小于最大数的所有 D的倍数

第二部分的期望：
设 dp[i]为摸到 i个求的期望步数
dp[i] = (N-(i-1))/N * dp[i-1] + (i-1)/N * dp[i] + 1
移项整理后可得 dp[i] = dp[i-1] + N/(N-(i-1))

最后的期望步数要加上第一部分构造时所用的步数
*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
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
#define Sqr(a) (a*a)
int GCD(int a,int b){return b?GCD(b,a%b):a;};

const int maxn=1e5+10;
int N;
int inpt[maxn];
DBL dp[maxn];

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
		scanf("%d", &N);
		CLR(dp);
		
		for(int i=0; i<N; i++) scanf("%d", &inpt[i]);
		sort(inpt,inpt+N);
		int gcd=inpt[0];
		for(int i=1; i<N; i++) gcd=GCD(gcd,inpt[i]);

		int tot=inpt[N-1]/gcd;
		if(!inpt[0]) tot++;
		dp[1]=1;
		for(int i=2; i<=tot; i++)
		{
			DBL down=tot-i+1,up=tot;
			dp[i]=dp[i-1]+up/down;
		}
		cout << (int)floor(dp[tot])+tot-N << '\n';
//		printf("%d\n", floor(dp[tot])+tot-N);
	}
	return 0;
}


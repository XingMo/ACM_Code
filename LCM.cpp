/*
SEERC15 - D
给定两个数 A和 B，求一个正整数 N，使得 LCM(A+N, B+N)最小
如果有多解，输出最小的 N

这次是两个数加上一个数，再与 GCD|LCM 关联起来
用之前的套路怎么也不会算，因为这个加法真是太讨厌了
看了题解才知道咋做的

因为不管加了什么数，两个数的差是不会改变的
不妨设 A比 B小，那么两个数可以表示为 A和 A+x
其中 x=B-A，这样一来，lcm = (A+N)*(A+N+x)/gcd
而 d=gcd(x, x+a)，不管 x怎么变，d必然是 a的约数
所以 gcd必然是 x的约数
接下来就简单了，根号复杂度枚举 x的因子作为 gcd
然后求一个最小的 lcm即可

由于 gcd必须是 x的因子
那么我加一个最小的 N使得 A+N能被gcd整除，那么 A+N+x必然也能被 gcd整除
这样就能算出 gcd为该因子的最小的 lcm

然后可能要特判一下 A=B的情况
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
#include <ctime>
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

const int maxn = 1e5+10;
const LL INF = 0x3f3f3f3f3f3f3f3f;
int A,B;
LL tmax, ans;

void update(int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &A, &B))
	{
		if(A==B)
		{
			puts("1");
			continue;
		}
		tmax = ans = INF;
		if(B<A) swap(A,B);
		int delt = B-A, lim=sqrt(delt);
		for(int i=1; i<=lim; i++) if(delt%i==0)
		{
			update(i);
			update(delt/i);
		}
		cout << ans << endl;
	}
	return 0;
}

void update(int tem)
{
	LL add = tem - A%tem;
	LL res = (LL)(A+add)/__gcd(A+add, B+add)*(B+add);
	if(res < tmax)
	{
		tmax = res;
		ans = add;
	}
	else if(res == tmax)
		ans = min(ans, add);
}

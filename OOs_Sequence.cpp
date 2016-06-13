/*
HDU - 5288
定义 f(l,r)为区间内不被其他数整除的数的个数
求所有区间 f(l,r)的和

可以计算第 i个数对于答案的贡献
在某个区间 [i-L, i-R]内，第 i个数不被其他数整除
设这个向左延伸的最大距离 L,向右最大距离 R
则答案就为 sigma_1^N {L_i*R_i}
以计算 L为例，维护一下数 a最晚出现的位置，然后枚举第 i个数的因子
在所有因子最晚出现的位置中取 max，就能得到 L
计算 R是一样的，只要把数列翻转一下即可
时间复杂度 O(N*sqrt(a))
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

const int maxn=1e5+10, maxa=1e4+10, MOD=1e9+7;
int N;
int inpt[maxn];
int L[maxa];
int res[2][maxn];

void solve(int*);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		for(int i=1; i<=N; i++) scanf("%d", &inpt[i]);
		solve(res[0]);
		reverse(inpt+1,inpt+1+N); 
		solve(res[1]);
		reverse(res[1]+1, res[1]+1+N);
		int ans=0;
		for(int i=1; i<=N; i++)
		{
			ans=((LL)ans+(LL)res[0][i]*res[1][i])%MOD;
		}
		printf("%d\n", ans);
	}
	return 0;
}

void solve(int res[])
{
	CLR(L);
	for(int i=1; i<=N; i++)
	{
		int Lim=sqrt(inpt[i]), l=0;
		for(int j=1; j<=Lim; j++)
		{
			if(inpt[i]%j) continue;
			l=max(l, L[j]);
			l=max(l, L[inpt[i]/j]);
		}
		res[i]= i-l;
		L[ inpt[i] ] = i;
	}
}

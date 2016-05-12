/*
SCU - 4499
已有 x，求利用除法和乘法算出 x^n的最小步数

IDA* 迭代加深地去搜
如果能在step步得出解，那么大于这个步数的也一定有解
所以从小到大枚举步数，然后暴力去搜
由于限定步数，就可以加一个 A*的估价剪枝
当前最值反复平方也不能在限定步数得出解的时候，则不往下搜
由于N只有1000,而 2^10 > 1000，所以最终步数其实不会很大
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

const int maxn=1e3, INF=0x3f3f3f3f;
int N;
int list[maxn];

int dfs(int,int);
int Value(int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	#endif
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		list[0]=1;
		scanf("%d", &N);
		if(N==1){puts("0");continue;}
		for(int dep=1; dep<16; dep++)
		{
			int ans=dfs(1, dep);
			if(~ans) {printf("%d\n", dep);break;}
		}
		
	}
}

int dfs(int step, int Lim)
{
	if(step>Lim) return -1;
//	printf("debug: %d\n", step);
	int ans;
	for(int i=0; i<=step-1; i++)
	{
		list[step]=list[step-1]+list[i];
//		printf("%d\n", list[step]);
		if(list[step]==N) return step;
		if(step+Value(list[step])>Lim) continue;
		ans=dfs(step+1, Lim);
		if(~ans) return ans;
		
		list[step]=abs(list[step-1]-list[i]);
		if(list[step]==N) return step;
		if(step+Value(list[step])>Lim) continue;
		ans=dfs(step+1, Lim);
		if(~ans) return ans;
	}
	return -1;
}

int Value(int num)
{
	int val=0;
	if(num==0) return INF;
	else
	{
		while(num<N){num*=2; val++;}
	}
	return val;
}

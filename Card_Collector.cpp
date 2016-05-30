/*
HDU - 4336
有 N张卡片，有 p_i的概率抽到第 i张
求集齐所有卡片的期望步数

注意 sigma{p_i} != 1
所以有可能一次什么也抽不到,设 m'是 m的子集，列出公式
expt[m] = (1- sigma{p_i})expt[m] + sigma{ p_i * expt[m']} + 1
化简成 expt[m] = (sigma{ p_i*expt[m'] } + 1) / sigma{p_i}
然后状压dp就好了
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
#define Sqr(a) (a*a)
#define CLR(a) MST(a,0)

const DBL eps=1e-8;
int N, fmask;
DBL prob[30];
DBL expt[1<<20];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		for(int i=0; i<N; i++) scanf("%lf", &prob[i]);
		fmask=(1<<N)-1;
		CLR(expt);
		for(int m=1; m<=fmask; m++)
		{
			DBL pc=0.0 ,ec=1.0;
			for(int i=0; i<N; i++)
			{
				if(!(m&(1<<i))) continue;
				int nm = m^(1<<i);
				pc += prob[i];
				ec += expt[nm]*prob[i];
			}
			if(pc>eps) expt[m]=ec/pc;
			else expt[m]=1e10;
		}
		printf("%.5f\n", expt[fmask]);
	}
	return 0;
}


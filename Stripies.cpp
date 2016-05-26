/*
POJ - 1862
有若干个生物，有自己的质量，两个生物碰撞后，
生成一个新的生物质量为 2*sqrt(m_1*m_2)

贪心策略是尽可能地让大的生物先碰撞
这样较大的数可以被多次开方
由于 N比较小，生成的新生物冒泡排序一下就好了
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

int N;
DBL inpt[110];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		for(int i=0; i<N; i++) scanf("%lf", &inpt[i]);
		sort(inpt, inpt+N);
		for(int i=N-1; i>0; i--)
		{
			inpt[i-1]=2*sqrt(inpt[i]*inpt[i-1]);
			for(int j=i-2; j>0; j--)
			{
				if(inpt[j-1] > inpt[j]) swap(inpt[j-1], inpt[j]);
				else break;
			}
		}
		printf("%.3f\n", inpt[0]);
	}
	return 0;
}


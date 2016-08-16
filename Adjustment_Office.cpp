/*
Gym - 100851A (NEERC15 - A)
给一个 N×N的格子，位于格子有一个权值，为 x+y
询问 Q次，询问一行或者一列的权值和，然后清空这一行或这一列
其中 N<=1e6，Q<=1e5

由于每次都会清空，所以一个点的权值只会被加一次
并且权值的分布相当有规律
所以只要统计一下哪些行，哪些列被询问过了
以后询问的时候，先加上所有权值，再减去哪些被询问过的位置的权值
总的时间复杂度是 O(Q)的
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

const int maxn=1e6+10;
int N,Q;
bool qx[maxn], qy[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	#ifndef LOCAL
	freopen("adjustment.in", "r", stdin);
	freopen("adjustment.out", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &Q))
	{
		CLR(qx); CLR(qy);
		char opt; int p;
		LL rsum=0, csum=0, rcnt=0, ccnt=0;
		for(int i=0; i<Q; i++)
		{
			scanf(" %c%d", &opt, &p);
			if(opt=='R')
			{
				if(qx[p]) puts("0");
				else
				{
					rcnt++; rsum+=p; qx[p]=1;
					printf("%lld\n", (LL)p*N + (LL)N*(N+1)/2 - (LL)ccnt*p - csum);
				}
			}
			else
			{
				if(qy[p]) puts("0");
				else
				{
					ccnt++; csum+=p; qy[p]=1;
					printf("%lld\n", (LL)p*N + (LL)N*(N+1)/2 - (LL)rcnt*p - rsum);
				}
			}
		}
	}
	return 0;
}


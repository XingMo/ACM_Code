/*
HDU - 5821
给定一列球，每种球有一个颜色，同一颜色的球无区别
每次选择一个区间，任意排列其中的球
问是否能从初始的排列变成给定的一个排列

首先有一个很重要的性质，就是同种颜色的球
最终排列的相对顺序是不变的
也就是说，颜色为 1的第一个球，最后还是在同类球的第一个
预处理出每个球在最终排列上的位置，然后对于每次操作
尽量让最终排列靠前的在区间的前面
即按最终位置 sort区间上的球，最后再check一下是否合法即可
时间复杂度 O(NMlogN)
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

const int maxn=1e3+10;
int N, M, A[maxn], B[maxn], cnt[maxn], tot[maxn], opt[maxn][2];
int C[maxn];

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
		CLR(cnt); CLR(tot);
		scanf("%d%d", &N, &M);
		for(int i=1; i<=N; i++) scanf("%d", &A[i]), tot[A[i]]++;
		for(int i=1; i<=N; i++) scanf("%d", &B[i]), tot[B[i]]--;
		for(int i=1; i<=M; i++) scanf("%d%d", &opt[i][0], &opt[i][1]);
		
		bool ok=1;
		for(int i=1; i<=N; i++) if(tot[A[i]]) {ok=0; break;}
		for(int i=1; i<=N; i++) if(tot[B[i]]) {ok=0; break;}
		if(!ok){puts("No"); continue;}
		
		for(int i=1; i<=N; i++)
		{
			cnt[A[i]]++;
			int sum=0;
			for(int j=1; j<=N; j++) if(B[j]==A[i])
			{
				sum++;
				if(sum==cnt[A[i]])
				{
					C[i] = j;
					break;
				}
			}
		}
//		for(int i=1; i<=N; i++) printf("%d ", C[i]); puts("");
		for(int i=1; i<=M; i++)
		{
			int l=opt[i][0], r=opt[i][1];
			sort(C+l, C+r+1);
		}
		
		for(int i=1; i<=N; i++) if(C[i]!=i) {ok=0; break;}
		if(!ok) puts("No");
		else puts("Yes");
	}
	return 0;
}


/*
Codeforces - 451B
给定一个序列，其中每个数都不相同
问是否能在翻转其中一段后，整个序列变得单调递增

实现题
首先设一个 B数组为 A数组排序后的结果
由于只能翻转一个区间，那么我假装 A是满足要求的
找到最小的 A[l]!=B[l]，最大的 A[r]!=B[r]，
翻转的区间将会是 [l,r]这个区间，
翻转这个区间以后，再看是否满足要求

有一个 trick是找不到这样的 [l,r]的时候，
说明整个序列已经有序了，这时候随便输出一个长度为 1的区间即可
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
#define PCUT puts("----------")

const int maxn=1e5+10;
int N, A[maxn], B[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	scanf("%d", &N);
	for(int i=1; i<=N; i++) scanf("%d", &A[i]);
	for(int i=1; i<=N; i++) B[i] = A[i];
	sort(B+1, B+1+N);
	int l=-1,r=-1;
	for(int i=1; i<=N; i++)
	{
		if(A[i]!=B[i] && l==-1) l = i;
		if(A[i]!=B[i]) r=i;
	}
	reverse(A+l, A+r+1);
	bool ok=1;
	for(int i=1; i<=N; i++) if(A[i]!=B[i]) {ok=0; break;}
	if(ok)
	{
		puts("yes");
		if(l==-1 && r==-1) puts("1 1");
		else printf("%d %d\n", l, r);
	}
	else puts("no");
	return 0;
}


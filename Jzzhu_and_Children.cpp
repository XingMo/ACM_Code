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

int A[110];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int N,M;
	scanf("%d%d", &N, &M);
	for(int i=0; i<N; i++) scanf("%d", &A[i]);
	int np=0,last=N-1, cnt=0;
	for(;cnt<N;np=(np+1)%N)
	{
		if(A[np]<=0) continue;
		A[np]-=M;
		if(A[np]<=0)
		{
			last=np;
			cnt++;
		}
	}
	printf("%d", last+1);
	return 0;
}


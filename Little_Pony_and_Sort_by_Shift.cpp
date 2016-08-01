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
int A[2*maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int N;
	while(~scanf("%d", &N))
	{
		for(int i=1; i<=N; i++) scanf("%d", &A[i]);
		int firp=-1;
		for(int i=1; i<=N; i++)
		{
			if(A[i]<A[i-1] && firp==-1) firp=i;
		}
		if(firp==-1)
		{
			puts("0"); continue;
		}
		int np=N;
		for(int i=1; i<firp; i++) A[++np] = A[i];
		A[firp-1]=0;
		bool ok=1;
		for(int i=firp; i<=np; i++) 
		{
			if(A[i]<A[i-1]){ ok=0; break;}
		}
		if(!ok) puts("-1");
		else
		{
			printf("%d\n", N-firp+1);
		}
	}
	return 0;
}


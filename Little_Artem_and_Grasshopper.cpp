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

const int maxn=1e5+10;
int N;
char buff[maxn];
int A[maxn];
bool vis[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		scanf("%s", buff+1);
		for(int i=1; i<=N; i++)
		{
			scanf("%d", &A[i]);
			if(buff[i]=='<') A[i] = -A[i];
		}
		CLR(vis);
		int np=1;
		while(1<=np && np<=N && !vis[np])
		{
			vis[np]=1;
			np += A[np];
		}
		if(1<=np && np<=N) puts("INFINITE");
		else puts("FINITE");
	}
	return 0;
}


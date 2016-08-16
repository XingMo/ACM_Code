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

int N, last;
bool vis[7];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &last))
	{
		bool ok=1;
		for(int i=0,x,y; i<N; i++)
		{
			scanf("%d%d", &x, &y);
			CLR(vis);
			vis[x] = vis[7-x] = 1;
			vis[y] = vis[7-y] = 1;
			int cnt=0, tp;
			for(int j=1; j<=6; j++) if(!vis[j] && j!=last) cnt++, tp=j;
			if(cnt>=2) ok=0;
			last = tp;
		}
		puts(ok?"YES":"NO");
	}
	return 0;
}


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

const int maxn=1e3+10;
char in[maxn][6];
int N;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		bool ok=0;
		for(int i=0; i<N; i++)
		{
			scanf("%s", in[i]);
			if(!ok)
			{
				if(in[i][0]==in[i][1] && in[i][0]=='O')
				{
					ok=1;
					in[i][0] = in[i][1] = '+';
				}
			}
			if(!ok)
			{
				if(in[i][3]==in[i][4] && in[i][3]=='O')
				{
					ok=1;
					in[i][3] = in[i][4] = '+';
				}
			}
		}
		if(ok)
		{
			puts("YES");
			for(int i=0; i<N; i++) puts(in[i]);
		}
		else puts("NO");
	}
	return 0;
}


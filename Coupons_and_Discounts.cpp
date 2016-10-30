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

const int maxn=2e5+10;
int N;
int in[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		for(int i=1; i<=N; i++) scanf("%d", &in[i]);
		bool ok = 1;
		for(int i=1; i<N; i++) if((in[i]&1) && in[i+1])
		{
			in[i]--; in[i+1]--;
		}
		for(int i=1; i<=N; i++) if(!(in[i]&1)) in[i] = 0;
		for(int i=1; i<=N && ok; i++) if(in[i]) ok=0;
		puts(ok?"YES":"NO");
	}
	return 0;
}


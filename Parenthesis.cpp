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
int N,Q;
char in[maxn];
int pre[maxn], cnt[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d%s", &N, &Q, in+1))
	{
		for(int i=1; in[i]; i++)
		{
			pre[i] = pre[i-1] + (in[i]==')'?-1:1);
			cnt[i] = cnt[i-1];
			if(pre[i]<2) cnt[i]++;
		}
		for(int q=0,x,y; q<Q; q++)
		{
			scanf("%d%d", &x, &y);
			if(x>y) swap(x,y);
			bool ok=1;
			if(in[x]=='(' && in[y]==')' && cnt[y-1]-cnt[x-1]>0) ok=0;
			puts(ok?"Yes":"No");
		}
	}
	return 0;
}


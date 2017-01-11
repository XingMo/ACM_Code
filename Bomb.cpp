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
int N;
int x[maxn], y[maxn], r[maxn], c[maxn];
bool vis[maxn];

int go(int);

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
		CLR(vis);
		scanf("%d", &N);
		int ans = 0;
		for(int i=0; i<N; i++) scanf("%d%d%d%d", &x[i], &y[i], &r[i], &c[i]), ans+=c[i];
		for(int i=0; i<N; i++) if(!vis[i])
			ans = min(ans, go(i));
		printf("Case #%d: %d\n", ck, ans);
	}
	return 0;
}


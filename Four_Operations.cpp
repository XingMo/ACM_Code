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

const LL INF=0x3f3f3f3f3f3f3f3f;
int len;
char str[25];
LL Get[25][25], tpow[25];

void init();

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
		scanf("%s", str);
		len = strlen(str);
		init();
		LL ans = -INF;
		for(int i=1; i<len-3; i++)
		{
			LL ans0=-1, ans1=INF;
			for(int j=0; j<i; j++) ans0 = max(ans0, Get[0][j]+Get[j+1][i]);
//			printf("%lld %lld\n", Get[0][0], Get[1][1]);
//			cout << ans0 << endl;
			for(int j=i+1; j<len-2; j++) ans1 = min(ans1, Get[i+1][j]*Get[j+1][j+1]/Get[j+2][len-1]);
//			cout << ans1 << endl;
//			if(ans0-ans1 >= ans) printf("%d: %lld-%lld = %lld\n", i, ans0, ans1, ans0-ans1);
			ans = max(ans, ans0 - ans1);
		}
		printf("Case #%d: %lld\n", ck, ans);
	}
	return 0;
}

void init()
{
	tpow[0] = 1;
	for(int i=1; i<25; i++) tpow[i] = tpow[i-1]*10;
	LL now = 0;
	for(int i=0; i<len; i++)
	{
		now = now*10+(str[i]-'0');
		Get[0][i] = now;
	}
	for(int i=1; i<len; i++) for(int j=i; j<len; j++)
	{
		Get[i][j] = Get[0][j] - Get[0][i-1]*tpow[j-i+1];
	}
//	for(int i=0; i<len; i++, puts("")) for(int j=i; j<len; j++) printf("%lld ", Get[i][j]);
}

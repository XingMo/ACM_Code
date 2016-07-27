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
#include <ctime>
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

const int maxn=1e7+10, MOD=1e9+7;
int A[maxn];

int main()
{
	#ifdef LOCAL
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	srand(time(0));
	int T, N, nt;
	scanf("%d %d", &T, &N);
	N = min(N,maxn);
	for(int i=0; i<N; i++) A[i] = rand()%MOD;
	
	LL ans;
	
	nt=clock();
	for(int ck=1; ck<=T; ck++)
	{
		ans = 0;
		for(int i=0; i<N; i++) ans = (ans+A[i])%MOD;
	}
	printf("%lld\n", ans);
	printf("time = %.3f\n", (DBL)(clock()-nt)/CLOCKS_PER_SEC);
	
	nt=clock();
	for(int ck=1; ck<=T; ++ck)
	{
		ans = 0;
		for(int i=0; i<N; ++i) ans = (ans+A[i])%MOD;
	}
	printf("%lld\n", ans);
	printf("time = %.3f\n", (DBL)(clock()-nt)/CLOCKS_PER_SEC);
	printf("time = %.3f\n", (DBL)(clock()-nt)/CLOCKS_PER_SEC);

	return 0;
}


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
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define SQR(a) ((a)*(a))

LL gcd(LL a, LL b){return b?gcd(b,a%b):a;}

const int maxn=1e5+10;
int N;
LL W[maxn];

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
		scanf("%d", &N);
		LL sum2=0, sum=0;
		for(int i=1; i<=N; i++)
		{
			scanf("%lld", &W[i]);
			sum += abs(W[i]);
			sum2 += W[i]*W[i];
		}
		sum2 = sum2*N-sum*sum;
		LL D = gcd(sum2, N);
		if(sum2==0) puts("0/1");
		else 
		{
			printf("%lld/%lld\n", sum2/D, N/D);
		}
		
	}
	return 0;
}


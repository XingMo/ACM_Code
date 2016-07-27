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
#define Sqr(a) ((a)*(a))

const int MOD=1e9+7;
int N;
char inpt[2][110];

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
		CLR(inpt);
		scanf("%d %s %s", &N, inpt[0], inpt[1]);
		int cnt=0, ok=1;
		for(int i=0; i<N; i++)
		{
			if(inpt[0][i]=='1' && inpt[1][i]=='0')
			{
				ok=0;
				break;
			}
			if(inpt[0][i]=='1' && inpt[1][i]=='1') cnt++;
		}
		LL ans=1;
		if(!ok) puts("IMPOSSIBLE");
		else
		{
			while(cnt--)
			{
				ans<<=1;
				ans%=MOD;
			}
			cout << ans << '\n';
		}
	}
	return 0;
}


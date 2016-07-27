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

int GCD(int a,int b){return b?GCD(b,a%b):a;}

int N;
int inpt[1010];

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
		int D=0;
		for(int i=0; i<N; i++)
		{
			scanf("%d", &inpt[i]);
			if(D) D=GCD(D,inpt[i]);
			else D=inpt[i];
		}
		int ans=0;
		for(int i=0; i<N; i++) ans+=inpt[i]/D;
		printf("%d %d\n", D, ans);
	}
	return 0;
}


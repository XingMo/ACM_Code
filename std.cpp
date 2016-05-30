#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
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
#define Sqr(a) (a*a)

const int maxn=1e6+10;
int N;
int inpt[2*maxn];
int psum[2*maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	scanf("%d", &N);
	for(int i=1; i<=N; i++)
	{
		scanf("%d", &inpt[i]);
		inpt[i+N]=inpt[i];
	}
	for(int i=1; i<=2*N; i++) psum[i]=psum[i-1]+inpt[i];
	int ans=0;
	for(int i=1; i<=N; i++)
	{
		bool ok=1;
		for(int j=i; j-i+1<=N; j++)
		{
			if(psum[j]-psum[i-1]<0){ok=0; break;}
		}
		if(ok)
		{
			ans++;
			printf("%d %d\n", i, i+N-1);
		}
	}
	printf("%d\n", ans);
	return 0;
}


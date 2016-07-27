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

int gcd(int a, int b){return b?gcd(b,a%b):a;}
int N, M, A[110];
bool give[110];

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
		MST(A,-1); CLR(give);
		A[0]=100;
		scanf("%d%d", &N, &M);
		for(int i=1; i<=M; i++)
		{
			int x,y;
			scanf("%d%d", &x, &y);
			A[x]=y;
			give[x]=1;
		}
		int have=2, now=0, ts=0, s=0;
		for(int i=N; i>=1; i--)
		{
			if(A[i] != -1) now=A[i];
			else A[i]=now;
		}
		if(!give[1]) A[1]=100;
		if(!give[2]) A[2]=A[1];
		
		for(int i=1; i<=N; i++) s+=A[i];
		ts=A[1]+A[2];
		int D=gcd(ts,s);
		ts/=D; s/=D;
		printf("%d/%d\n", ts, s);
	}
	return 0;
}


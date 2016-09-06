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
#include <cassert>
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

int N,K,A,fmask;
int lel[10], loy[10];
DBL ans;

void dfs(int,int);
void cal();

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d%d", &N, &K, &A))
	{
		fmask=(1<<N)-1;
		for(int i=0; i<N; i++) scanf("%d%d", &lel[i], &loy[i]);
		ans = 0;
		dfs(0,K);
		printf("%.7f\n", ans);
	}
	return 0;
}

void dfs(int np, int left)
{
	if(np>=N) {cal(); return;}
	for(int i=0; i<=left; i++) if(loy[np]+i*10<=100)
	{
		loy[np] += i*10;
		dfs(np+1, left-i);
		loy[np] -= i*10;
	}
}

void cal()
{
	DBL res = 0;
	for(int m=0; m<=fmask; m++)
	{
		int b=0, cnt=0; DBL pro=1;
		for(int i=0; i<N; i++)
		{
			if((m>>i)&1) b+=lel[i], pro *= (100-loy[i])/100.0;
			else pro *= loy[i]/100.0, cnt++;
		}
		if(cnt > N-cnt) res += pro;
		else res += pro*A/((DBL)A+b);
	}
	ans = max(ans, res);
}

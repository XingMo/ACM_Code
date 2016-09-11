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

const int maxn=500+10;
int N;
LL in[maxn][maxn];
LL que[2*maxn];
int tail;

void Get();

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		if(N==1)
		{
			scanf("%*d");
			puts("1");
			continue;
		}
		for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) cin >> in[i][j];
		Get();
		if(tail!=2) puts("-1");
		else
		{
			LL dif = que[1]-que[0];
			for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) if(!in[i][j]) in[i][j] = dif;
			Get();
			if(tail!=1) puts("-1");
			else cout << dif << "\n";
		}
	}
	return 0;
}

void Get()
{
	tail = 0;
	for(int i=1; i<=N; i++)
	{
		LL sum1=0, sum2=0;
		for(int j=1; j<=N; j++) sum1 += in[i][j], sum2 += in[j][i];
		que[tail++] = sum1;
		que[tail++] = sum2;
	}
	LL sum=0;
	for(int i=1; i<=N; i++) sum += in[i][i];
	que[tail++] = sum;
	sum=0;
	for(int i=1; i<=N; i++) sum += in[i][N-i+1];
	que[tail++] = sum;
	sort(que, que+tail);
	tail = unique(que, que+tail) - que;
}

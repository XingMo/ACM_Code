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

const int maxn=5e3+10;
char in[2*maxn];
int N, id[2*maxn], ans[maxn], stk[2*maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%s", &N, in))
	{
		int cntA=0, cnta=0;
		for(int i=0; in[i]; i++)
		{
			if(islower(in[i])) id[i] = ++cnta;
			if(isupper(in[i])) id[i] = ++cntA;
		}
		int top = 0;
		for(int i=0; in[i]; i++)
		{
			if(top && toupper(in[stk[top-1]]) == toupper(in[i]) && in[stk[top-1]]!=in[i])
			{
				top--;
				if(isupper(in[i])) ans[id[i]] = id[stk[top]];
				else ans[id[stk[top]]] = id[i];
			}
			else stk[top++] = i;
		}
		if(top) puts("Impossible");
		else {for(int i=1; i<=N; i++) printf("%d ", ans[i]); puts("");}
	}
	return 0;
}


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

int S[100], M;
void dfs(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	M=3;
	dfs(1,2);
	return 0;
}

void dfs(int u, int v)
{
	if(u>=M)
	{
		for(int i=1; i<=M; i++) printf("%d ", S[i]);
		puts("");
		return;
	}
	
	S[u]+=2;
	if(v<M) dfs(u, v+1);
	else dfs(u+1,u+2);
	S[u]-=2;
	
	S[u]+=1; S[v]+=1;
	if(v<M) dfs(u, v+1);
	else dfs(u+1,u+2);
	S[u]-=1; S[v]-=1;
	
	S[v]+=2;
	if(v<M) dfs(u, v+1);
	else dfs(u+1, u+2);
	S[v]-=2;
}

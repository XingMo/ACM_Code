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

const int maxn=1e3+10;
int A[maxn], ans[2][maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int N;
	cin >> N;
	for(int i=1; i<=N; i++) scanf("%d", &A[i]);
	for(int i=1; i<=N; i++) 
	{
		if(A[i-1]<=A[i]) ans[0][i] = ans[0][i-1]+1;
		else ans[0][i]=1;
	}
	for(int i=N; i>=1; i--)
	{
		if(A[i+1]<=A[i]) ans[1][i] = ans[1][i+1]+1;
		else ans[1][i]=1;
	}
	int res=1;
	for(int i=1; i<=N; i++) res = max(res, ans[0][i]+ans[1][i]-1);
	printf("%d\n", res);
	return 0;
}


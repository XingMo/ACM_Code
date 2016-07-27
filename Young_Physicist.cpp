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


int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int N,X=0,Y=0,Z=0;
	scanf("%d", &N);
	for(int i=1,x,y,z; i<=N; i++)
	{
		scanf("%d%d%d", &x, &y, &z);
		X+=x; Y+=y; Z+=z;
	}
	if(!X && !Y && !Z) puts("YES");
	else puts("NO");
	return 0;
}


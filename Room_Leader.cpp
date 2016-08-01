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

struct data
{
	char name[30];
	int s;
	bool operator < (const data &v) const { return s > v.s;}
};
data inpt[60];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int N;
	scanf("%d", &N);
	for(int i=0; i<N; i++)
	{
		int p,m,a,b,c,d,e;
		scanf(" %s %d %d %d %d %d %d %d", inpt[i].name, &p, &m, &a, &b, &c, &d, &e);
		inpt[i].s = p*100 - m*50 + a + b + c + d + e;
	}
	sort(inpt, inpt+N);
	printf("%s\n", inpt[0].name);
	return 0;
}


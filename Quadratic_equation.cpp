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

const DBL eps=1e-6;
DBL A,B,C;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%lf%lf%lf", &A, &B, &C))
	{
		DBL x1,x2,d;
		d=sqrt(SQR(B)-4*A*C);
		x1 = (-B-d)/(2*A), x2 = (-B+d)/(2*A);
		if(abs(x1-x2)<eps) printf("%.5f\n", x1);
		else printf("%.5f %.5f\n", x1, x2);
	}
	return 0;
}


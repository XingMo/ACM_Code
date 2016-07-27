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
#define Sqr(a) ((a)*(a))

const int maxn=1e5+10;
int N;

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
		scanf("%d", &N);
		LL x, y, z, xl, xr, yl, yr, zl, zr;
		cin >> x >> y >> z;
		xr=xl=x; yr=yl=y; zr=zl=z;
		for(int i=2; i<=N; i++) 
		{
			cin >> x >> y >> z;
			xl=min(xl, x); xr=max(xr, x);
			yl=min(yl, y); yr=max(yr, y);
			zl=min(zl, z); zr=max(zr, z);
		}
		x=(xl+xr)/2;
		y=(yl+yr)/2;
		z=(zl+zr)/2;
		cout << x << " " << y << " " << z << endl;
	
	}
	return 0;
}


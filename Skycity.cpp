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

const DBL eps=1e-8, PI=acos(-1.0);
int sgn(DBL x){return x>eps?1:(x<eps?-1:0);}

DBL work(DBL,DBL);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int R1,R2,H,F,S;
	DBL ans;
	while(~scanf("%d%d%d%d%d", &R2, &R1, &H, &F, &S))
	{
		ans = 0;
		DBL dl = (DBL)S*F/H;
		DBL dr = 1.0*(R2-R1)/F;
		for(int i=0; i<F; i++) ans += work(R1+i*dr,dl);
		printf("%.3f\n", ans*H/F);
	}
	return 0;
}

DBL work(DBL R, DBL lis)
{
	int l=3, r=1e6;
	lis *= 0.5;
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		DBL nr = lis / tan(PI/mid);
		if(sgn(nr-R) > 0) r = mid-1;
		else l = mid;
	}
	DBL res = 2*R*tan(PI/l) * l;
	return res;
}


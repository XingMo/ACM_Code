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

const LL maxk=5e5;
LL M;
LL Cnt(LL);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(cin >> M)
	{
		LL l=1, r=1e16+10;
		while(l<r)
		{
			LL mid=(l+r)>>1;
			if(Cnt(mid)>=M) r=mid;
			else l=mid+1;
		}
		if(Cnt(l) != M) cout << "-1\n";
		else cout << l << "\n";
	}
	return 0;
}

LL Cnt(LL Lim)
{
	LL cnt=0;
	for(LL k=2; k<=maxk; k++)
	{
		cnt += Lim/(k*k*k);
	}
	return cnt;
}

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

const int maxn=1e5+10, INF=0x3f3f3f3f;
char in[maxn];
int U, D, L, R;

int Test(int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%s", in))
	{
		U=D=L=R=0;
		for(int i=0; in[i]; i++)
		{
			if(in[i]=='U') U++;
			if(in[i]=='D') D++;
			if(in[i]=='L') L++;
			if(in[i]=='R') R++;
		}
		if(U>D) swap(U,D);
		if(L>R) swap(L,R);
		int ans=INF;
		for(int i=U; i<=D; i++) ans = min(ans, Test(i));
		swap(U,L); swap(D,R);
		for(int i=U; i<=D; i++) ans = min(ans, Test(i));
		if(ans < INF) printf("%d\n", ans);
		else puts("-1");
	}
	return 0;
}

int Test(int ud)
{
	int dl = D-ud, ul=ud-U, dif=R-L, tot = L+R, res=0;
	if(dl>=ul)
	{
		res += dl;
		int ntot = L+R+dl-ul;
		if(ntot&1) return INF;
		ntot >>= 1;
		if(ntot<R) res += R-ntot; 
	}
	else
	{
		res += ul;
		int ntot = tot - ul-dl;
		if(ntot<0 || ntot&1) return INF;
		ntot >>= 1;
		if(ntot<R) res += R-ntot;
		if(ntot<L) res += L-ntot;
	}
	return res;
}
